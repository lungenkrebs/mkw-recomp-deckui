// The prompts of the native "Steam Deck" button style (glyphs.c, GLYPHS_DECK): Xelu's free controller
// prompts for the Steam Deck, packed into the game's glyph cell grid (1024x1024, cells 104x104 at 105,
// rows bottom-up as PicFont stores them).
//
// Xelu's Free Controller & Key Prompts are CC0 (public domain):
// https://thoseawesomeguys.com/prompts/ -- the Steam Deck set, embedded as deck_sheet.png. The
// runtime blits these cells instead of drawing white badges, so the style matches the RomFS mods.
#include <stddef.h>
#include <stdint.h>

// stb_image static, PNG only: the launcher's mods_browse.cpp already has an implementation of its own
// (C++ linkage), and the runtime needs no other format.
#define STB_IMAGE_STATIC
#define STBI_ONLY_PNG
#define STBI_NO_STDIO
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#include "third_party/stb/stb_image.h"
#pragma clang diagnostic pop

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc23-extensions"   // #embed in C11
// Relative to this file: #embed does not search the -I directories.
static const unsigned char deck_png[] = {
#embed "deck_sheet.png"
};
#pragma clang diagnostic pop

const uint8_t *glyph_deck_sheet(void) {
    static uint8_t *rgba;
    static int state;   // 0: not tried, 1: decoded, -1: failed (the style then draws its badges)
    if (!state) {
        int w = 0, h = 0, n = 0;
        rgba = stbi_load_from_memory(deck_png, (int)sizeof deck_png, &w, &h, &n, 4);
        state = rgba && w == 1024 && h == 1024 ? 1 : -1;
        if (state < 0) {
            stbi_image_free(rgba);
            rgba = NULL;
        }
    }
    return rgba;
}
