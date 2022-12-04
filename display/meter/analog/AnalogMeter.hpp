#ifndef __UIKIT_DISPLAY_METER_ANALOG__
#define __UIKIT_DISPLAY_METER_ANALOG__

#include "../MeterBase.hpp"

#define __ANALOG_METER_SHORT_STEP__ 3
#define __ANALOG_METER_LONG_STEP__ 15
#define __ANALOG_METER_INDICATOR_SIZE__ 28

class AnalogMeter : public MeterBase
{
private:
  int _degrees = 120;
  int _prevx0 = 0;
  int _prevy0 = 0;
  int _prevx1 = 0;
  int _prevy1 = 0;

  float valueToDeg(float value);

public:
  AnalogMeter() {}
  AnalogMeter(TFT_eSPI *tft, const char *id);

  void setArcDegrees(int degrees = 120);
  void updateState();
  void draw(bool forceRedraw = false);
};

#endif
