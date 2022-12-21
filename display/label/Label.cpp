#include "Label.hpp"

Label::Label(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  strcpy(_label, "");
  _shouldRedraw = true;
  _isReady = true;
}

void Label::setColor(COLOR color)
{
  _color = color;
  _shouldRedraw = true;
}

void Label::setFont(const uint8_t font[])
{
  _font = (uint8_t *)font;
  _isFreeFont = false;
  _shouldRedraw = true;
}

void Label::setFont(const GFXfont *font)
{
  _fFont = (GFXfont *)font;
  _isFreeFont = true;
  _shouldRedraw = true;
}

void Label::clearWithColor(COLOR color)
{
  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  _tft->loadFont(LABEL_FONT_FAMILY);
  _tft->setTextSize(BUTTON_FONT_SIZE);
  uint16_t tw = _tft->textWidth(_label);
  uint16_t th = _tft->fontHeight() - 2;
  _tft->unloadFont();

  int x = _x;
  int y = _y;
  if (_datum >= 3 && _datum < 6)
    y = _y - (th / 2 + (th % 2 != 0 ? 1 : 0));
  if (_datum >= 6)
    y = _y - th;

  if (_datum == 1 || _datum == 3 || _datum == 4 || _datum == 7)
    x = _x - (tw / 2);
  if (_datum == 2 || _datum == 5 || _datum == 8 || _datum == 11)
    x = _x - tw;

  y = y < 0 ? 0 : y;
  x = x < 0 ? 0 : x;

  th = _y + th > _vH ? _vH : th;
  tw = _x + tw > _vW ? _vW : tw;

  _tft->fillRect(x, y, tw, th, color);
}

void Label::setLabel(const char *label)
{
  strcpy(_label, label);
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

  draw();
}

void Label::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!_isReady || !force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  _tft->setTextSize(BUTTON_FONT_SIZE);
  _tft->setTextColor(_color);
  _tft->setTextDatum(_datum);
  if (_isFreeFont)
  {
    _tft->setFreeFont(_fFont);
    _tft->drawString(_label, _x, _y);
  }
  else
  {
    _tft->loadFont(_font);
    _tft->drawString(_label, _x, _y);
    _tft->unloadFont();
  }

  _shouldRedraw = false;
}