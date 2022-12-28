#include "Stepper.hpp"

Stepper::Stepper(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
  _shouldRedraw = true;
}

int Stepper::getValue()
{
  return _current;
}

void Stepper::setStringsMode(bool stringsMode)
{
  _stringsMode = stringsMode;
  _shouldRedraw = true;
}

void Stepper::addString(const char *str)
{
  _strings.push_back(str);
  _shouldRedraw = true;
}

void Stepper::clearStrings()
{
  _strings.clear();
  _shouldRedraw = true;
}

void Stepper::setDelegate(StepperInterface *delegate)
{
  _delegate = delegate;
}

void Stepper::setVertical(bool vertical)
{
  _vertical = vertical;
  _shouldRedraw = true;
}

void Stepper::setValue(int value)
{
  int prev = _current;
  _current = value;
  if (_stringsMode)
  {
    _min = 0;
    _max = _strings.size() - 1;
  }
  if (_current < _min)
    _current = _cycle ? _max : _min;
  if (_current > _max)
    _current = _cycle ? _min : _max;

  _updated = prev != _current;
  if (_updated && _delegate)
    _delegate->onStepperValueChange(_id, prev, _current, _pointer);
}

void Stepper::setStep(int step)
{
  _step = step;
  _shouldRedraw = true;
}

void Stepper::setRange(int min, int max)
{
  _min = min < max ? min : max;
  _max = max > min ? max : min;
  setValue(_current);
  _shouldRedraw = true;
}

void Stepper::setNumberFormat(const char *format)
{
  strcpy(_format, format);
  _shouldRedraw = true;
}

void Stepper::setCustomColors(COLOR btnColor, COLOR btnTextColor, COLOR textColor)
{
  _btnColor = btnColor;
  _btnTextColor = btnTextColor;
  _labelColor = textColor;
  _shouldRedraw = true;
}

void Stepper::setSideMode(bool sideMode, bool left)
{
  _sideMode = sideMode;
  _left = left;
  _shouldRedraw = true;
}

void Stepper::setButtonSize(uint16_t w, uint16_t h)
{
  _btnW = w;
  _btnH = h;
  _shouldRedraw = true;
}

void Stepper::updateState()
{
  if (!_isReady)
    return;

  if ((int)millis() - (int)_lastCheck > 40)
  {
    _lastCheck = millis();
    if (_btnUp.isTouching())
    {
      _repeating = true;
      moveStepper();
    }
    else if (_btnDown.isTouching())
    {
      _repeating = true;
      moveStepper(false);
    }
  }

  if (_updated)
  {
    _updated = false;
    _lblValue.clearWithColor(_bgColor);

    if (_stringsMode && _strings.size() > 0)
      _lblValue.setLabel(_strings[_current]);
    else if (_stringsMode)
      _lblValue.setLabel("- -");
    else
    {
      char val[4];
      sprintf(val, _format, _current);
      _lblValue.setLabel(val);
    }
  }

  _lblValue.updateState();
  _btnUp.updateState();
  _btnDown.updateState();

  draw();
}

void Stepper::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!force || !_isReady)
    return;

  uint16_t w = _w;
  uint16_t h = _h;
  if (_sideMode)
    w += _btnW;
  else
  {
    w += _vertical ? 0 : (2 * _btnW);
    h += _vertical ? (2 * _btnH) : 0;
  };

  _tft->resetViewport();
  _tft->setViewport(_vX + _x, _vY + _y, w, h);
  if (!_btnUp.isReady())
  {
    _btnUp = Button(_tft, "StepperUp");
    _btnUp.setLabel("+");
    _btnUp.setParentViewport(_vX + _x, _vY + _y, w, h);
    _btnUp.setDelegate(this);
  }
  if (!_btnDown.isReady())
  {
    _btnDown = Button(_tft, "StepperDown");
    _btnDown.setLabel("-");
    _btnDown.setParentViewport(_vX + _x, _vY + _y, w, h);
    _btnDown.setDelegate(this);
  }
  if (!_lblValue.isReady())
  {
    _lblValue = Label(_tft, "StepperValue");
    _lblValue.setParentViewport(_vX + _x, _vY + _y, w, h);
  }

  char val[4];
  sprintf(val, _format, _current);
  _lblValue.setLabel(val);
  _btnUp.setCustomColors(_btnColor, _btnColor, _btnTextColor, _btnTextColor);
  _btnDown.setCustomColors(_btnColor, _btnColor, _btnTextColor, _btnTextColor);
  _lblValue.setColor(_labelColor);
  _lblValue.setPosition(w / 2, h / 2, MC_DATUM);

  if (_sideMode)
  {
    _btnUp.setDimensions(_left ? 0 : _w, 0, _btnW, (h / 2) - 1);
    _btnDown.setDimensions(_left ? 0 : _w, (h / 2), _btnW, (h % 2) != 0 ? (h / 2) + 1 : (h / 2));
    _lblValue.setPosition(_left ? _btnW + (_w / 2) : _w / 2, h / 2, MC_DATUM);
    _tft->drawRect(_left ? _btnW : 0, 0, _w, _h, COLOR_LIGHT_GRAY);
  }
  else if (_vertical)
  {
    _btnUp.setDimensions(0, 0, w, _btnH);
    _btnDown.setDimensions(0, h - _btnH, w, _btnH);
    _tft->drawRect(0, _btnH, _w, _h, COLOR_LIGHT_GRAY);
  }
  else
  {
    _btnDown.setDimensions(0, 0, _btnW, h);
    _btnUp.setDimensions(w - _btnW, 0, _btnW, h);
    _tft->drawRect(_btnW, 0, _w, _h, COLOR_LIGHT_GRAY);
  }

  _btnUp.setDisabled(_isDisabled);
  _btnDown.setDisabled(_isDisabled);
  _lblValue.setDisabled(_isDisabled);

  _lblValue.draw(force);
  _btnUp.draw(force);
  _btnDown.draw(force);

  _shouldRedraw = false;
}

void Stepper::moveStepper(bool up)
{
  setValue(up ? _current + _step : _current - _step);
}

// Interface
void Stepper::onButtonTouchStart(const char *btnId, void *ptr)
{
  _lastCheck = millis() + 500;
}

void Stepper::onButtonTouch(const char *btnId, void *ptr)
{
  if (_repeating)
  {
    _repeating = false;
    return;
  }

  if (strcmp(btnId, "StepperUp") == 0)
    moveStepper();
  else
    moveStepper(false);
}
