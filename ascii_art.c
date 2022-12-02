#include "ascii_art.h"

#define LOGO_HEIGHT 7

static const char* logo_buffer [] = {
    "                                                      \n",
    "               ,--.      ,--.                         \n",
    " ,---. ,--.,--.`--' ,---.|  |,-.,-----. ,---.  ,---.  \n",
    "| .-. ||  ||  |,--.| .--'|     /'-----'| .-. |(  .-'  \n",
    "' '-' |'  ''  '|  |\\ `--.|  \\  \\       ' '-' '.-'  `) \n",
    " `-|  | `----' `--' `---'`--'`--'       `---' `----'  \n",
    "   `--'                                               \n"
};

static const int logo_colors [] = {
    VGA_COLOR_WHITE,
    VGA_COLOR_WHITE,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_GREEN
};

void render_logo()
{
    for (size_t i = 0; i < LOGO_HEIGHT; i++) {
        terminal_setcolor(logo_colors[i]);
        terminal_writestring(logo_buffer[i]);
    }
}