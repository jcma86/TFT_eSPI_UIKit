#include "MeterBase.hpp"

void MeterBase::setRange(float min, float max)
{
  _range.min = min;
  _range.max = max;

  _shouldRedraw = true;
}

void MeterBase::clearRangeColors()
{
  _rangeColors.clear();

  _shouldRedraw = true;
}

void MeterBase::setRangeColors(std::map<COLOR, MeterRange> &rangeColors)
{
  _rangeColors.clear();
  for (std::pair<COLOR, MeterRange> element : rangeColors)
    _rangeColors.insert(std::pair<COLOR, MeterRange>(element.first, element.second));

  _shouldRedraw = true;
}

void MeterBase::addRangeColor(std::pair<COLOR, MeterRange> rangeColor)
{
  _rangeColors.insert(std::pair<COLOR, MeterRange>(rangeColor.first, rangeColor.second));
  _shouldRedraw = true;
}

void MeterBase::setUnits(const char *units)
{
  strcpy(_units, units);
  _shouldRedraw = true;
}

void MeterBase::setTitle(const char *title)
{
  strcpy(_title, title);
  _shouldRedraw = true;
}

void MeterBase::setPosition(uint16_t x, uint16_t y)
{
  _x = x;
  _y = y;
  _shouldRedraw = true;
}

void MeterBase::setValue(float value)
{
  _prevValue = _value;
  _value = value;

  if (_prevValue != _value)
    _valChanged = true;
}
