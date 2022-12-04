#ifndef __UIKIT_HELPERS_COLORS__
#define __UIKIT_HELPERS_COLORS__

#include <inttypes.h>

#define COLOR uint16_t

#define COLOR_WHITE 0xffff      // getColorFromRGB(255,255,255)
#define COLOR_BLACK 0x0         // getColorFromRGB(0,0,0)
#define COLOR_RED 0xf800        // getColorFromRGB(255,0,0)
#define COLOR_YELLOW 0xffe0     // getColorFromRGB(255,255,0)
#define COLOR_GREEN 0x7e0       // getColorFromRGB(0,255,0)
#define COLOR_BLUE 0x1f         // getColorFromRGB(0, 0,255)
#define COLOR_DARK_GRAY 0x29c9  // getColorFromRGB(46, 56, 77)
#define COLOR_LIGHT_GRAY 0x84d5 // getColorFromRGB(135, 152, 173)

#define COLOR_PRIMARY 0xe228         // getColorFromRGB(231, 70, 69)
#define COLOR_PRIMARY_LIGHT 0xfedb   // getColorFromRGB(252, 219, 218)
#define COLOR_SECONDARY 0xfbaa       // getColorFromRGB(251, 119, 86)
#define COLOR_TERTIARY 0xfe6c        // getColorFromRGB(250, 205, 96)
#define COLOR_COMPLEMENTARY_A 0xffcc // getColorFromRGB(253, 250, 102)
#define COLOR_COMPLEMENTARY_B 0x1e18 // getColorFromRGB(26, 192, 198)

static COLOR getColorFromRGB(u_char r, u_char g, u_char b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#endif