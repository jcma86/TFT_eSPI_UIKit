#include "Button.hpp"

Button::Button()
{
  _isReady = false;
}

Button::Button(TFT_eSPI *tft, const char *id, ButtonMode mode) : ButtonBase(tft, id)
{
  _mode = mode;

  _isPressed = false;
  _shouldRedraw = true;
  _isEnabled = true;
  _isReady = true;
}

void Button::setDelegate(ButtonInterface *delegate)
{
  _delegate = delegate;
}

void Button::setIsEnabled(bool isEnabled)
{
  _isEnabled = isEnabled;
  _touchableEnabled = isEnabled;
  _shouldRedraw = true;
}

void Button::setButtonMode(ButtonMode mode)
{
  _mode = mode;
  _shouldRedraw = true;
}

void Button::setIsPressed(bool isPressed)
{
  _isPressed = isPressed;
  _shouldRedraw = true;
}

void Button::setCustomColors(COLOR backNormal, COLOR backPressed, COLOR textNormal, COLOR textPressed)
{
  _backNormal = backNormal;
  _backPressed = backPressed;
  _textNormal = textNormal;
  _textPressed = textPressed;
  _hasCustomColor = true;
  _shouldRedraw = true;
}

void Button::removeCustomColors()
{
  _hasCustomColor = false;
  _shouldRedraw = false;
}

void Button::onTouch()
{
  if (_delegate)
    _delegate->onButtonTouch(_id);
  setIsPressed(false);
}

void Button::onTouchStart()
{
  if (_delegate)
    _delegate->onButtonTouchStart(_id);
  setIsPressed();
}

void Button::onTouchEnd()
{
  if (_delegate)
    _delegate->onButtonTouchEnd(_id);
  setIsPressed(false);
}

void Button::onTouchCancel()
{
  if (_delegate)
    _delegate->onButtonTouchCancel(_id);
  setIsPressed(false);
}

void Button::updateState()
{
  if (!_isReady || !_isEnabled)
    return;

  processTouch();
  draw(_label);
}

void Button::draw(const char *label, bool forceRedraw)
{
  if (!_isReady || !_isVisible)
    return;

  bool force = _shouldRedraw || forceRedraw;
  if (!force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);
  strcpy(_label, label);

  COLOR textColor;
  COLOR backColor;

  if (_mode == NORMAL)
  {
    textColor = _isPressed ? BUTTON_TEXT_COLOR_PRESSED : BUTTON_TEXT_COLOR_NORMAL;
    _tft->setTextDatum(MC_DATUM);
  }
  if (_mode == TEXT)
  {
    textColor = _isPressed ? TEXT_BUTTON_COLOR_PRESSED : TEXT_BUTTON_COLOR_NORMAL;
    _tft->setTextDatum(ML_DATUM);
  }

  if (_hasCustomColor)
  {
    textColor = _isPressed ? _textPressed : _textNormal;
    backColor = _isPressed ? _backPressed : _backNormal;
  }
  else
    backColor = _isPressed ? BUTTON_BACKGROUND_COLOR_PRESSED : BUTTON_BACKGROUND_COLOR_NORMAL;

  _tft->loadFont(BUTTON_FONT_FAMILY);
  _tft->setTextSize(BUTTON_FONT_SIZE);
  _tft->setTextColor(textColor);

  uint32_t textX = 0;
  uint32_t textY = _y + (_h / 2);
  if (_mode == TEXT)
  {
    if (_hasCustomColor)
      _tft->fillRect(_x, _y, _w, _h, backColor);
    textX = _x;
  }
  if (_mode == NORMAL)
  {
    _tft->fillRect(_x, _y, _w, _h, backColor);
    textX = _x + (_w / 2);
  }
  textY += 2;

  _tft->drawString(label, textX, textY);

  _tft->unloadFont();

  _shouldRedraw = false;
}
