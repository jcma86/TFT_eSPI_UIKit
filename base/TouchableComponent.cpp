#include "TouchableComponent.hpp"

bool TouchableComponent::isValidTouch(uint16_t x, uint16_t y)
{
  // Serial.printf("%d,%d --> %d %d (%d %d) --> %d %d (%d %d)\n", x, y, _x, _y, _w, _h, _vX, _vY, _vW, _vH);
  uint16_t offsetY = _vY + _y;
  uint16_t offsetX = _vX + _x;

  return (y > offsetY && y < (offsetY + _h) && x > offsetX && x < (offsetX + _w));
}

void TouchableComponent::processTouch()
{
  if (!_touchableEnabled)
    return;

  if (millis() - lastTouch < 20)
    return;

  if (_tft->getTouch(&_touchX, &_touchY))
  {
    lastTouch = millis();
    // Use to validation if touch ENDED in valid area
    _prevTouchX = _touchX;
    _prevTouchY = _touchY;

    bool isValid = isValidTouch(_touchX, _touchY);
    if (isValid && !_onTouchStart)
    {
      currentTouch = millis();
      onTouchStart();
    }
    else if (!isValid && !_onTouchStart)
      _touchStartedOutside = true;

    _onTouchStart = true;
  }
  else
  {
    if (_onTouchStart)
    {
      if (!_touchStartedOutside && isValidTouch(_prevTouchX, _prevTouchY) && millis() - currentTouch > 20)
      {
        onTouch();
        onTouchEnd();
      }
      else
        onTouchCancel();
    }

    _onTouchStart = false;
    _touchStartedOutside = false;
  }
}