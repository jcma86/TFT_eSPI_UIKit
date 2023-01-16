#include "DigitalMeter.hpp"

DigitalMeter::DigitalMeter(TFT_eSPI *tft, const char *id) : MeterBase(tft, id)
{
  strcpy(_units, "");
  _isReady = true;
}

void DigitalMeter::setFontColor(COLOR color)
{
  _color = color;
  _shouldRedraw = true;
}

void DigitalMeter::setDatum(int datum)
{
  _datum = datum;
  _shouldRedraw = true;
}

void DigitalMeter::updateState()
{
  if (!_isReady)
    return;

  draw();
}

void DigitalMeter::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw || _valChanged;
  if (!_isReady || !force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  char value[10];
  snprintf(value, 10, "%.1lf %s", _value, _units);

  _tft->fillRect(_x - _prevWidth, _y, _prevWidth, 35, SCREEN_BACKGROUND_COLOR);
  _tft->loadFont(DIGITAL_METER_FONT_FAMILY);
  _tft->setTextSize(DIGITAL_METER_FONT_SIZE);
  _tft->setTextColor(_color);
  _tft->setTextDatum(_datum);
  _tft->drawString(value, _x, _y);

  _prevWidth = _tft->textWidth(value);
  _tft->unloadFont();

  _shouldRedraw = false;
  _valChanged = false;
}