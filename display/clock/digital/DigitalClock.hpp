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
  bool _showSeconds = false;
  COLOR _backgroundColor = SCREEN_BACKGROUND_COLOR;
  COLOR _color = COLOR_BLACK;

  void updateClockState();

public:
  DigitalClock() {}
  DigitalClock(TFT_eSPI *tft, const char *id) : ClockBase(tft, id) {}

  void setColors(COLOR font = COLOR_BLACK, COLOR background = SCREEN_BACKGROUND_COLOR);
  void set12HourMode(bool is12h = true);
  void showSeconds(bool showSeconds = true);
  void draw(bool forceRedraw = false);
};

#endif
