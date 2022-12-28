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
  _isReady = true;
}

void Button::setDelegate(ButtonInterface *delegate)
{
  _delegate = delegate;
}

void Button::setLabel(const char *label)
{
  strcpy(_label, label);
  _shouldRedraw = true;
}

const char *Button::getLabel()
{
  return _label;
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

void Button::setHoverColors(COLOR backHover, COLOR textHover)
{
  _backHover = backHover;
  _textHover = textHover;
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
    _delegate->onButtonTouch(_id, _pointer);
  _isTouching = false;
  setIsPressed(false);
}

void Button::onTouchStart()
{
  if (_delegate)
    _delegate->onButtonTouchStart(_id, _pointer);
  _isTouching = true;
  setIsPressed();
}

void Button::onTouchEnd()
{
  if (_delegate)
    _delegate->onButtonTouchEnd(_id, _pointer);
  _isTouching = false;
  setIsPressed(false);
}

void Button::onTouchCancel()
{
  if (_delegate)
    _delegate->onButtonTouchCancel(_id, _pointer);
  _isTouching = false;
  setIsPressed(false);
}

void Button::updateState()
{
  if (!_isReady)
    return;

  processTouch();
  draw(_label);
}

void Button::draw(bool forceRedraw)
{
  draw(_label, forceRedraw);
}

void Button::draw(const char *label, bool forceRedraw)
{
  if (!_isReady || !_isVisible)
    return;

  bool force = _shouldRedraw || forceRedraw;
  if (!force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX + _x, _vY + _y, _w, _h);
  strcpy(_label, label);

  COLOR textColor;
  COLOR backColor;

  if (_mode == BUTTON_MODE_NORMAL)
  {
    textColor = _isPressed ? BUTTON_TEXT_COLOR_PRESSED : BUTTON_TEXT_COLOR_NORMAL;
    _tft->setTextDatum(MC_DATUM);
  }
  if (_mode == BUTTON_MODE_TEXT)
  {
    textColor = _isPressed ? TEXT_BUTTON_COLOR_PRESSED : TEXT_BUTTON_COLOR_NORMAL;
    _tft->setTextDatum(ML_DATUM);
  }

  if (_isDisabled)
  {
    textColor = _textDisabledColor;
    backColor = _backDisabledColor;
  }
  else if (_isTouching)
  {
    textColor = _textHover;
    backColor = _backHover;
  }
  else if (_hasCustomColor)
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
  uint32_t textY = _h / 2;
  if (_mode == BUTTON_MODE_TEXT)
  {
    if (_hasCustomColor)
      _tft->fillRect(0, 0, _w, _h, backColor);
    textX = 0;
  }
  if (_mode == BUTTON_MODE_NORMAL)
  {
    _tft->fillRect(0, 0, _w, _h, backColor);
    textX = (_w / 2);
  }
  textY += 2;

  _tft->drawString(label, textX, textY);

  _tft->unloadFont();

  _shouldRedraw = false;
}
