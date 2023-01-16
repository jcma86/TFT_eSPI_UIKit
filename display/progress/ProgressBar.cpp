#include "ProgressBar.hpp"

ProgressBar::ProgressBar(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
  _shouldRedraw = true;
}

void ProgressBar::hidePercent(bool hidePercent)
{
  _hidePercent = hidePercent;
  _shouldRedraw = true;
}

void ProgressBar::setRange(float min, float max)
{
  _min = min < max ? min : max;
  _max = max > min ? max : min;
  _shouldRedraw = true;
}

void ProgressBar::setValue(float value)
{
  _value = value > _max ? _max : value;
  _value = value < _min ? _min : value;
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

  float percentVal = (100.0 / (_max - _min) * (_value - _min));
  int16_t fillTo = (percentVal * (_w - 2)) / 100.0;

  _tft->drawRect(_x, _y, _w, _h, _borderColor);
  _tft->fillRectHGradient(_x + 1, _y + 1, fillTo, _h - 2, _startColor, _endColor);

  if (!_hidePercent)
  {
    char percent[10];
    snprintf(percent, 10, "%.1f %%", percentVal);

    if (!_lblPercent.isReady())
    {
      _lblPercent = Label(_tft, "PB_Percent");
      _lblPercent.setParentViewport(_vX, _vY, _vW, _vH);
    }

    _lblPercent.setFont(_font);
    _lblPercent.setFontColor(_fontColor);
    _lblPercent.setPosition(_x + (_w / 2), _y + (_h / 2) + 2);
    _lblPercent.setDatum(MC_DATUM);
    _lblPercent.setLabel(percent);

    _lblPercent.draw();
  }

  _shouldRedraw = false;
}
