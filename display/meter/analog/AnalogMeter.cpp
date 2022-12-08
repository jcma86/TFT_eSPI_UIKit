#include "AnalogMeter.hpp"

AnalogMeter::AnalogMeter(TFT_eSPI *tft, const char *id) : MeterBase(tft, id)
{
  // TODO: Find way to adjust meter to custom sizes
  // in the meantime will force a fixed size.
  _w = __ANALOG_METER_WIDTH__;
  _h = __ANALOG_METER_HEIGHT__;
  _degrees = 200;

  strcpy(_units, "");
  _shouldRedraw = true;
  _isReady = true;
}

void AnalogMeter::setArcDegrees(int degrees)
{
  _degrees = degrees;
  _shouldRedraw = true;
}

void AnalogMeter::setMarkSteps(int longStep, int shortStep, int labelStep)
{
  _stepLongMark = longStep;
  _stepShortMark = shortStep;
  _stepLabel = labelStep;

  _shouldRedraw = true;
}

void AnalogMeter::updateState()
{
  if (!_isReady)
    return;

  draw();
}

void AnalogMeter::draw(bool forceRedraw)
{
  if (!_isReady)
    return;

  bool force = _shouldRedraw || forceRedraw;
  if (!force && !_valChanged)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  char minTag[5];
  char maxTag[5];
  _tft->loadFont(ANALOG_METER_UNITS_FONT_FAMILY);
  sprintf(minTag, "%.0f", _range.min);
  sprintf(maxTag, "%.0f", _range.max);
  int tw = _tft->textWidth(strlen(minTag) > strlen(maxTag) ? minTag : maxTag);
  _tft->unloadFont();

  float arcRadius = (_w / 2) - (2 * tw);
  float arcMidPoint = (_degrees / 2);

  uint16_t xCircCenter = _w / 2;
  uint16_t yCircCenter = (_h / 2) + 30;
  if (strlen(_title) > 0)
    yCircCenter += 12;

  if (force)
  {
    _tft->fillRect(_x, _y, _w, _h, ANALOG_METER_BORDER_COLOR);
    _tft->fillRect(_x + 2, _y + 2, _w - 4, _h - 4, ANALOG_METER_BACKGROUND_COLOR);

    if (strlen(_title) > 0)
    {
      _tft->loadFont(ANALOG_METER_TITLE_FONT_FAMILY);
      _tft->setTextSize(ANALOG_METER_FONT_SIZE);
      _tft->setTextColor(ANALOG_METER_TITLE_FONT_COLOR);
      _tft->setTextDatum(MC_DATUM);
      _tft->drawString(_title, _x + (_w / 2), _y + 13);
      _tft->unloadFont();
    }

    _tft->loadFont(ANALOG_METER_FONT_FAMILY);
    _tft->setTextSize(ANALOG_METER_FONT_SIZE);
    _tft->setTextColor(ANALOG_METER_FONT_COLOR);

    int tempRange = _range.max - _range.min;
    // float tempRangeStep = tempRange / (float)(_degrees / __ANALOG_METER_LONG_STEP__);

    int lastMark = 9999999;
    for (int i = -arcMidPoint; i <= arcMidPoint; i += 1)
    {
      int currentMark = map((i + arcMidPoint), 0, _degrees, _range.min, _range.max);

      // Long or short scale tick length
      int tl = 0;
      if (currentMark == lastMark)
        tl = 0;
      else if (currentMark % _stepLongMark == 0)
        tl = 15;
      else if (currentMark % _stepShortMark == 0)
        tl = 8;

      // Coodinates of tick to draw
      uint16_t x0;
      uint16_t y0;
      uint16_t x1;
      uint16_t y1;
      float sx = cos((i - 90) * 0.0174532925);
      float sy = sin((i - 90) * 0.0174532925);

      x0 = _x + (sx * (arcRadius + tl) + xCircCenter);
      y0 = _y + (sy * (arcRadius + tl) + yCircCenter);
      x1 = _x + (sx * arcRadius + xCircCenter);
      y1 = _y + (sy * arcRadius + yCircCenter);

      float sx2 = cos((i + __ANALOG_METER_SHORT_STEP__ - 90) * 0.0174532925);
      float sy2 = sin((i + __ANALOG_METER_SHORT_STEP__ - 90) * 0.0174532925);
      int x2 = _x + (sx2 * (arcRadius + tl) + xCircCenter);
      int y2 = _y + (sy2 * (arcRadius + tl) + yCircCenter);
      int x3 = _x + (sx2 * arcRadius + xCircCenter);
      int y3 = _y + (sy2 * arcRadius + yCircCenter);

      if (_rangeColors.size() > 0)
      {
        int size = 12;
        int length = arcRadius;
        int xColor0 = _x + (sx * (length + size) + xCircCenter);
        int yColor0 = _y + (sy * (length + size) + yCircCenter);
        int xColor1 = _x + (sx * length + xCircCenter);
        int yColor1 = _y + (sy * length + yCircCenter);
        int xColor2 = _x + (sx2 * (length + size) + xCircCenter);
        int yColor2 = _y + (sy2 * (length + size) + yCircCenter);
        int xColor3 = _x + (sx2 * length + xCircCenter);
        int yColor3 = _y + (sy2 * length + yCircCenter);

        for (std::pair<COLOR, MeterRange> element : _rangeColors)
        {
          if (currentMark >= element.second.min && currentMark < element.second.max)
          {
            _tft->fillTriangle(xColor0, yColor0, xColor1, yColor1, xColor2, yColor2, element.first);
            _tft->fillTriangle(xColor1, yColor1, xColor2, yColor2, xColor3, yColor3, element.first);
          }
        }
      }

      // Draw tick
      if (tl != 0)
        _tft->drawLine(x0, y0, x1, y1, ANALOG_METER_ARC_MARK_COLOR);

      // Check if labels should be drawn, with position tweaks
      if (currentMark % _stepLabel == 0 && lastMark != currentMark)
      {
        char valLabel[10];
        sprintf(valLabel, "%d", currentMark);

        // Calculate label positions
        x0 = _x + (sx * (arcRadius + tl + 14) + xCircCenter);
        y0 = _y + (sy * (arcRadius + tl + 14) + yCircCenter);

        _tft->drawCentreString(valLabel, x0, y0 - 6, 2);
      }

      // Now draw the arc of the scale
      sx = cos((i + __ANALOG_METER_SHORT_STEP__ - 90) * 0.0174532925);
      sy = sin((i + __ANALOG_METER_SHORT_STEP__ - 90) * 0.0174532925);
      x0 = _x + (sx * arcRadius + xCircCenter);
      y0 = _y + (sy * arcRadius + yCircCenter);
      // Draw scale arc, don't draw the last part
      if (i < arcMidPoint)
        _tft->drawLine(x0, y0, x1, y1, ANALOG_METER_ARC_MARK_COLOR);

      lastMark = currentMark;
    }
    _tft->unloadFont();
  }

  // Draw units
  if (strlen(_units) > 0)
  {
    _tft->loadFont(ANALOG_METER_UNITS_FONT_FAMILY);
    _tft->setTextSize(ANALOG_METER_UNITS_FONT_SIZE);
    _tft->setTextColor(ANALOG_METER_UNITS_FONT_COLOR);

    _tft->setTextColor(TFT_ORANGE);
    _tft->setTextDatum(MC_DATUM);
    _tft->drawString(_units, _x + xCircCenter, _y + _h - 25);

    _tft->unloadFont();
  }

  // Draw indicator
  if (_valChanged || force)
  {
    float prevDeg = valueToDeg(_prevValue);
    float currDeg = valueToDeg(_value);

    float tmpDeg = prevDeg;

    bool dir = isnan(_value) ? false : prevDeg < currDeg;
    int offset = 20;
    while (tmpDeg != currDeg)
    {
      _tft->drawLine(_prevx0, _prevy0, _prevx1, _prevy1, ANALOG_METER_BACKGROUND_COLOR);
      float sx = cos((tmpDeg - 90) * 0.0174532925);
      float sy = sin((tmpDeg - 90) * 0.0174532925);
      int x0 = _x + xCircCenter + (sx * offset);
      int y0 = _y + yCircCenter + (sy * offset);
      int x1 = _x + xCircCenter + (sx * (arcRadius - 2));
      int y1 = _y + yCircCenter + (sy * (arcRadius - 2));

      _tft->drawLine(x0, y0, x1, y1, ANALOG_METER_INDICATOR_COLOR);

      _prevx0 = x0;
      _prevy0 = y0;
      _prevx1 = x1;
      _prevy1 = y1;

      if (dir && tmpDeg >= currDeg)
        tmpDeg = currDeg;
      else if (!dir && tmpDeg <= currDeg)
        tmpDeg = currDeg;
      else
        tmpDeg = dir ? tmpDeg + 0.2 : tmpDeg - 0.2;

      delay(1);
    }
  }

  _prevValue = _value;
  _valChanged = false;
  _shouldRedraw = false;
}

float AnalogMeter::valueToDeg(float val)
{
  int midArc = _degrees / 2;
  int offlimitDeg = midArc + 3;
  float degs = 0.0;
  if (isnan(val) || val < _range.min)
    degs = -offlimitDeg;
  else if (val > _range.max)
    degs = offlimitDeg;
  else
    degs = map(val * 100, _range.min * 100, _range.max * 100, -midArc * 100, midArc * 100) / 100.0;

  return degs;
}
