#ifndef __UIKIT_DISPLAY_METER_DIGITAL__
#define __UIKIT_DISPLAY_METER_DIGITAL__

#include "../MeterBase.hpp"

class DigitalMeter : public MeterBase
{
private:
  COLOR _color = DIGITAL_METER_FONT_COLOR;
  int _datum = TR_DATUM;
  int16_t _prevWidth = 80;

public:
  DigitalMeter() {}
  DigitalMeter(TFT_eSPI *tft, const char *id);

  void setFontColor(COLOR color = DIGITAL_METER_FONT_COLOR);
  void setDatum(int datum = TR_DATUM);
  void updateState();
  void draw(bool forceRedraw = false);
};

#endif
