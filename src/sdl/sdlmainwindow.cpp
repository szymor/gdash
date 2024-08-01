/*
 * Copyright (c) 2007-2013, Czirkos Zoltan http://code.google.com/p/gdash/
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:

 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include <numeric>

#include "settings.hpp"
#include "framework/app.hpp"
#include "framework/commands.hpp"
#include "framework/gameactivity.hpp"
#include "framework/titlescreenactivity.hpp"
#include "framework/messageactivity.hpp"
#include "gfx/fontmanager.hpp"
#include "sdl/sdlpixbuffactory.hpp"
#include "sdl/sdlgameinputhandler.hpp"
#include "sdl/sdlscreen.hpp"
#include "misc/logger.hpp"

#include "sdl/sdlmainwindow.hpp"


class SDLApp: public App {
public:
    SDLApp(Screen &screenref);
};

SDLApp::SDLApp(Screen &screenref)
    : App(screenref) {
    screen->set_properties(gd_cell_scale_factor_game, GdScalingType(gd_cell_scale_type_game), gd_pal_emulation_game);
    font_manager = new FontManager(*screen, "");
    gameinput = new SDLGameInputHandler;
}


/* generate a user event */
static Uint32 timer_callback(Uint32 interval, void *param) {
    SDL_Event ev;

    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);

    return interval;
}


static Activity::KeyCode activity_keycode_from_sdl_key_event(SDL_KeyboardEvent const &ev) {
    switch (ev.keysym.sym) {
        case SDLK_UP:
            return App::Up;
        case SDLK_DOWN:
            return App::Down;
        case SDLK_LEFT:
            return App::Left;
        case SDLK_RIGHT:
            return App::Right;
        case SDLK_PAGEUP:
            return App::PageUp;
        case SDLK_PAGEDOWN:
            return App::PageDown;
        case SDLK_HOME:
            return App::Home;
        case SDLK_END:
            return App::End;
        case SDLK_F1:
            return App::F1;
        case SDLK_F2:
            return App::F2;
        case SDLK_F3:
            return App::F3;
        case SDLK_F4:
            return App::F4;
        case SDLK_F5:
            return App::F5;
        case SDLK_F6:
            return App::F6;
        case SDLK_F7:
            return App::F7;
        case SDLK_F8:
            return App::F8;
        case SDLK_F9:
            return App::F9;
        case SDLK_BACKSPACE:
            return App::BackSpace;
        case SDLK_RETURN:
            return App::Enter;
        case SDLK_TAB:
            return App::Tab;
        case SDLK_ESCAPE:
            return App::Escape;

        default:
            return ev.keysym.unicode;
    }
}


class SetNextActionCommandSDL : public Command {
public:
    SetNextActionCommandSDL(App *app, NextAction &na, NextAction to_what): Command(app), na(na), to_what(to_what) {}
private:
    virtual void execute() {
        na = to_what;
    }
    NextAction &na;
    NextAction to_what;
};


static void run_the_app(App &the_app, NextAction &na) {
    /* for the sdltimer based timing */
    int const timer_ms = gd_fine_scroll ? 20 : 40;
    SDL_TimerID timer_id;
    bool timer_installed = false;
    /* for the screen based timing */
    Uint32 ticks_now = SDL_GetTicks(), ticks_last = SDL_GetTicks();
    enum { average_time_frame = 25 };
    Uint32 moved[average_time_frame];
    unsigned move_index = 0;

    if (!SDL_WasInit(SDL_INIT_TIMER))
        SDL_InitSubSystem(SDL_INIT_TIMER);

    /* if screen reports we can use it for timing, measure the number of
     * milliseconds each refresh takes */
    bool use_screen_timing = the_app.screen->has_timed_flips();
    if (use_screen_timing)
        gd_debug("starting screen based timing");
    /* by default, assume 20 ms / frame for frame rate measuring */
    std::fill(moved, moved + average_time_frame, 20);

    if (!use_screen_timing) {
        timer_id = SDL_AddTimer(timer_ms, timer_callback, NULL);
        timer_installed = true;
    }


    the_app.set_no_activity_command(new SetNextActionCommandSDL(&the_app, na, Quit));

    /* sdl_waitevent will wait until at least one event appears. */
    na = StartTitle;
    while (na == StartTitle) {
        /* and now we poll all the events, as there might be more than one. */
        bool had_timer_event1 = false;
        SDL_Event ev;

        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    the_app.quit_event();
                    break;
                case SDL_KEYDOWN:
                    if ((ev.key.keysym.sym == SDLK_F11)
                            || (ev.key.keysym.sym == SDLK_RETURN && (ev.key.keysym.mod & (KMOD_LALT | KMOD_RALT)))) {
                        gd_fullscreen = !gd_fullscreen;
                        the_app.screen->set_size(the_app.screen->get_width(), the_app.screen->get_height(), gd_fullscreen);
                        the_app.redraw_event(true);
                    } else if ((ev.key.keysym.sym == SDLK_q) && (ev.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL))) {
                        the_app.quit_event();
                    } else {
                        Activity::KeyCode keycode = activity_keycode_from_sdl_key_event(ev.key);
                        the_app.keypress_event(keycode, ev.key.keysym.sym);
                    }
                    break;
                case SDL_KEYUP:
					// TODO: refactor to make it not miss key presses
                    the_app.gameinput->keyrelease(ev.key.keysym.sym);
                    break;
                case SDL_VIDEOEXPOSE:
                    the_app.redraw_event(true);
                    break;
                case SDL_USEREVENT:
                    had_timer_event1 = true;
                    break;
                case SDL_USEREVENT+1:
                    the_app.timer2_event();
                    break;
            } // switch ev.type
        } // while pollevent

        if (use_screen_timing) {
            int average_ms = std::accumulate(moved, moved + average_time_frame, 0) / average_time_frame;
            if (average_ms < 7) {
                use_screen_timing = false;
                gd_debug("screen timing too fast, switching to built-in timer");
                timer_id = SDL_AddTimer(timer_ms, timer_callback, NULL);
                timer_installed = true;
            }
            /* feed the timer with the average value. */
            the_app.timer_event(average_ms);
            if (the_app.redraw_queued()) {
                the_app.redraw_event(the_app.screen->must_redraw_all_before_flip());
            }
            /*
            // writing the ms delays to the screen
            std::string s;
            for (int i = 0; i < average_time_frame; ++i) {
                s += SPrintf("%d ") % moved[i];
            }
            the_app.set_color(GD_GDASH_WHITE);
            the_app.blittext_n(0, the_app.screen->get_height()-20, s.c_str());
            */

            /* calculate average milliseconds / refresh. if seems to be too fast, switch to timer based stuff */
            ticks_now = SDL_GetTicks();
            Uint32 ms = ticks_now - ticks_last;
            if (ms <= 60) {
                moved[move_index] = ms;
                move_index = (move_index + 1) % average_time_frame;
            }
            /* always flip, because we need the time it waits! */
            the_app.screen->do_the_flip();
            ticks_last = ticks_now;
        } else {
            if (had_timer_event1)
                the_app.timer_event(timer_ms);
            if (the_app.redraw_queued()) {
                the_app.redraw_event(the_app.screen->must_redraw_all_before_flip());
            }
            if (the_app.screen->is_drawn()) {
                /* only flip if drawn something. */
                the_app.screen->do_the_flip();
            }
            /* we must wait the next event here so we do not eat cpu.
             * but events are generated regurarly by the timer. */
            SDL_WaitEvent(NULL);
        }

#ifdef HAVE_GTK
        // check if the g_main_loop has something to do. if it has,
        // it is usually gtk stuff - so let gtk do its job :D
        while (g_main_context_pending(NULL))
            g_main_context_iteration(NULL, FALSE);
#endif
    }

    if (timer_installed)
        SDL_RemoveTimer(timer_id);
}


void gd_main_window_sdl_run(CaveSet *caveset, NextAction &na, bool opengl) {
	(void)opengl;
    SDLPixbufFactory pf;
    Screen *screen;
	screen = new SDLScreen(pf);

    {
        SDLApp the_app(*screen);

        /* normal application: title screen, menu etc */
        the_app.caveset = caveset;
        the_app.set_quit_event_command(new AskIfChangesDiscardedCommand(&the_app, new PopAllActivitiesCommand(&the_app)));
        the_app.set_request_restart_command(new SetNextActionCommandSDL(&the_app, na, Restart));
#ifdef HAVE_GTK
        the_app.set_start_editor_command(new SetNextActionCommandSDL(&the_app, na, StartEditor));
#endif
        the_app.push_activity(new TitleScreenActivity(&the_app));

        run_the_app(the_app, na);
    }
    /* the app must die before the screen, the block above controls its lifetime */
    delete screen;
}


void gd_main_window_sdl_run_a_game(GameControl *game, bool opengl) {
	(void)opengl;
    SDLPixbufFactory pf;
    Screen *screen;
	screen = new SDLScreen(pf);

    {
        SDLApp the_app(*screen);

        NextAction na = StartTitle;      // because the func below needs one to work with
        the_app.set_quit_event_command(new SetNextActionCommandSDL(&the_app, na, Quit));
        the_app.push_activity(new GameActivity(&the_app, game));

        run_the_app(the_app, na);
    }
    /* the app must die before the screen, the block above controls its lifetime */
    delete screen;
}
