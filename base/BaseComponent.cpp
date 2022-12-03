#include "BaseComponent.hpp"

BaseComponent::BaseComponent(TFT_eSPI *tft, const char *id)
{
  _tft = tft;
  strcpy(_id, id);
}

bool BaseComponent::isReady()
{
  return _isReady;
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
