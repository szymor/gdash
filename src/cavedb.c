/*
 * Copyright (c) 2007, 2008 Czirkos Zoltan <cirix@fw.hu>
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

#include <glib.h>
#include <glib/gi18n.h>
#include <string.h>
#include "cavedb.h"



/* elements description array. do not miss an index!
	the game will check if one is missing and stop the game.
	the identifier in the saved file might also not match, reading an "outbox" from
	the file should store an O_PRE_OUTBOX.
	
   images are: image in editor, image in editor - animated, image pixbuf, game image
*/
GdElements gd_elements[] = {
	{O_SPACE, N_("Space"), P_AMOEBA_CONSUMES, "SPACE", ' ', 0, 0, 0},
	{O_DIRT, N_("Dirt"), P_AMOEBA_CONSUMES|P_VISUAL_EFFECT|P_DIRT, "DIRT", '.', 2, 2, 2},
	{O_DIRT_SLOPED_UP_RIGHT, N_("Sloped dirt (up & right)"), P_DIRT|P_SLOPED_UP|P_SLOPED_RIGHT|P_AMOEBA_CONSUMES, "DIRTSLOPEDUPRIGHT", 0, 280, 280, 280},
	{O_DIRT_SLOPED_UP_LEFT, N_("Sloped dirt (up & left)"), P_DIRT|P_SLOPED_UP|P_SLOPED_LEFT|P_AMOEBA_CONSUMES, "DIRTSLOPEDUPLEFT", 0, 281, 281, 281},
	{O_DIRT_SLOPED_DOWN_LEFT, N_("Sloped dirt (down & left)"), P_DIRT|P_SLOPED_DOWN|P_SLOPED_LEFT|P_AMOEBA_CONSUMES, "DIRTSLOPEDDOWNLEFT", 0, 282, 282, 282},
	{O_DIRT_SLOPED_DOWN_RIGHT, N_("Sloped dirt (down & right)"), P_DIRT|P_SLOPED_DOWN|P_SLOPED_RIGHT|P_AMOEBA_CONSUMES, "DIRTSLOPEDDOWNRIGHT", 0, 283, 283, 283},
	{O_DIRT2, N_("Dirt 2"), P_DIRT|P_AMOEBA_CONSUMES, "DIRT2", 0, 3, 3, 3},
	{O_BRICK, N_("Brick wall"), P_SLOPED|P_CAN_BE_HAMMERED, "WALL", 'w', 5, 5, 5},
	{O_BRICK_SLOPED_UP_RIGHT, N_("Sloped brick wall (up & right)"), P_SLOPED_UP|P_SLOPED_RIGHT|P_CAN_BE_HAMMERED, "WALLSLOPEDUPRIGHT", 0, 276, 276, 276},
	{O_BRICK_SLOPED_UP_LEFT, N_("Sloped brick wall (up & left)"), P_SLOPED_UP|P_SLOPED_LEFT|P_CAN_BE_HAMMERED, "WALLSLOPEDUPLEFT", 0, 277, 277, 277},
	{O_BRICK_SLOPED_DOWN_LEFT, N_("Sloped brick wall (down & left)"), P_SLOPED_DOWN|P_SLOPED_LEFT|P_CAN_BE_HAMMERED, "WALLSLOPEDDOWNLEFT", 0, 278, 278, 278},
	{O_BRICK_SLOPED_DOWN_RIGHT, N_("Sloped brick wall (down & right)"), P_SLOPED_DOWN|P_SLOPED_RIGHT|P_CAN_BE_HAMMERED, "WALLSLOPEDDOWNRIGHT", 0, 279, 279, 279},
	{O_BRICK_NON_SLOPED, N_("Non-sloped brick wall"), P_CAN_BE_HAMMERED, "WALLNONSLOPED", 0, 352, 352, 5},
	{O_MAGIC_WALL, N_("Magic wall"), 0, "MAGICWALL", 'M', 184, -184, -184},
	{O_PRE_OUTBOX, N_("Outbox"), 0, "OUTBOX", 'X', 351, -291, 22},	/* 291, 292, 293, 294, 295, 296, 297, 298 */
	{O_OUTBOX, N_("Outbox (open)"), 0, "OUTBOXopen", 0, 299, 299, 22},
	{O_PRE_INVIS_OUTBOX, N_("Invisible outbox"), 0, "HIDDENOUTBOX", 'H', 288, 288, 22},
	{O_INVIS_OUTBOX, N_("Invisible outbox (open)"), 0, "HIDDENOUTBOXopen", 0, 300, 300, 22},
	{O_STEEL, N_("Steel wall"), P_NON_EXPLODABLE, "STEELWALL", 'W', 4, 4, 4},
	{O_STEEL_SLOPED_UP_RIGHT, N_("Sloped steel wall (up & right)"), P_SLOPED_UP|P_SLOPED_RIGHT|P_NON_EXPLODABLE, "STEELWALLSLOPEDUPRIGHT", 0, 284, 284, 284},
	{O_STEEL_SLOPED_UP_LEFT, N_("Sloped steel wall (up & left)"), P_SLOPED_UP|P_SLOPED_LEFT|P_NON_EXPLODABLE, "STEELWALLSLOPEDUPLEFT", 0, 285, 285, 285},
	{O_STEEL_SLOPED_DOWN_LEFT, N_("Sloped steel wall (down & left)"), P_SLOPED_DOWN|P_SLOPED_LEFT|P_NON_EXPLODABLE, "STEELWALLSLOPEDDOWNLEFT", 0, 286, 286, 286},
	{O_STEEL_SLOPED_DOWN_RIGHT, N_("Sloped steel wall (down & right)"), P_SLOPED_DOWN|P_SLOPED_RIGHT|P_NON_EXPLODABLE, "STEELWALLSLOPEDDOWNRIGHT", 0, 287, 287, 287},
	{O_STEEL_EXPLODABLE, N_("Explodable steel wall"), 0, "STEELWALLDESTRUCTABLE", 'E', 72, 72, 4},
	{O_STEEL_EATABLE, N_("Eatable steel wall"), 0, "STEELWALLEATABLE", 0, 339, 339, 4},
	{O_BRICK_EATABLE, N_("Eatable brick wall"), 0, "WALLEATABLE", 0, 340, 340, 5},
	{O_STONE, N_("Stone"), P_SLOPED, "BOULDER", 'r', 1, 1, 1, 156},	/* has ckdelay */
	{O_STONE_F, N_("Stone, falling"), 0, "BOULDERf", 'R', 314, 314, 1, 156},	/* has ckdelay */
	{O_MEGA_STONE, N_("Mega stone"), P_SLOPED, "MEGABOULDER", 0, 272, 272, 272, 156},	/* has ckdelay */
	{O_MEGA_STONE_F, N_("Mega stone, falling"), 0, "MEGABOULDERf", 0, 345, 345, 272, 156},	/* has ckdelay */
	{O_DIAMOND, N_("Diamond"), P_SLOPED, "DIAMOND", 'd', 248, -248, -248, 156},	/* has ckdelay */
	{O_DIAMOND_F, N_("Diamond, falling"), 0, "DIAMONDf", 'D', 315, 315, -248, 156},	/* has ckdelay */
	{O_BLADDER_SPENDER, N_("Bladder Spender"), 0, "BLADDERSPENDER", 0, 6, 6, 6, 20},	/* has ckdelay */
	{O_INBOX, N_("Inbox"), 0, "INBOX", 'P', 35, 35, 22},
	{O_H_GROWING_WALL, N_("Expanding wall, horizontal"), P_VISUAL_EFFECT, "HEXPANDINGWALL", 'x', 316, 316, 5, 111},	/* has ckdelay */
	{O_V_GROWING_WALL, N_("Expanding wall, vertical"), P_VISUAL_EFFECT, "VEXPANDINGWALL", 'v', 326, 326, 5, 111},	/* has ckdelay */
	{O_GROWING_WALL, N_("Expanding wall"), P_VISUAL_EFFECT, "EXPANDINGWALL", 'e', 343, 343, 5, 111},	/* has ckdelay */
	{O_GROWING_WALL_SWITCH, N_("Expanding wall switch"), 0, "EXPANDINGWALLSWITCH", 0, 40, 40, 40},
	{O_CREATURE_SWITCH, N_("Creature direction switch"), 0, "FIREFLYBUTTERFLYSWITCH", 0, 18, 18, 18},
	{O_BITER_SWITCH, N_("Biter switch"), 0, "BITERSWITCH", 0, 12, 12, 12},
	{O_ACID, N_("Acid"), 0, "ACID", 0, 20, 20, 20, 128},	/* has ckdelay */
	{O_FALLING_WALL, N_("Falling wall"), 0, "FALLINGWALL", 0, 342, 342, 5, 80},	/* has ckdelay */
	{O_FALLING_WALL_F, N_("Falling wall, falling"), 0, "FALLINGWALLf", 0, 344, 344, 5, 80},	/* has ckdelay */
	{O_BOX, N_("Box"), 0, "SOKOBANBOX", 0, 21, 21, 21},
	{O_TIME_PENALTY, N_("Time penalty"), P_NON_EXPLODABLE, "TIMEPENALTY", 0, 346, 346, 9},
	{O_GRAVESTONE, N_("Gravestone"), P_NON_EXPLODABLE, "GRAVESTONE", 'G', 9, 9, 9},
	{O_STONE_GLUED, N_("Glued stone"), P_SLOPED, "GLUEDBOULDER", 0, 334, 334, 1},
	{O_DIAMOND_GLUED, N_("Glued diamond"), P_SLOPED, "GLUEDDIAMOND", 0, 341, 341, -248},
	{O_DIAMOND_KEY, N_("Diamond key"), 0, "DIAMONDRELEASEKEY", 0, 11, 11, 11},
	{O_TRAPPED_DIAMOND, N_("Trapped diamond"), P_NON_EXPLODABLE, "TRAPPEDDIAMOND", 0, 10, 10, 10},
	{O_CLOCK, N_("Clock"), 0, "CLOCK", 0, 16, 16, 16},
	{O_DIRT_GLUED, N_("Glued dirt"), 0, "GLUEDDIRT", 0, 321, 321, 2},
	{O_KEY_1, N_("Key 1"), 0, "KEY1", 0, 67, 67, 67},
	{O_KEY_2, N_("Key 2"), 0, "KEY2", 0, 68, 68, 68},
	{O_KEY_3, N_("Key 3"), 0, "KEY3", 0, 69, 69, 69},
	{O_DOOR_1, N_("Door 1"), 0, "DOOR1", 0, 64, 64, 64},
	{O_DOOR_2, N_("Door 2"), 0, "DOOR2", 0, 65, 65, 65},
	{O_DOOR_3, N_("Door 3"), 0, "DOOR3", 0, 66, 66, 66},

	{O_POT, N_("Pot"), 0, "POT", 0, 63, 63, 63},
	{O_GRAVITY_SWITCH, N_("Gravity switch"), 0, "GRAVITY_SWITCH", 0, 274, 274, 274},
	{O_PNEUMATIC_HAMMER, N_("Pneumatic hammer"), 0, "PNEUMATIC_HAMMER", 0, 62, 62, 62},
	{O_TELEPORTER, N_("Teleporter"), 0, "TELEPORTER", 0, 61, 61, 61},
	{O_SKELETON, N_("Skeleton"), 0, "SKELETON", 0, 273, 273, 273},
	{O_WATER, N_("Water"), 0, "WATER", 0, 96, -96, -96, 100},	/* has ckdelay */
	{O_WATER_1, N_("Water (1)"), 0, "WATER1", 0, 96, -96, -96},
	{O_WATER_2, N_("Water (2)"), 0, "WATER2", 0, 96, -96, -96},
	{O_WATER_3, N_("Water (3)"), 0, "WATER3", 0, 96, -96, -96},
	{O_WATER_4, N_("Water (4)"), 0, "WATER4", 0, 96, -96, -96},
	{O_WATER_5, N_("Water (5)"), 0, "WATER5", 0, 96, -96, -96},
	{O_WATER_6, N_("Water (6)"), 0, "WATER6", 0, 96, -96, -96},
	{O_WATER_7, N_("Water (7)"), 0, "WATER7", 0, 96, -96, -96},
	{O_WATER_8, N_("Water (8)"), 0, "WATER8", 0, 96, -96, -96},
	{O_WATER_9, N_("Water (9)"), 0, "WATER9", 0, 96, -96, -96},
	{O_WATER_10, N_("Water (10)"), 0, "WATER10", 0, 96, -96, -96},
	{O_WATER_11, N_("Water (11)"), 0, "WATER11", 0, 96, -96, -96},
	{O_WATER_12, N_("Water (12)"), 0, "WATER12", 0, 96, -96, -96},
	{O_WATER_13, N_("Water (13)"), 0, "WATER13", 0, 96, -96, -96},
	{O_WATER_14, N_("Water (14)"), 0, "WATER14", 0, 96, -96, -96},
	{O_WATER_15, N_("Water (15)"), 0, "WATER15", 0, 96, -96, -96},
	{O_WATER_16, N_("Water (16)"), 0, "WATER16", 0, 96, -96, -96},
	{O_COW_1, N_("Cow (left)"), P_CCW, "COWl", 0, 317, -88, -88, 384},	/* has ckdelay */
	{O_COW_2, N_("Cow (up)"), P_CCW, "COWu", 0, 318, -88, -88, 384},	/* has ckdelay */
	{O_COW_3, N_("Cow (right)"), P_CCW, "COWr", 0, 319, -88, -88, 384},	/* has ckdelay */
	{O_COW_4, N_("Cow (down)"), P_CCW, "COWd", 0, 320, -88, -88, 384},	/* has ckdelay */
	{O_COW_ENCLOSED_1, N_("Cow (enclosed, 1)"), 0, "COW_ENCLOSED1", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_COW_ENCLOSED_2, N_("Cow (enclosed, 2)"), 0, "COW_ENCLOSED2", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_COW_ENCLOSED_3, N_("Cow (enclosed, 3)"), 0, "COW_ENCLOSED3", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_COW_ENCLOSED_4, N_("Cow (enclosed, 4)"), 0, "COW_ENCLOSED4", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_COW_ENCLOSED_5, N_("Cow (enclosed, 5)"), 0, "COW_ENCLOSED5", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_COW_ENCLOSED_6, N_("Cow (enclosed, 6)"), 0, "COW_ENCLOSED6", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_COW_ENCLOSED_7, N_("Cow (enclosed, 7)"), 0, "COW_ENCLOSED7", 0, 327, -88, -88, 120},	/* has ckdelay */
	{O_WALLED_DIAMOND, N_("Walled diamond"), P_CAN_BE_HAMMERED, "WALLED_DIAMOND", 0, 322, 322, 5},
	{O_WALLED_KEY_1, N_("Walled key 1"), P_CAN_BE_HAMMERED, "WALLED_KEY1", 0, 323, 323, 5},
	{O_WALLED_KEY_2, N_("Walled key 2"), P_CAN_BE_HAMMERED, "WALLED_KEY2", 0, 324, 324, 5},
	{O_WALLED_KEY_3, N_("Walled key 3"), P_CAN_BE_HAMMERED, "WALLED_KEY3", 0, 325, 325, 5},

	{O_AMOEBA, N_("Amoeba"), P_BLOWS_UP_FLIES, "AMOEBA", 'a', 192, -192, -192, 260},	/* has ckdelay */
	{O_SWEET, N_("Sweet"), 0, "SWEET", 0, 8, 8, 8},
	{O_VOODOO, N_("Voodoo doll"), P_BLOWS_UP_FLIES, "DUMMY", 'F', 7, 7, 7},
	{O_SLIME, N_("Slime"), 0, "SLIME", 's', 200, -200, -200, 211},	/* has ckdelay */
	{O_BLADDER, N_("Bladder"), 0, "BLADDER", 0, 176, -176, -176, 267},	/* has ckdelay */
	{O_BLADDER_1, N_("Bladder (1)"), 0, "BLADDERd1", 0, 176, -176, -176},
	{O_BLADDER_2, N_("Bladder (2)"), 0, "BLADDERd2", 0, 176, -176, -176},
	{O_BLADDER_3, N_("Bladder (3)"), 0, "BLADDERd3", 0, 176, -176, -176},
	{O_BLADDER_4, N_("Bladder (4)"), 0, "BLADDERd4", 0, 176, -176, -176},
	{O_BLADDER_5, N_("Bladder (5)"), 0, "BLADDERd5", 0, 176, -176, -176},
	{O_BLADDER_6, N_("Bladder (6)"), 0, "BLADDERd6", 0, 176, -176, -176},
	{O_BLADDER_7, N_("Bladder (7)"), 0, "BLADDERd7", 0, 176, -176, -176},
	{O_BLADDER_8, N_("Bladder (8)"), 0, "BLADDERd8", 0, 176, -176, -176},
	{O_BLADDER_9, N_("Bladder (9)"), 0, "BLADDERd9", 0, 176, -176, -176},

	{O_WAITING_STONE, N_("Waiting stone"), P_SLOPED, "WAITINGBOULDER", 0, 290, 290, 1, 176},	/* has ckdelay */
	{O_CHASING_STONE, N_("Chasing stone"), P_SLOPED, "CHASINGBOULDER", 0, 17, 17, 17, 269},	/* has ckdelay */
	{O_GHOST, N_("Ghost"), 0, "GHOST", 'g', 160, -160, -160, 50},	/* has ckdelay */
	{O_GUARD_1, N_("Guard, left"), P_EXPLODES_TO_SPACE | P_CCW, "FIREFLYl", 'Q', 310, -136, -136, 384},	/* has ckdelay */
	{O_GUARD_2, N_("Guard, up"), P_EXPLODES_TO_SPACE | P_CCW, "FIREFLYu", 'o', 311, -136, -136, 384},	/* has ckdelay */
	{O_GUARD_3, N_("Guard, right"), P_EXPLODES_TO_SPACE | P_CCW, "FIREFLYr", 'O', 312, -136, -136, 384},	/* has ckdelay */
	{O_GUARD_4, N_("Guard, down"), P_EXPLODES_TO_SPACE | P_CCW, "FIREFLYd", 'q', 313, -136, -136, 384},	/* has ckdelay */
	{O_ALT_GUARD_1, N_("Alternative guard, left"), P_EXPLODES_TO_SPACE, "A_FIREFLYl", 0, 301, -104, -104, 384},	/* has ckdelay */
	{O_ALT_GUARD_2, N_("Alternative guard, up"), P_EXPLODES_TO_SPACE, "A_FIREFLYu", 0, 302, -104, -104, 384},	/* has ckdelay */
	{O_ALT_GUARD_3, N_("Alternative guard, right"), P_EXPLODES_TO_SPACE, "A_FIREFLYr", 0, 303, -104, -104, 384},	/* has ckdelay */
	{O_ALT_GUARD_4, N_("Alternative guard, down"), P_EXPLODES_TO_SPACE, "A_FIREFLYd", 0, 304, -104, -104, 384},	/* has ckdelay */
	{O_BUTTER_1, N_("Butterfly, left"), P_EXPLODES_TO_DIAMONDS, "BUTTERFLYl", 'C', 330, -144, -144, 384},	/* has ckdelay */
	{O_BUTTER_2, N_("Butterfly, up"), P_EXPLODES_TO_DIAMONDS, "BUTTERFLYu", 'b', 331, -144, -144, 384},	/* has ckdelay */
	{O_BUTTER_3, N_("Butterfly, right"), P_EXPLODES_TO_DIAMONDS, "BUTTERFLYr", 'B', 332, -144, -144, 384},	/* has ckdelay */
	{O_BUTTER_4, N_("Butterfly, down"), P_EXPLODES_TO_DIAMONDS, "BUTTERFLYd", 'c', 333, -144, -144, 384},	/* has ckdelay */
	{O_ALT_BUTTER_1, N_("Alternative butterfly, left"), P_EXPLODES_TO_DIAMONDS | P_CCW, "A_BUTTERFLYl", 0, 305, -112, -112, 384},	/* has ckdelay */
	{O_ALT_BUTTER_2, N_("Alternative butterfly, up"), P_EXPLODES_TO_DIAMONDS | P_CCW, "A_BUTTERFLYu", 0, 306, -112, -112, 384},	/* has ckdelay */
	{O_ALT_BUTTER_3, N_("Alternative butterfly, right"), P_EXPLODES_TO_DIAMONDS | P_CCW, "A_BUTTERFLYr", 0, 307, -112, -112, 384},	/* has ckdelay */
	{O_ALT_BUTTER_4, N_("Alternative butterfly, down"), P_EXPLODES_TO_DIAMONDS | P_CCW, "A_BUTTERFLYd", 0, 308, -112, -112, 384},	/* has ckdelay */
	{O_STONEFLY_1, N_("Stonefly, left"), P_EXPLODES_TO_STONES, "STONEFLYl", 0, 335, -152, -152, 384},	/* has ckdelay */
	{O_STONEFLY_2, N_("Stonefly, up"), P_EXPLODES_TO_STONES, "STONEFLYu", 0, 336, -152, -152, 384},	/* has ckdelay */
	{O_STONEFLY_3, N_("Stonefly, right"), P_EXPLODES_TO_STONES, "STONEFLYr", 0, 337, -152, -152, 384},	/* has ckdelay */
	{O_STONEFLY_4, N_("Stonefly, down"), P_EXPLODES_TO_STONES, "STONEFLYd", 0, 338, -152, -152, 384},	/* has ckdelay */
	{O_BITER_1, N_("Biter, up"), 0, "BITERu", 0, 347, -168, -168, 518},	/* has ckdelay */
	{O_BITER_2, N_("Biter, right"), 0, "BITERr", 0, 348, -168, -168, 518},	/* has ckdelay */
	{O_BITER_3, N_("Biter, down"), 0, "BITERd", 0, 349, -168, -168, 518},	/* has ckdelay */
	{O_BITER_4, N_("Biter, left"), 0, "BITERl", 0, 350, -168, -168, 518},	/* has ckdelay */

	{O_PRE_PL_1, N_("Player birth (1)"), 0, "GUYBIRTH1", 0, 32, 32, 32},
	{O_PRE_PL_2, N_("Player birth (2)"), 0, "GUYBIRTH2", 0, 33, 33, 33},
	{O_PRE_PL_3, N_("Player birth (3)"), 0, "GUYBIRTH3", 0, 34, 34, 34},
	{O_PLAYER, N_("Player"), P_BLOWS_UP_FLIES | P_EXPLODES_TO_SPACE, "GUY", 0, 328, 328, 35, 32},	/* has ckdelay */
	{O_PLAYER_BOMB, N_("Player with bomb"), P_BLOWS_UP_FLIES | P_EXPLODES_TO_SPACE, "GUYBOMB", 0, 42, 42, 42, 25},	/* has ckdelay */
	{O_PLAYER_GLUED, N_("Glued player"), P_BLOWS_UP_FLIES | P_EXPLODES_TO_SPACE, "GUYGLUED", 0, 329, 329, 35},
	{O_PLAYER_STIRRING, N_("Player stirring"), P_BLOWS_UP_FLIES | P_EXPLODES_TO_SPACE, "GUYSTIRRING", 0, 256, -256, -256},

	{O_BOMB, N_("Bomb"), 0, "BOMB", 0, 48, 48, 48},
	{O_BOMB_TICK_1, N_("Ticking bomb (1)"), 0, "IGNITEDBOMB1", 0, 49, 49, 49},
	{O_BOMB_TICK_2, N_("Ticking bomb (2)"), 0, "IGNITEDBOMB2", 0, 50, 50, 50},
	{O_BOMB_TICK_3, N_("Ticking bomb (3)"), 0, "IGNITEDBOMB3", 0, 51, 51, 51},
	{O_BOMB_TICK_4, N_("Ticking bomb (4)"), 0, "IGNITEDBOMB4", 0, 52, 52, 52},
	{O_BOMB_TICK_5, N_("Ticking bomb (5)"), 0, "IGNITEDBOMB5", 0, 53, 53, 53},
	{O_BOMB_TICK_6, N_("Ticking bomb (6)"), 0, "IGNITEDBOMB6", 0, 54, 54, 54},
	{O_BOMB_TICK_7, N_("Ticking bomb (7)"), 0, "IGNITEDBOMB7", 0, 55, 55, 55},

	{O_PRE_CLOCK_1, N_("Clock birth (1)"), 0, "CLOCKBIRTH1", 0, 28, 28, 28, 280},	/* has ckdelay */
	{O_PRE_CLOCK_2, N_("Clock birth (2)"), 0, "CLOCKBIRTH2", 0, 29, 29, 29, 280},	/* has ckdelay */
	{O_PRE_CLOCK_3, N_("Clock birth (3)"), 0, "CLOCKBIRTH3", 0, 30, 30, 30, 280},	/* has ckdelay */
	{O_PRE_CLOCK_4, N_("Clock birth (4)"), 0, "CLOCKBIRTH4", 0, 31, 31, 31, 280},	/* has ckdelay */
	{O_PRE_DIA_1, N_("Diamond birth (1)"), 0, "DIAMONDBIRTH1", 0, 56, 56, 56, 280},	/* has ckdelay */
	{O_PRE_DIA_2, N_("Diamond birth (2)"), 0, "DIAMONDBIRTH2", 0, 57, 57, 57, 280},	/* has ckdelay */
	{O_PRE_DIA_3, N_("Diamond birth (3)"), 0, "DIAMONDBIRTH3", 0, 58, 58, 58, 280},	/* has ckdelay */
	{O_PRE_DIA_4, N_("Diamond birth (4)"), 0, "DIAMONDBIRTH4", 0, 59, 59, 59, 280},	/* has ckdelay */
	{O_PRE_DIA_5, N_("Diamond birth (5)"), 0, "DIAMONDBIRTH5", 0, 60, 60, 60, 280},	/* has ckdelay */
	{O_EXPLODE_1, N_("Explosion (1)"), 0, "EXPLOSION1", 0, 43, 43, 43, 280},	/* has ckdelay */
	{O_EXPLODE_2, N_("Explosion (2)"), 0, "EXPLOSION2", 0, 44, 44, 44, 280},	/* has ckdelay */
	{O_EXPLODE_3, N_("Explosion (3)"), 0, "EXPLOSION3", 0, 45, 45, 45, 280},	/* has ckdelay */
	{O_EXPLODE_4, N_("Explosion (4)"), 0, "EXPLOSION4", 0, 46, 46, 46, 280},	/* has ckdelay */
	{O_EXPLODE_5, N_("Explosion (5)"), 0, "EXPLOSION5", 0, 47, 47, 47, 280},	/* has ckdelay */
	{O_PRE_STONE_1, N_("Stone birth (1)"), 0, "BOULDERBIRTH1", 0, 36, 36, 36, 280},	/* has ckdelay */
	{O_PRE_STONE_2, N_("Stone birth (2)"), 0, "BOULDERBIRTH2", 0, 37, 37, 37, 280},	/* has ckdelay */
	{O_PRE_STONE_3, N_("Stone birth (3)"), 0, "BOULDERBIRTH3", 0, 38, 38, 38, 280},	/* has ckdelay */
	{O_PRE_STONE_4, N_("Stone birth (4)"), 0, "BOULDERBIRTH4", 0, 39, 39, 39, 280},	/* has ckdelay */
	{O_PRE_STEEL_1, N_("Steel birth (1)"), 0, "STEELWALLBIRTH1", 0, 24, 24, 24, 280},	/* has ckdelay */
	{O_PRE_STEEL_2, N_("Steel birth (2)"), 0, "STEELWALLBIRTH2", 0, 25, 25, 25, 280},	/* has ckdelay */
	{O_PRE_STEEL_3, N_("Steel birth (3)"), 0, "STEELWALLBIRTH3", 0, 26, 26, 26, 280},	/* has ckdelay */
	{O_PRE_STEEL_4, N_("Steel birth (4)"), 0, "STEELWALLBIRTH4", 0, 27, 27, 27, 280},	/* has ckdelay */
	{O_GHOST_EXPL_1, N_("Ghost explosion (1)"), 0, "GHOSTEXPLOSION1", 0, 80, 80, 80, 280},	/* has ckdelay */
	{O_GHOST_EXPL_2, N_("Ghost explosion (2)"), 0, "GHOSTEXPLOSION2", 0, 81, 81, 81, 280},	/* has ckdelay */
	{O_GHOST_EXPL_3, N_("Ghost explosion (3)"), 0, "GHOSTEXPLOSION3", 0, 82, 82, 82, 280},	/* has ckdelay */
	{O_GHOST_EXPL_4, N_("Ghost explosion (4)"), 0, "GHOSTEXPLOSION4", 0, 83, 83, 83, 280},	/* has ckdelay */
	{O_BOMB_EXPL_1, N_("Bomb explosion (1)"), 0, "BOMBEXPLOSION1", 0, 84, 84, 84, 280},	/* has ckdelay */
	{O_BOMB_EXPL_2, N_("Bomb explosion (2)"), 0, "BOMBEXPLOSION2", 0, 85, 85, 85, 280},	/* has ckdelay */
	{O_BOMB_EXPL_3, N_("Bomb explosion (3)"), 0, "BOMBEXPLOSION3", 0, 86, 86, 86, 280},	/* has ckdelay */
	{O_BOMB_EXPL_4, N_("Bomb explosion (4)"), 0, "BOMBEXPLOSION4", 0, 87, 87, 87, 280},	/* has ckdelay */

	{O_PLAYER_PNEUMATIC_LEFT, NULL /* Player using hammer, left */, P_BLOWS_UP_FLIES|P_EXPLODES_TO_SPACE, "GUYHAMMERl", 0, 265, 265, 265},
	{O_PLAYER_PNEUMATIC_RIGHT, NULL /* Player using hammer, right */, P_BLOWS_UP_FLIES|P_EXPLODES_TO_SPACE, "GUYHAMMERr", 0, 268, 268, 268},
	{O_PNEUMATIC_ACTIVE_LEFT, NULL /* Active hammer, left */, 0, "HAMMERACTIVEl", 0, 264, 264, 264},
	{O_PNEUMATIC_ACTIVE_RIGHT, NULL /* Active hammer, right */, 0, "HAMMERACTIVEr", 0, 269, 269, 269},

	{O_UNKNOWN, N_("Unknown element"), P_NON_EXPLODABLE, "UNKNOWN", 0, 289, 289, 4},
	{O_NONE, N_("No element"), 0, "NONE", 0, 79, 79, 79},
	{O_MAX},

	/* these are just helpers, for all the element -> image index information to be in this array */
	{O_FAKE_BONUS, NULL, 0, NULL, 0, 120, -120, -120},
	{O_OUTBOX_CLOSED, NULL, 0, NULL, 0, 22, 22, 22},	/* game graphics - also for imported diego effects, but don't know if it is used anywhere in original games */
	{O_OUTBOX_OPEN, NULL, 0, NULL, 0, 23, 23, 23},
	{O_COVERED, NULL, 0, NULL, 0, 128, -128, -128},
	{O_PLAYER_LEFT, NULL, 0, NULL, 0, 232, -232, -232},
	{O_PLAYER_RIGHT, NULL, 0, NULL, 0, 240, -240, -240},
	{O_PLAYER_TAP, NULL, 0, NULL, 0, 216, -216, -216},
	{O_PLAYER_BLINK, NULL, 0, NULL, 0, 208, -208, -208},
	{O_PLAYER_TAP_BLINK, NULL, 0, NULL, 0, 224, -224, -224},
	{O_CREATURE_SWITCH_ON, NULL, 0, NULL, 0, 19, 19, 19},
	{O_GROWING_WALL_SWITCH_HORIZ, NULL, 0, NULL, 0, 40, 40, 40},
	{O_GROWING_WALL_SWITCH_VERT, NULL, 0, NULL, 0, 41, 41, 41},
	{O_GRAVITY_SWITCH_ACTIVE, NULL, 0, NULL, 0, 275, 275, 275},

	{O_QUESTION_MARK, NULL, 0, NULL, 0, 70, 70, 70},
	{O_EATABLE, NULL, 0, NULL, 0, 71, 71, 71},
	{O_DOWN_ARROW, NULL, 0, NULL, 0, 73, 73, 73},
	{O_LEFTRIGHT_ARROW, NULL, 0, NULL, 0, 74, 74, 74},
	{O_EVERYDIR_ARROW, NULL, 0, NULL, 0, 75, 75, 75},
	{O_GLUED, NULL, 0, NULL, 0, 76, 76, 76},
	{O_OUT, NULL, 0, NULL, 0, 77, 77, 77},
	{O_EXCLAMATION_MARK, NULL, 0, NULL, 0, 78, 78, 78},
	{-1},
};



/* entries. */
/* type given for each element;
 * GD_TYPE_ELEMENT represents a combo box of gdash objects.
 * GD_TAB&LABEL represents a notebook tab or a label.
 * others are self-explanatory. */
const GdStructDescriptor
gd_cave_properties[] = {
	/* default data */
	{"", GD_TAB, 0, N_("Cave data")},
	{"Name", GD_TYPE_STRING, 0, N_("Name"), G_STRUCT_OFFSET(Cave, name), 1, N_("Name of game")},
	{"Description", GD_TYPE_STRING, 0, N_("Description"), G_STRUCT_OFFSET(Cave, description), 1, N_("Some words about the game")},
	{"Author", GD_TYPE_STRING, 0, N_("Author"), G_STRUCT_OFFSET(Cave, author), 1, N_("Name of author")},
	{"Date", GD_TYPE_STRING, 0, N_("Date"), G_STRUCT_OFFSET(Cave, date), 1, N_("Date of creation")},
	{"WWW", GD_TYPE_STRING, 0, N_("WWW"), G_STRUCT_OFFSET(Cave, www), 1, N_("Web page or e-mail address")},
	{"Difficulty", GD_TYPE_STRING, 0, N_("Difficulty"), G_STRUCT_OFFSET(Cave, difficulty), 1, N_("Difficulty (informative)")},
	{"Remark", GD_TYPE_STRING, 0, N_("Remark"), G_STRUCT_OFFSET(Cave, remark), 1, N_("Remark (informative)")},

	{"Selectable", GD_TYPE_BOOLEAN, 0, N_("Selectable as start"), G_STRUCT_OFFSET(Cave, selectable), 1, N_("This sets whether the game can be started at this cave.")},
	{"Intermission", GD_TYPE_BOOLEAN, GD_ALWAYS_SAVE, N_("Intermission"), G_STRUCT_OFFSET(Cave, intermission), 1, NULL},
	{"IntermissionProperties.instantlife", GD_TYPE_BOOLEAN, 0, N_("   Instant life"), G_STRUCT_OFFSET(Cave, intermission_instantlife), 1, N_("If true, an extra life is given to the player, when the intermission cave is reached.")},
	{"IntermissionProperties.rewardlife", GD_TYPE_BOOLEAN, 0, N_("   Reward life"), G_STRUCT_OFFSET(Cave, intermission_rewardlife), 1, N_("If true, an extra life is given to the player, when the intermission cave is successfully finished.")},
	{"Size", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Width"), G_STRUCT_OFFSET(Cave, w), 1, N_("Width and height of cave."), 12, 128},
	{"Size", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Height"), G_STRUCT_OFFSET(Cave, h), 1, N_("Width and height of cave."), 12, 128},
	{"Size", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Visible, left"), G_STRUCT_OFFSET(Cave, x1), 1, N_("Visible parts of the cave, upper left and lower right corner."), 0, 127},
	{"Size", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Visible, upper"), G_STRUCT_OFFSET(Cave, y1), 1, N_("Visible parts of the cave, upper left and lower right corner."), 0, 127},
	{"Size", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Visible, right"), G_STRUCT_OFFSET(Cave, x2), 1, N_("Visible parts of the cave, upper left and lower right corner."), 0, 127},
	{"Size", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Visible, lower"), G_STRUCT_OFFSET(Cave, y2), 1, N_("Visible parts of the cave, upper left and lower right corner."), 0, 127},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Border color"), G_STRUCT_OFFSET(Cave, colorb), 1, N_("Border color for C64 graphics. Only for compatibility, not used by GDash.")},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Background color"), G_STRUCT_OFFSET(Cave, color0), 1, N_("Background color for C64 graphics")},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Color 1 (dirt)"), G_STRUCT_OFFSET(Cave, color1), 1, N_("Foreground color 1 for C64 graphics")},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Color 2 (steel wall)"), G_STRUCT_OFFSET(Cave, color2), 1, N_("Foreground color 2 for C64 graphics")},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Color 3 (brick wall)"), G_STRUCT_OFFSET(Cave, color3), 1, N_("Foreground color 3 for C64 graphics")},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Amoeba color"), G_STRUCT_OFFSET(Cave, color4), 1, N_("Amoeba color for C64 graphics")},
	{"Colors", GD_TYPE_COLOR, GD_ALWAYS_SAVE|GD_DONT_SHOW_IN_EDITOR, N_("Slime color"), G_STRUCT_OFFSET(Cave, color5), 1, N_("Slime color for C64 graphics")},
	{"Charset", GD_TYPE_STRING, 0, N_("Character set"), G_STRUCT_OFFSET(Cave, charset), 1, N_("Theme used for displaying the game. Not used by GDash.")},
	{"Fontset", GD_TYPE_STRING, 0, N_("Font set"), G_STRUCT_OFFSET(Cave, fontset), 1, N_("Font used during the game. Not used by GDash.")},


	/* difficulty */
	{"", GD_TAB, 0, N_("Difficulty")},
	{"", GD_LEVEL_LABEL, 0},
	{"", GD_LABEL, 0, N_("<b>Diamonds</b>")},
	{"DiamondsRequired", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Diamonds needed"), CAVE_OFFSET(level_diamonds[0]), 5, N_("Here zero means automatically count diamonds before level start. If negative, the value is subtracted from that. This is useful for totally random caves."), -100, 999},
	{"DiamondValue", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Score for diamonds"), CAVE_OFFSET(diamond_value), 1, N_("Number of points per diamond collected, before opening the exit."), 0, 100},
	{"DiamondValue", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Score for extra diamonds"), CAVE_OFFSET(extra_diamond_value), 1, N_("Number of points per diamond collected, after opening the exit."), 0, 100},
	{"", GD_LABEL, 0, N_("<b>Time</b>")},
	{"CaveTime", GD_TYPE_INT, GD_ALWAYS_SAVE, N_("Time (s)"), CAVE_OFFSET(level_time[0]), 5, N_("Time available to solve cave, in seconds."), 1, 999},
	{"CaveMaxTime", GD_TYPE_INT, 0, N_("Maximum time (s)"), CAVE_OFFSET(max_time), 1, N_("If you reach this time by collecting too many clocks, the timer will overflow."), 60, 999},
	{"PALTiming", GD_TYPE_BOOLEAN, 0, N_("   PAL timing"), CAVE_OFFSET(pal_timing), 1, N_("On the PAL version of the C64 computer, the timer was "
	"actually slower than normal seconds. This flag is used to compensate for this. Most original games are authored for the PAL version.")},
	{"TimeValue", GD_TYPE_INT, 0, N_("Score for time"), CAVE_OFFSET(level_timevalue[0]), 5, N_("Points for each seconds remaining, when the player exits the level."), 0, 50},
	{"CaveScheduling", GD_TYPE_SCHEDULING, GD_DONT_SAVE, N_("Scheduling type"), CAVE_OFFSET(scheduling), 1, N_("This flag sets whether the game uses an emulation of the original timing (c64-style), or a more modern milliseconds-based timing. The original game used a delay (empty loop) based timing of caves; this is selected by setting this to BD1, BD2, Construction Kit or Crazy Dream 7. (BD1 intermissions are faster than normal caves - that is the only difference between BD1 and BD2 scheduling.)")},
	{"CaveDelay", GD_TYPE_INT, GD_DONT_SAVE, N_("   Delay (c64-style)"), CAVE_OFFSET(level_ckdelay[0]), 5, N_("The length of the delay loop between game frames. Used when milliseconds-based timing is inactive, ie. C64 scheduling is on."), 0, 32},
	{"HatchingTime", GD_TYPE_INT, 0, N_("   Hatching time (seconds)"), CAVE_OFFSET(hatching_delay_time), 1, N_("This value sets how much the cave will move until the player enters the cave. This is used for the C64-like schedulings."), 1, 40},
	{"FrameTime", GD_TYPE_INT, GD_DONT_SAVE, N_("   Speed (ms)"), CAVE_OFFSET(level_speed[0]), 5, N_("Number of milliseconds between game frames. Used when milliseconds-based timing is active, ie. C64 scheduling is off."), 50, 500},
	{"HatchingDelay", GD_TYPE_INT, 0, N_("   Hatching delay (frames)"), CAVE_OFFSET(hatching_delay_frame), 1, N_("This value sets how much the cave will move until the player enters the cave. This is used for the milliseconds-based scheduling."), 1, 40},
	{"", GD_LABEL, 0, N_("<b>Elements</b>")},
	{"RandSeed", GD_TYPE_INT, 0, N_("Random seed value"), CAVE_OFFSET(level_rand[0]), 5, N_("Random seed value controls the predictable random number generator, which fills the cave initially. If set to -1, cave is totally random every time it is played."), -1, 255},

	/* initial fill */
	{"InitialBorder", GD_TYPE_ELEMENT, GD_DONT_SHOW_IN_EDITOR, NULL /* Initial border */, CAVE_OFFSET(initial_border), 1, NULL},
	{"InitialFill", GD_TYPE_ELEMENT, GD_DONT_SHOW_IN_EDITOR, NULL /* Initial fill */, CAVE_OFFSET(initial_fill), 1, NULL},
	{"RandomFill", GD_TYPE_ELEMENT, GD_DONT_SHOW_IN_EDITOR, NULL /* Random fill 1 */, CAVE_OFFSET(random_fill[0]), 1, NULL},
	{"RandomFill", GD_TYPE_INT, GD_DONT_SHOW_IN_EDITOR, NULL /* Probability 1 */, CAVE_OFFSET(random_fill_probability[0]), 1, NULL, 0, 255},
	{"RandomFill", GD_TYPE_ELEMENT, GD_DONT_SHOW_IN_EDITOR, NULL /* Random fill 2 */, CAVE_OFFSET(random_fill[1]), 1, NULL},
	{"RandomFill", GD_TYPE_INT, GD_DONT_SHOW_IN_EDITOR, NULL /* Probability 2 */, CAVE_OFFSET(random_fill_probability[1]), 1, NULL, 0, 255},
	{"RandomFill", GD_TYPE_ELEMENT, GD_DONT_SHOW_IN_EDITOR, NULL /* Random fill 3 */, CAVE_OFFSET(random_fill[2]), 1, NULL},
	{"RandomFill", GD_TYPE_INT, GD_DONT_SHOW_IN_EDITOR, NULL /* Probability 3 */, CAVE_OFFSET(random_fill_probability[2]), 1, NULL, 0, 255},
	{"RandomFill", GD_TYPE_ELEMENT, GD_DONT_SHOW_IN_EDITOR, NULL /* Random fill 4 */, CAVE_OFFSET(random_fill[3]), 1, NULL},
	{"RandomFill", GD_TYPE_INT, GD_DONT_SHOW_IN_EDITOR, NULL /* Probability 4 */, CAVE_OFFSET(random_fill_probability[3]), 1, NULL, 0, 255},

	/* PLAYER */
	{"", GD_TAB, 0, N_("Player")},
	/* player */
	{"", GD_LABEL, 0, N_("<b>Player movements</b>")},
	{"DiagonalMovement", GD_TYPE_BOOLEAN, 0, N_("Diagonal movements"), CAVE_OFFSET(diagonal_movements), 1, N_("Controls if the player can move diagonally.")},
	{"ActiveGuyIsFirst", GD_TYPE_BOOLEAN, 0, N_("Uppermost player active"), CAVE_OFFSET(active_is_first_found), 1, N_("In 1stB, cave is scrolled to the uppermost and leftmost player found, whereas in the original game to the last one. Chasing stones also follow the active player.")},
	{"SnapEffect", GD_TYPE_ELEMENT, 0, N_("Snap element"), CAVE_OFFSET(snap_element), 1, N_("Snapping (pressing fire while moving) usually creates space, but it can create any other element.")},
	{"PushingBoulderProb", GD_TYPE_PROBABILITY, 0, N_("Probability of pushing stone (%)"), CAVE_OFFSET(pushing_stone_prob), 1, N_("Chance of player managing to push a stone, every game cycle he tries. This is the normal probability.")},
	{"PushingBoulderProb", GD_TYPE_PROBABILITY, 0, N_("  With sweet (%)"), CAVE_OFFSET(pushing_stone_prob_sweet), 1, N_("Chance of player managing to push a stone, every game cycle he tries. This is used after eating sweet.")},
	{"", GD_LABEL, 0, N_("<b>Clock</b>")},
	{"BonusTime", GD_TYPE_INT, 0, N_("Time bonus for clock (s)"), CAVE_OFFSET(bonus_time), 1, N_("Bonus time when a clock is collected."), 0, 100},
	{"", GD_LABEL, 0, N_("<b>Pneumatic hammer</b>")},
	{"PneumaticHammer.frames", GD_TYPE_INT, 0, N_("Time for hammer (frames)"), CAVE_OFFSET(pneumatic_hammer_frame), 1, N_("This is the number of game frames, a pneumatic hammer is required to break a wall."), 1, 100},
	{"PneumaticHammer.wallsreappear", GD_TYPE_BOOLEAN, 0, N_("Hammered walls reappear"), CAVE_OFFSET(hammered_walls_reappear), 1, N_("If this is set to true, walls broken with a pneumatic hammer will reappear later.")},
	{"PneumaticHammer.wallsreappearframes", GD_TYPE_INT, 0, N_("   Timer for reappear (frames)"), CAVE_OFFSET(hammered_wall_reappear_frame), 1, N_("This sets the number of game frames, after hammered walls reappear, when the above setting is true."), 1, 200},
	/* voodoo */
	{"", GD_LABEL, 0, N_("<b>Voodoo Doll</b>")},
	{"DummyProperties.diamondcollector", GD_TYPE_BOOLEAN, 0, N_("Can collect diamonds"), CAVE_OFFSET(voodoo_collects_diamonds), 1, N_("Controls if a voodoo doll can collect diamonds for the player.")},
	{"DummyProperties.destructable", GD_TYPE_BOOLEAN, 0, N_("Can be destroyed by explosion"), CAVE_OFFSET(voodoo_can_be_destroyed), 1, N_("Controls if the voodoo can be destroyed by an explosion nearby. If not, it is converted to a gravestone, and you get a time penalty.")},
	{"DummyProperties.penalty", GD_TYPE_BOOLEAN, 0, N_("Dies if hit by a stone"), CAVE_OFFSET(voodoo_dies_by_stone), 1, N_("Controls if the voodoo doll dies if it is hit by a stone. Then the player gets a time penalty.")},
	{"PenaltyTime", GD_TYPE_INT, 0, N_("Time penalty (s)"), CAVE_OFFSET(penalty_time), 1, N_("Penalty time when the voodoo is destroyed by a stone."), 0, 100},

	/* ACTIVE 1 */
	{"", GD_TAB, 0, N_("Active elements")},
	/* magic wall */
	{"", GD_LABEL, 0, N_("<b>Magic Wall</b>")},
	{"MagicWallTime", GD_TYPE_INT, 0, N_("Milling time (s)"), CAVE_OFFSET(magic_wall_milling_time), 1, N_("Magic wall will stop after this time, and it cannot be activated again."), 0, 600},
	{"MagicWallProperties", GD_TYPE_ELEMENT, 0, N_("Converts diamond to"), CAVE_OFFSET(magic_diamond_to), 1, N_("As a special effect, magic walls can convert diamonds to any other element.")},
	{"MagicWallProperties", GD_TYPE_ELEMENT, 0, N_("Converts stone to"), CAVE_OFFSET(magic_stone_to), 1, N_("As a special effect, magic walls can convert stones to any other element.")},
	{"MagicWallProperties.convertamoeba", GD_TYPE_BOOLEAN, 0, N_("Stops amoeba"), CAVE_OFFSET(magic_wall_stops_amoeba), 1, N_("When the magic wall is activated, it can convert amoeba into diamonds.")},
	{"MagicWallProperties.waitforhatching", GD_TYPE_BOOLEAN, 0, N_("Timer waits for hatching"), CAVE_OFFSET(magic_timer_wait_for_hatching), 1, N_("This determines if the magic wall timer starts before the player appearing. Magic can always be activated before that; but if this is set to true, the timer will not start.")},
	/* amoeba */
	{"", GD_LABEL, 0, N_("<b>Amoeba</b>")},
	{"AmoebaThreshold", GD_TYPE_RATIO, 0, N_("Threshold (cells)"), CAVE_OFFSET(amoeba_threshold), 1, N_("If the amoeba grows more than this fraction of the cave, it is considered too big."), 0, 16383},
	{"AmoebaTime", GD_TYPE_INT, 0, N_("Slow growth time (s)"), CAVE_OFFSET(amoeba_slow_growth_time), 1, N_("After this time, amoeba will grow very quickly."), 0, 600},
	{"AmoebaProperties.immediately", GD_TYPE_BOOLEAN, 0, N_("Timer started immediately"), CAVE_OFFSET(amoeba_timer_started_immediately), 1, N_("If this flag is enabled, the amoeba slow growth timer will start at the beginning of the cave, regardless of the amoeba being let free or not.")},
	{"AmoebaProperties.waitforhatching", GD_TYPE_BOOLEAN, 0, N_("Timer waits for hatching"), CAVE_OFFSET(amoeba_timer_wait_for_hatching), 1, N_("This determines if the amoeba timer starts before the player appearing. Amoeba can always be activated before that; but if this is set to true, the timer will not start.")},
	{"AmoebaGrowthProb", GD_TYPE_PROBABILITY, 0, N_("Growth ratio, slow (%)"), CAVE_OFFSET(amoeba_growth_prob), 1, N_("This sets the speed at which a slow amoeba grows.")},
	{"AmoebaGrowthProb", GD_TYPE_PROBABILITY, 0, N_("Growth ratio, fast (%)"), CAVE_OFFSET(amoeba_fast_growth_prob), 1, N_("This sets the speed at which a fast amoeba grows.")},
	{"AmoebaProperties", GD_TYPE_ELEMENT, 0, N_("If too big, converts to"), CAVE_OFFSET(too_big_amoeba_to), 1, N_("Controls which element an overgrown amoeba converts to.")},
	{"AmoebaProperties", GD_TYPE_ELEMENT, 0, N_("If enclosed, converts to"), CAVE_OFFSET(enclosed_amoeba_to), 1, N_("Controls which element an enclosed amoeba converts to.")},
	/* water */
	{"", GD_LABEL, 0, N_("<b>Water</b>")},
	{"WaterProperties.doesnotflowdown", GD_TYPE_BOOLEAN, 0, N_("Does not flow downwards"), CAVE_OFFSET(water_does_not_flow_down), 1, N_("In CrDr, the water element had the odd property that it did not flow downwards, only in other directions. This flag emulates this behaviour.")},

	/* ACTIVE 2 */
	{"", GD_TAB, 0, N_("More elements")},
	/* slime */
	{"", GD_LABEL, 0, N_("<b>Slime</b>")},
	{"", GD_TYPE_BOOLEAN, GD_DONT_SAVE, N_("Predictable"), CAVE_OFFSET(slime_predictable), 1, N_("Controls if the predictable random generator is used for slime. It is required for compatibility with some older caves.")},
	{"SlimePermeabilityC64", GD_TYPE_INT, GD_DONT_SAVE, N_("Permeability (predictable, bit pattern)"), CAVE_OFFSET(slime_permeability_c64), 1, N_("This controls the rate at which elements go through the slime. This one is for predictable slime, and the value is used for a bitwise AND function."), 0, 255},
	{"SlimePermeability", GD_TYPE_PROBABILITY, GD_DONT_SAVE, N_("Permeability (unpredictable, %)"), CAVE_OFFSET(slime_permeability), 1, N_("This controls the rate at which elements go through the slime. Higher values represent higher probability of passing. This one is for unpredictable slime.")},
	{"SlimeProperties", GD_TYPE_ELEMENT, 0, N_("Eats this and converts to"), CAVE_OFFSET(slime_eats_1), 1, N_("Slime can let other elements than stone and diamond go through. It always lets a waiting or a chasing stone pass, though.")},
	{"SlimeProperties", GD_TYPE_ELEMENT, 0, N_("Eats this and converts to"), CAVE_OFFSET(slime_converts_1), 1, N_("Slime can let other elements than stone and diamond go through. It always lets a waiting or a chasing stone pass, though.")},
	{"SlimeProperties", GD_TYPE_ELEMENT, 0, N_("Eats this and converts to"), CAVE_OFFSET(slime_eats_2), 1, N_("Slime can let other elements than stone and diamond go through. It always lets a waiting or a chasing stone pass, though.")},
	{"SlimeProperties", GD_TYPE_ELEMENT, 0, N_("Eats this and converts to"), CAVE_OFFSET(slime_converts_2), 1, N_("Slime can let other elements than stone and diamond go through. It always lets a waiting or a chasing stone pass, though.")},

	/* acid */
	{"", GD_LABEL, 0, N_("<b>Acid</b>")},
	{"AcidProperties", GD_TYPE_ELEMENT, 0, N_("Eats this element"), CAVE_OFFSET(acid_eats_this), 1, N_("The element which acid eats. If it cannot find any, it simply disappears.")},
	{"AcidProperties", GD_TYPE_PROBABILITY, 0, N_("Spread ratio (%)"), CAVE_OFFSET(acid_spread_ratio), 1, N_("The probability at which an acid will explode and eat neighbouring elements.")},
	{"ACIDEffect", GD_TYPE_EFFECT, 0, N_("Turns to this when spreading"), CAVE_OFFSET(acid_turns_to), 1, N_("If acid converts to explosion on spreading or not.")},

	/* biter */
	{"", GD_LABEL, 0, N_("<b>Biter</b>")},
	{"BiterProperties", GD_TYPE_INT, 0, N_("Delay (frame)"), CAVE_OFFSET(biter_delay_frame), 1, N_("Number of frames biters wait between movements."), 0, 3},
	{"BiterProperties", GD_TYPE_ELEMENT, 0, N_("Eats this"), CAVE_OFFSET(biter_eat), 1, N_("Biters eat this element. (They always eat dirt.)")},

	/* bladder */
	{"", GD_LABEL, 0, N_("<b>Bladder</b>")},
	{"BladderProperties", GD_TYPE_ELEMENT, 0, N_("Converts to clock by touching"), CAVE_OFFSET(bladder_converts_by), 1, NULL},

	/* SOUND */
	{"", GD_TAB, 0, N_("Sound")},
	{"AmoebaProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Amoeba"), CAVE_OFFSET(amoeba_sound), 1, N_("Controls if the living amoeba has sound or not.")},
	{"MagicWallProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Magic wall"), CAVE_OFFSET(magic_wall_sound), 1, N_("If true, the activated magic wall will have sound.")},
	{"SlimeProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Slime"), CAVE_OFFSET(slime_sound), 1, N_("If true, the elements passing slime will have sound.")},
	{"AcidProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Acid"), CAVE_OFFSET(acid_spread_sound), 1, N_("If true, the acid spreading will have sound.")},
	{"BiterProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Biter"), CAVE_OFFSET(biter_sound), 1, N_("Biters eating something or pushing a stone will have sound.")},
	{"BladderProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Bladder"), CAVE_OFFSET(bladder_sound), 1, N_("Bladders moving and being pushed can have sound.")},
	{"WaterProperties.sound", GD_TYPE_BOOLEAN, 0, N_("Water"), CAVE_OFFSET(water_sound), 1, N_("If true, the cave containing water will have sound.")},

	/* EFFECTS */
	{"", GD_TAB, 0, N_("Effects")},
	/* creature effects */
	{"", GD_LABEL, 0, N_("<b>Creature effects</b>")},
	{"EnemyDirectionProperties.startbackwards", GD_TYPE_BOOLEAN, 0, N_("Start backwards"), CAVE_OFFSET(creatures_backwards), 1, NULL},
	{"EnemyDirectionProperties.time", GD_TYPE_INT, 0, N_("Automatically turn (s)"), CAVE_OFFSET(creatures_direction_auto_change_time), 1, N_("If this is greater than zero, creatures will automatically change direction in every x seconds."), 0, 999},
	{"EnemyDirectionProperties.changeathatching", GD_TYPE_BOOLEAN, 0, N_("Automatically turn on start"), CAVE_OFFSET(creatures_direction_auto_change_on_start), 1, N_("If this is set to true, creatures also turn at the start signal. If false, the first change in direction occurs only later.")},
	/* cave effects */
	{"", GD_LABEL, 0, N_("<b>Cave effects</b>")},
	{"EXPLOSIONEffect", GD_TYPE_EFFECT, 0, N_("Explosions convert to"), CAVE_OFFSET(explosion_to), 1, N_("This element appears in places where an explosion happens.")},
	{"DIAMONDBIRTHEffect", GD_TYPE_EFFECT, 0, N_("Diamond births convert to"), CAVE_OFFSET(diamond_birth_to), 1, NULL},
	{"BOMBEXPLOSIONeffect", GD_TYPE_EFFECT, 0, N_("Bombs explode to"), CAVE_OFFSET(bomb_explode_to), 1, NULL},
	{"BOULDERfallingeffect", GD_TYPE_EFFECT, 0, N_("Falling stones convert to"), CAVE_OFFSET(falling_stone_to), 1, N_("When a stone begins falling, it converts to this element.")},
	{"BOULDERbouncingeffect", GD_TYPE_EFFECT, 0, N_("Bouncing stones convert to"), CAVE_OFFSET(bouncing_stone_to), 1, N_("When a stone stops falling and rolling, it converts to this element.")},
	{"DIAMONDfallingeffect", GD_TYPE_EFFECT, 0, N_("Falling diamonds convert to"), CAVE_OFFSET(falling_diamond_to), 1, N_("When a diamond begins falling, it converts to this element.")},
	{"DIAMONDbouncingeffect", GD_TYPE_EFFECT, 0, N_("Bouncing diamonds convert to"), CAVE_OFFSET(bouncing_diamond_to), 1, N_("When a diamond stops falling and rolling, it converts to this element.")},
	/* visual effects */
	{"", GD_LABEL, 0, N_("<b>Visual effects</b>")},
	{"EXPANDINGWALLLOOKSLIKEeffect", GD_TYPE_EFFECT, 0, N_("Expanding wall looks like"), CAVE_OFFSET(expanding_wall_looks_like), 1, NULL},
	{"DIRTLOOKSLIKEeffect", GD_TYPE_EFFECT, 0, N_("Dirt looks like"), CAVE_OFFSET(dirt_looks_like), 1, NULL},
	/* gravity */
	{"", GD_LABEL, 0, N_("<b>Gravitation effects</b>")},
	{"Gravitation", GD_TYPE_DIRECTION, 0, N_("Gravitation"), CAVE_OFFSET(gravity), 1, N_("The direction where stones and diamonds fall.")},
	{"SkeletonsForPot", GD_TYPE_INT, 0, N_("Skeletons needed for pot"), CAVE_OFFSET(skeletons_needed_for_pot), 1, N_("The number of skeletons to be collected to be able to use a pot."), 0, 50},
	{"GravitationChangeDelay", GD_TYPE_INT, 0, N_("Gravitation switch delay"), CAVE_OFFSET(gravity_change_time), 1, N_("The gravitation changes after a while using the gravitation switch. This option sets the number of seconds to wait."), 1, 60},

	/* COMPATIBILITY */
	{"", GD_TAB, 0, N_("Compatibility")},
	{"BorderProperties.lineshift", GD_TYPE_BOOLEAN, 0, N_("Line shifting border"), CAVE_OFFSET(lineshift), 1, N_("If this is set to true, the player exiting on either side will appear one row lower or upper on the other side.")},
	{"ShortExplosions", GD_TYPE_BOOLEAN, 0, N_("Short explosions"), CAVE_OFFSET(short_explosions), 1, N_("In 1stB, explosions were longer, took five cave frames to complete, as opposed to four in the original.")},
	{"SkeletonsWorthDiamonds", GD_TYPE_INT, 0, N_("Skeletons worth diamonds"), CAVE_OFFSET(skeletons_worth_diamonds), 1, N_("The number of diamonds each skeleton is worth."), 0, 10},
	{"GravityAffectsAll", GD_TYPE_BOOLEAN, 0, N_("Gravity change affects everything"), CAVE_OFFSET(gravity_affects_all), 1, N_("If this is enabled, changing the gravity will also affect bladders (moving and pushing), bladder spenders, falling walls and waiting stones. Otherwise, those elements behave as gravity was always pointing downwards.")},
	{NULL}
};


GdPropertyDefault gd_cave_defaults_gdash[] = {
	/* default data */
	{CAVE_OFFSET(selectable), TRUE},
	{CAVE_OFFSET(intermission), FALSE},
	{CAVE_OFFSET(intermission_instantlife), FALSE},
	{CAVE_OFFSET(intermission_rewardlife), TRUE},
	{CAVE_OFFSET(w), 40},
	{CAVE_OFFSET(h), 22},
	{CAVE_OFFSET(x1), 0},
	{CAVE_OFFSET(y1), 0},
	{CAVE_OFFSET(x2), 39},
	{CAVE_OFFSET(y2), 21},
	{CAVE_OFFSET(colorb), 0},
	{CAVE_OFFSET(color0), 0},
	{CAVE_OFFSET(color1), 8},
	{CAVE_OFFSET(color2), 11},
	{CAVE_OFFSET(color3), 1},
	{CAVE_OFFSET(color4), 5},
	{CAVE_OFFSET(color5), 6},

	/* difficulty */
	{CAVE_OFFSET(level_diamonds[0]), 10},
	{CAVE_OFFSET(diamond_value), 0},
	{CAVE_OFFSET(extra_diamond_value), 0},
	{CAVE_OFFSET(level_time[0]), 999},
	{CAVE_OFFSET(max_time), 999},
	{CAVE_OFFSET(pal_timing), FALSE},
	{CAVE_OFFSET(level_timevalue[0]), 1},
	{CAVE_OFFSET(scheduling), GD_SCHEDULING_MILLISECONDS},
	{CAVE_OFFSET(level_ckdelay[0]), 0},
	{CAVE_OFFSET(hatching_delay_time), 2},
	{CAVE_OFFSET(level_speed[0]), 200},
	{CAVE_OFFSET(hatching_delay_frame), 21},
	{CAVE_OFFSET(level_rand[0]), 0},

	/* initial fill */
	{CAVE_OFFSET(initial_border), O_STEEL},
	{CAVE_OFFSET(initial_fill), O_DIRT},
	{CAVE_OFFSET(random_fill[0]), O_DIRT},
	{CAVE_OFFSET(random_fill_probability[0]), 0},
	{CAVE_OFFSET(random_fill[1]), O_DIRT},
	{CAVE_OFFSET(random_fill_probability[1]), 0},
	{CAVE_OFFSET(random_fill[2]), O_DIRT},
	{CAVE_OFFSET(random_fill_probability[2]), 0},
	{CAVE_OFFSET(random_fill[3]), O_DIRT},
	{CAVE_OFFSET(random_fill_probability[3]), 0},

	/* PLAYER */
	{CAVE_OFFSET(diagonal_movements), FALSE},
	{CAVE_OFFSET(active_is_first_found), TRUE},
	{CAVE_OFFSET(snap_element), O_SPACE},
	{CAVE_OFFSET(pushing_stone_prob), 125000},
	{CAVE_OFFSET(pushing_stone_prob_sweet), 1000000},
	{CAVE_OFFSET(bonus_time), 30},
	{CAVE_OFFSET(pneumatic_hammer_frame), 5},
	{CAVE_OFFSET(hammered_walls_reappear), FALSE},
	{CAVE_OFFSET(hammered_wall_reappear_frame), 100},
	{CAVE_OFFSET(voodoo_collects_diamonds), FALSE},
	{CAVE_OFFSET(voodoo_can_be_destroyed), TRUE},
	{CAVE_OFFSET(voodoo_dies_by_stone), FALSE},
	{CAVE_OFFSET(penalty_time), 30},

	/* magic wall */
	{CAVE_OFFSET(magic_wall_milling_time), 999},
	{CAVE_OFFSET(magic_diamond_to), O_STONE_F},
	{CAVE_OFFSET(magic_stone_to), O_DIAMOND_F},
	{CAVE_OFFSET(magic_wall_stops_amoeba), TRUE},
	{CAVE_OFFSET(magic_timer_wait_for_hatching), FALSE},
	/* amoeba */
	{CAVE_OFFSET(amoeba_threshold), 200},
	{CAVE_OFFSET(amoeba_growth_prob), 31250},
	{CAVE_OFFSET(amoeba_fast_growth_prob), 250000},
	{CAVE_OFFSET(amoeba_slow_growth_time), 999},
	{CAVE_OFFSET(amoeba_timer_started_immediately), TRUE},
	{CAVE_OFFSET(amoeba_timer_wait_for_hatching), FALSE},
	{CAVE_OFFSET(too_big_amoeba_to), O_STONE},
	{CAVE_OFFSET(enclosed_amoeba_to), O_DIAMOND},
	/* water */
	{CAVE_OFFSET(water_does_not_flow_down), FALSE},

	/* slime */
	{CAVE_OFFSET(slime_predictable), TRUE},
	{CAVE_OFFSET(slime_permeability_c64), 0},
	{CAVE_OFFSET(slime_permeability), 1000000},
	{CAVE_OFFSET(slime_eats_1), O_DIAMOND},
	{CAVE_OFFSET(slime_converts_1), O_DIAMOND_F},
	{CAVE_OFFSET(slime_eats_2), O_STONE},
	{CAVE_OFFSET(slime_converts_2), O_STONE_F},

	/* acid */
	{CAVE_OFFSET(acid_eats_this), O_DIRT},
	{CAVE_OFFSET(acid_spread_ratio), 31250},
	{CAVE_OFFSET(acid_turns_to), O_EXPLODE_3},

	/* biter */
	{CAVE_OFFSET(biter_delay_frame), 0},
	{CAVE_OFFSET(biter_eat), O_DIAMOND},

	/* bladder */
	{CAVE_OFFSET(bladder_converts_by), O_VOODOO},

	/* SOUND */
	{CAVE_OFFSET(amoeba_sound), TRUE},
	{CAVE_OFFSET(magic_wall_sound), TRUE},
	{CAVE_OFFSET(slime_sound), TRUE},
	{CAVE_OFFSET(acid_spread_sound), TRUE},
	{CAVE_OFFSET(biter_sound), TRUE},
	{CAVE_OFFSET(bladder_sound), TRUE},
	{CAVE_OFFSET(water_sound), TRUE},

	/* creature effects */
	{CAVE_OFFSET(creatures_backwards), FALSE},
	{CAVE_OFFSET(creatures_direction_auto_change_time), 0},
	{CAVE_OFFSET(creatures_direction_auto_change_on_start), FALSE},
	/* cave effects */
	{CAVE_OFFSET(explosion_to), O_SPACE},
	{CAVE_OFFSET(diamond_birth_to), O_DIAMOND},
	{CAVE_OFFSET(bomb_explode_to), O_BRICK},
	{CAVE_OFFSET(falling_stone_to), O_STONE_F},
	{CAVE_OFFSET(bouncing_stone_to), O_STONE},
	{CAVE_OFFSET(falling_diamond_to), O_DIAMOND_F},
	{CAVE_OFFSET(bouncing_diamond_to), O_DIAMOND},
	/* visual effects */
	{CAVE_OFFSET(expanding_wall_looks_like), O_BRICK},
	{CAVE_OFFSET(dirt_looks_like), O_DIRT},
	/* gravity */
	{CAVE_OFFSET(gravity), MV_DOWN},
	{CAVE_OFFSET(skeletons_needed_for_pot), 5},
	{CAVE_OFFSET(gravity_change_time), 10},

	/* COMPATIBILITY */
	{CAVE_OFFSET(lineshift), FALSE},
	{CAVE_OFFSET(short_explosions), TRUE},
	{CAVE_OFFSET(skeletons_worth_diamonds), 0},
	{CAVE_OFFSET(gravity_affects_all), TRUE},
	{-1},
};




GdC64Color gd_c64_colors[16]= {
#if 0
	{ "Black", 0x000000 },
	{ "White", 0xfcfcfc },
	{ "Red", 0xa80000 },
	{ "Cyan", 0x54fcfc },
	{ "Purple", 0xa800a8 },
	{ "Green", 0x00a800 },
	{ "Blue", 0x0000a8 },
	{ "Yellow", 0xfcfc00 },
	{ "Orange", 0xa85400 },
	{ "Brown", 0x802c00 },
	{ "LightRed", 0xfc5454 },
	{ "Gray1", 0x545454 },
	{ "Gray2", 0x808080 },
	{ "LightGreen", 0x54fc54 },
	{ "LightBlue", 0x5454fc },
	{ "Gray3", 0xa8a8a8 }
#endif

    /* vice new luminances */
	{ "Black", 0x000000 },
	{ "White", 0xffffff },
	{ "Red", 0x894036 },
	{ "Cyan", 0x7abfc7 },
	{ "Purple", 0x8a46ae },
	{ "Green", 0x68a941 },
	{ "Blue", 0x3e31a2 },
	{ "Yellow", 0xd0dc71 },
	{ "Orange", 0x905f25 },
	{ "Brown", 0x5c4700 },
	{ "LightRed", 0xbb776d },
	{ "Gray1", 0x555555 },
	{ "Gray2", 0x808080 },
	{ "LightGreen", 0xacea88 },
	{ "LightBlue", 0x7c70da },
	{ "Gray3", 0xababab }
};





void
gd_cave_db_init()
{
	int i;
	gboolean cell_used[NUM_OF_CELLS];
	GHashTable *pointers;
	
	for (i=0; i<NUM_OF_CELLS; i++)
		cell_used[i]=FALSE;
		
	/* check element database for faults. */
	for (i=0; gd_elements[i].element!=-1; i++) {
		int j, m;
		
		if (gd_elements[i].element!=i)
			g_critical ("element: i:0x%x!=0x%x", i, gd_elements[i].element);
		/* if it has a name, create a lowercase name (of the translated one). will be used by the editor */
		if (gd_elements[i].name)
			/* the function allocates a new string, but it is needed as long as the app is running */
			gd_elements[i].lowercase_name=g_utf8_strdown(gettext(gd_elements[i].name), -1);
		
		/* we do not like generated pixbufs for games. only those that are in the png. */
		if (ABS(gd_elements[i].image_game)>NUM_OF_CELLS_X*NUM_OF_CELLS_Y)
			g_critical ("game pixbuf for element %x (%s) bigger than png size", i, gd_elements[i].name);
	
		if (gd_elements[i].image<0)
			g_critical ("editor pixbuf for element %x (%s) should not be animated", i, gd_elements[i].name);
			
		m=gd_elements[i].image<0?8:1;
		for (j=0; j<m; j++)
			cell_used[ABS(gd_elements[i].image)+j]=TRUE;
		m=gd_elements[i].image_simple<0?8:1;
		for (j=0; j<m; j++)
			cell_used[ABS(gd_elements[i].image_simple)+j]=TRUE;
		m=gd_elements[i].image_game<0?8:1;
		for (j=0; j<m; j++)
			cell_used[ABS(gd_elements[i].image_game)+j]=TRUE;
	}

	/* uncomment this, to print free indexes in cells array */
	/*
	g_print("Free pixbuf indexes: ");
	for (i=NUM_OF_CELLS_X*NUM_OF_CELLS_Y; i<NUM_OF_CELLS; i++) {
		if (!cell_used[i])
			g_print("%d ", i);
	}
	g_print("\n");
	*/
	
	/* uncomment this, to show free element->character characters. */
	/*
	gd_create_char_to_element_table();
	g_print("Free characters: ");
	for (i=32; i<128; i++)
		if (gd_char_to_element[i]==O_UNKNOWN)
			g_print("%c", i);
	g_print("\n");
	*/
	
	/* check the cave property database for faults. */
	pointers=g_hash_table_new(g_direct_hash, g_direct_equal);
	for (i=0; gd_cave_properties[i].identifier!=NULL; i++) {
		GdType type=gd_cave_properties[i].type;
	
		switch (type) {
			case GD_LABEL:
			case GD_TAB:
			case GD_LEVEL_LABEL:
				/* some lines are used for the user interface. these should not have an identifier. */
				if (strcmp(gd_cave_properties[i].identifier, "")!=0) {
					g_critical ("ui lines in cave properties should not have identifiers: %s", gd_cave_properties[i].identifier);
					g_assert_not_reached();
				}
				break;
				
			case GD_TYPE_STRING:
				/* check if any of the properties are designated as string arrays. they are not supported in
				 * file read/write and operations, also they do not even make any sense! */
				if (gd_cave_properties[i].count!=1) {
					g_critical ("string arrays not supported in cave properties: %s", gd_cave_properties[i].identifier);
					g_assert_not_reached();
				}
				break;
				
			case GD_TYPE_EFFECT:
				/* the same applies for effects. */
				if (gd_cave_properties[i].count!=1) {
					g_critical ("effect arrays not supported in cave properties: %s", gd_cave_properties[i].identifier);
					g_assert_not_reached();
				}
				break;

			default:
				break;
		}
		
		if (type!=GD_LABEL && type!=GD_TAB && type!=GD_LEVEL_LABEL) {
			const char *another_prop;
			
			/* other types */
			/* check if its pointer is not the same as another one's */
			/* +1 is added so it is never zero */
			if (!(gd_cave_properties[i].flags&GD_DONT_SAVE) && strcmp(gd_cave_properties[i].identifier, "")==0) {
				g_critical ("property should have a bdcff identifier: line %d, name %s", i, gd_cave_properties[i].name);
				g_assert_not_reached();
			}
			another_prop=g_hash_table_lookup(pointers, GINT_TO_POINTER(gd_cave_properties[i].offset+1));
			if (another_prop!=NULL) {
				g_critical("property %s has the same pointer as property %s", gd_cave_properties[i].identifier, another_prop);
				g_assert_not_reached();
			} else
				/* value is the identifier, so we can report the OLD one if the check fails */
				g_hash_table_insert(pointers, GINT_TO_POINTER(gd_cave_properties[i].offset+1), gd_cave_properties[i].identifier);
		}
	}
	g_hash_table_destroy(pointers);
}