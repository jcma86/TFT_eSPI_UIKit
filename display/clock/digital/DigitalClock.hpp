#ifndef __UIKIT_DISPLAY_CLOCK_DIGITAL__
#define __UIKIT_DISPLAY_CLOCK_DIGITAL__

#include <vector>
#include "../ClockBase.hpp"
#include "../ClockInterface.hpp"
#include "../../label/Label.hpp"
#include "../../../fonts/Fonts.hpp"
#include "../../../helpers/Colors.hpp"

class DigitalClock : public ClockBase
{
private:
  Label _timeLbl;
  char _time[15];
  bool _is12h = false;
  bool _isFreeFont = false;
  bool _showSeconds = false;
  uint8_t _datum = TL_DATUM;
  uint8_t *_font = (uint8_t *)LiberationMonoRegular18;
  GFXfont *_fFont = NULL;
  COLOR _backgroundColor = SCREEN_BACKGROUND_COLOR;
  COLOR _color = COLOR_BLACK;

  void updateClockState();

public:
  DigitalClock() {}
  DigitalClock(TFT_eSPI *tft, const char *id) : ClockBase(tft, id) {}

  void setFont(const uint8_t font[], uint8_t datum);
  void setFont(const GFXfont *font, uint8_t datum);
  void setColors(COLOR font = COLOR_BLACK, COLOR background = SCREEN_BACKGROUND_COLOR);
  void set12HourMode(bool is12h = true);
  void showSeconds(bool showSeconds = true);
  void draw(bool forceRedraw = false);
};

#endif
