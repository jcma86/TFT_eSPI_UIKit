#include "ProgressBar.hpp"

ProgressBar::ProgressBar(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
  _shouldRedraw = true;
}

void ProgressBar::setValue(float value)
{
  _value = value;
  _shouldRedraw = true;
}

void ProgressBar::setColor(COLOR color)
{
  _startColor = color;
  _endColor = color;
  _shouldRedraw = true;
}

void ProgressBar::setColor(COLOR color, COLOR fontColor)
{
  _startColor = color;
  _endColor = color;
  _fontColor = fontColor;
  _shouldRedraw = true;
}

void ProgressBar::setColor(COLOR color, COLOR fontColor, COLOR borderColor)
{
  _startColor = color;
  _endColor = color;
  _fontColor = fontColor;
  _borderColor = borderColor;
  _shouldRedraw = true;
}

void ProgressBar::setFontColor(COLOR color)
{
  _fontColor = color;
  _shouldRedraw = true;
}

void ProgressBar::setBorderColor(COLOR color)
{
  _borderColor = color;
  _shouldRedraw = true;
}

void ProgressBar::setGradientColor(COLOR start, COLOR end)
{
  _startColor = start;
  _endColor = end;
  _shouldRedraw = true;
}

void ProgressBar::clearCustomColor()
{
  _startColor = PROGRESS_BAR_COLOR_A;
  _endColor = PROGRESS_BAR_COLOR_B;
  _borderColor = PROGRESS_BAR_BORDER_COLOR;
  _fontColor = PROGRESS_BAR_FONT_COLOR;

  _shouldRedraw = true;
}

void ProgressBar::updateState()
{
  if (!_isReady)
    return;

  draw();
}

void ProgressBar::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!_isReady || !force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH, false);

  char percent[7];
  sprintf(percent, "%.1f %%", _value);
  int16_t fillTo = (_value * (_w - 2)) / 100.0;

  _tft->drawRect(_x, _y, _w, _h, _borderColor);
  _tft->fillRectHGradient(_x + 1, _y + 1, fillTo, _h - 2, _startColor, _endColor);

  _tft->loadFont(PROGRESS_BAR_FONT_FAMILY);
  _tft->setTextColor(_fontColor);
  _tft->setTextDatum(MC_DATUM);

  _tft->drawString(percent, _x + (_w / 2), _y + (_h / 2) + 2);

  _tft->unloadFont();

  _shouldRedraw = false;
}
