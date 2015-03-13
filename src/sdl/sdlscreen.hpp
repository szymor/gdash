/*
 * Copyright (c) 2007-2013, Czirkos Zoltan http://code.google.com/p/gdash/
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef GD_SDLSCREEN
#define GD_SDLSCREEN

#include "config.h"

#include "sdl/sdlabstractscreen.hpp"


class SDLScreen: public SDLAbstractScreen {
private:
    SDLScreen(const SDLScreen &);       // not impl
    SDLScreen &operator=(const SDLScreen &);    // not impl

public:
    SDLScreen();
    ~SDLScreen();
    virtual void configure_size();
    virtual void set_title(char const *title);
    virtual bool must_redraw_all_before_flip();
    virtual void flip();
};


#endif
