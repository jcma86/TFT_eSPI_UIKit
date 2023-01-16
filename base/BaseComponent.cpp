#include "BaseComponent.hpp"

BaseComponent::BaseComponent()
{
  strcpy(_id, "BaseComponent - Not Initialized");
}

BaseComponent::BaseComponent(TFT_eSPI *tft, const char *id)
{
  _tft = tft;
  strcpy(_id, id);
}

BaseComponent::~BaseComponent()
{
  if (_wifi)
    _wifi->removeDelegate(_wifiDelegateId);
}

const char *BaseComponent::getId()
{
  return _id;
}

bool BaseComponent::isReady()
{
  return _isReady;
}

void BaseComponent::setWiFi(WiFiConnection *wifi)
{
  _wifi = wifi;
  if (_wifi)
    _wifiDelegateId = _wifi->setDelegate(this, _id);
}

void BaseComponent::setFont(const GFXfont *font)
{
  _font = (GFXfont *)font;
  _shouldRedraw = true;
}

void BaseComponent::setDatum(uint8_t datum)
{
  _datum = datum;
  _shouldRedraw = true;
}

void BaseComponent::setFontScale(uint8_t scale)
{
  _fontScale = scale;
  _shouldRedraw = true;
}

void BaseComponent::setPointer(void *ptr)
{
  _pointer = ptr;
}

void *BaseComponent::getPointer()
{
  return _pointer;
}

void BaseComponent::setDisabled(bool isDisabled)
{
  if(_isDisabled != isDisabled)
  _shouldRedraw = true;
  
  _isDisabled = isDisabled;
}

bool BaseComponent::isEnabled(){
  return !_isDisabled;
}

void BaseComponent::setDisabledColors(COLOR _backColor, COLOR _textColor)
{
  _backDisabledColor = _backColor;
  _textDisabledColor = _textColor;
  _shouldRedraw = true;
}

void BaseComponent::setParentViewport(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  _vX = x;
  _vY = y;
  _vW = w;
  _vH = h;
  _shouldRedraw = true;
}

void BaseComponent::setDimensions(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _shouldRedraw = true;
}

void BaseComponent::setIsVisible(bool isVisible)
{
  _isVisible = isVisible;
}
