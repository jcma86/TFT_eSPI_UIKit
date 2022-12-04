#include "Label.hpp"

Label::Label(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _shouldRedraw = true;
  _isReady = true;
}

void Label::setColor(COLOR color)
{
  _color = color;
  _shouldRedraw = true;
}

void Label::setPosition(int16_t x, uint16_t y, uint8_t datum)
{
  _x = x;
  _y = y;
  _datum = datum;
  _shouldRedraw = true;
}

void Label::updateState()
{
  if (!_isReady)
    return;
}

void Label::draw(const char *label, bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!_isReady || !force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  _tft->loadFont(LABEL_FONT_FAMILY);
  _tft->setTextSize(BUTTON_FONT_SIZE);
  _tft->setTextColor(_color);

  _tft->setTextDatum(_datum);
  _tft->drawString(label, _x, _y);
  _tft->unloadFont();

  _shouldRedraw = false;
}