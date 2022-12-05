#ifndef __UIKIT_DISPLAY_METER_BASE__
#define __UIKIT_DISPLAY_METER_BASE__

#include <map>
#include "../../base/BaseComponent.hpp"

typedef struct
{
  float min;
  float max;
} MeterRange;

class MeterBase : public BaseComponent
{
protected:
  float _value = 0.0;
  float _prevValue = -1.0;
  bool _valChanged = true;
  char _units[7];
  char _title[20];
  MeterRange _range = {.min = 0.0, .max = 100.0};
  std::map<COLOR, MeterRange> _rangeColors;

public:
  MeterBase() {}
  MeterBase(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id) {}

  void setRange(float minValue = 0.0, float maxVaue = 100.0);
  void setRangeColors(std::map<COLOR, MeterRange> &thresholds);
  void setValue(float value);
  void setUnits(const char *units);
  void setTitle(const char *title);
  void setPosition(uint16_t x, uint16_t y);
  void clearRangeColors();
  void addRangeColor(std::pair<COLOR, MeterRange> threshold);

  virtual void updateState() = 0;
  virtual void draw(bool forceRedraw = false) = 0;
};

#endif
