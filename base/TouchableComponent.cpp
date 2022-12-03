#include "TouchableComponent.hpp"

bool TouchableComponent::isValidTouch(uint16_t x, uint16_t y)
{
  return (y < (_y + _h) && y > _y &&
          x < (_x + _w) && x > _x);
}

void TouchableComponent::processTouch()
{
  if (!_touchableEnabled)
    return;

  if (millis() - lastTouch < 40)
    return;

  if (_tft->getTouch(&_touchX, &_touchY))
  {
    lastTouch = millis();
    _touchY -= _vY;
    _touchX -= _vX;

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
      if (!_touchStartedOutside && isValidTouch(_prevTouchX, _prevTouchY) && millis() - currentTouch > 80)
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