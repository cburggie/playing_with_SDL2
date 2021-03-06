#include <cburggie.h>
#include <string>

const char * cburggie::constants::window_title = "Playing With SDL2!";
#ifdef WIN32
const char * cburggie::constants::font_path = "c:\\windows\\fonts\\DejaVuSansMono.ttf";
#else
const char * cburggie::constants::font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#endif

const int cburggie::constants::min_window_width = 100;
const int cburggie::constants::window_width = 640;
const int cburggie::constants::min_window_height = 100;
const int cburggie::constants::window_height = 400;
