#include "ToggleButton.hpp"

ToggleButton::ToggleButton(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
}

void ToggleButton::setDelegate(ToggleButtonInterface *delegate)
{
  _delegate = delegate;
}

void ToggleButton::setState(bool state)
{
  _state = state;
  _shouldRedraw = true;
}

void ToggleButton::clearCustomColors()
{
  _backONColor = TOGGLE_BUTTON_ON_BACKGROUND_COLOR;
  _backOFFColor = TOGGLE_BUTTON_OFF_BACKGROUND_COLOR;
  _fontONColor = TOGGLE_BUTTON_ON_TEXT_COLOR;
  _fontOFFColor = TOGGLE_BUTTON_OFF_TEXT_COLOR;

  _shouldRedraw = true;
}

void ToggleButton::setCustomColors(COLOR backgroundOn, COLOR backgroundOff, COLOR textOn, COLOR textOff)
{
  _backONColor = backgroundOn;
  _backOFFColor = backgroundOff;
  _fontONColor = textOn;
  _fontOFFColor = textOff;

  _shouldRedraw = true;
}

void ToggleButton::setLabels(const char *labelON, const char *labelOFF)
{
  strcpy(_labelON, labelON);
  strcpy(_labelOFF, labelOFF);
  _shouldRedraw = true;
}

bool ToggleButton::getState()
{
  return _state;
}

void ToggleButton::updateState()
{
  if (!_isReady)
    return;

  _button.updateState();
  draw(_shouldRedraw);
}

void ToggleButton::draw(bool forceRedraw)
{
  if (!_isReady)
    return;

  bool force = _shouldRedraw || forceRedraw;
  if (!force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX + _x, _vY + _y, _w, _h);
  if (!_button.isReady())
  {
    _button = Button(_tft, "toogleButton");
    _button.setParentViewport(_x + _vX, _y + _vY, _w, _h);
    _button.setIsEnabled(true);
    _button.setDelegate(this);
  }

  if (_state)
    _button.setCustomColors(_backONColor, _backONColor, _fontONColor, _fontONColor);
  else
    _button.setCustomColors(_backOFFColor, _backOFFColor, _fontOFFColor, _fontOFFColor);

  _button.setDimensions(0, 0, _w, _h);
  _button.draw(_state ? _labelON : _labelOFF, force);

  _shouldRedraw = false;
}

// Interface
void ToggleButton::onButtonTouch(const char *btnId)
{
  _state = !_state;
  if (_delegate)
    _delegate->onToggle(_id, _state);

  _shouldRedraw = true;
}
