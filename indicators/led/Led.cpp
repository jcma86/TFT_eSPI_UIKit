#include "Led.hpp"

Led::Led(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
  _shouldRedraw = true;
}

void Led::turnOn()
{
  _state = true;
  _shouldRedraw = true;
}

void Led::turnOff()
{
  _state = false;
  _shouldRedraw = true;
}

void Led::setState(bool isOn)
{
  _state = isOn;
  _shouldRedraw = true;
}

void Led::setColor(COLOR on, COLOR off)
{
  _color = on;
  _colorOff = off;
  _shouldRedraw = true;
}

void Led::updateState()
{
  if (!_isReady)
    return;
}

void Led::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!_isReady || !force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);
  _tft->drawCircle(_x, _y, _w, COLOR_BLACK);
  _tft->fillCircle(_x, _y, _w - 1, _state ? _color : _colorOff);

  _shouldRedraw = false;
}
