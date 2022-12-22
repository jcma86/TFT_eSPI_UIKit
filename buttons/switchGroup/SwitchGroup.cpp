#include "SwitchGroup.hpp"

SwitchGroup::SwitchGroup(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
}

void SwitchGroup::setDelegate(SwitchGroupInterface *delegate)
{
  _delegate = delegate;
}

void SwitchGroup::setIsHorizontal(bool isHorizontal)
{
  _horizontal = isHorizontal;
  _shouldRedraw = true;
}

void SwitchGroup::setAllowMultiSelection(bool allowMulti)
{
  if (_allowMultiSelection && !allowMulti)
  {
    for (int i = 0; i < _buttons.size(); i += 1)
      if (_buttons[i].getState())
        _buttons[i].setState(false);
  }

  _allowMultiSelection = allowMulti;
}

void SwitchGroup::setStates(std::vector<bool> state)
{
  if (state.size() != _buttons.size())
    return;

  for (int i = 0; i < state.size(); i += 1)
    if (state[i] != _buttons[i].getState())
      _buttons[i].setState(state[i]);
}

void SwitchGroup::setState(int index, bool state)
{
  if (index < 0 || index >= _buttons.size())
    return;

  if (!_allowMultiSelection && state)
    for (int i = 0; i < _buttons.size(); i += 1)
    {
      if (i == index)
        continue;
      if (_buttons[i].getState())
        _buttons[i].setState(false);
    }

  if (_buttons[index].getState() != state)
    _buttons[index].setState(state);
}

void SwitchGroup::setButtonWidth(uint16_t width)
{
  _btnWidth = width;
  _shouldRedraw = true;
}

void SwitchGroup::setBehaveAsButtons(bool asButton)
{
  _asButtons = asButton;
  _shouldRedraw = true;
}

void SwitchGroup::addButton(const char *id, const char *label)
{
  char btnId[80];
  sprintf(btnId, "%d_%s", _buttons.size(), label);

  ToggleButton btn = ToggleButton(_tft, btnId);
  btn.setParentViewport(_vX, _vY, _vW, _vH);
  btn.setDelegate(this);
  btn.setLabels(label, label);
  btn.setState(false);

  _buttons.push_back(btn);

  _shouldRedraw = true;
}

void SwitchGroup::setLabel(int btnIndex, const char *label) {
  if (btnIndex < 0 || btnIndex > (_buttons.size() - 1))
    return;

    _buttons[btnIndex].setLabels(label, label);
}

const char *SwitchGroup::getButtonLabel(int btnIndex)
{
  if (btnIndex < 0 || btnIndex > (_buttons.size() - 1))
    return "";

  return _buttons[btnIndex].getLabel();
}

void SwitchGroup::deleteGroup()
{
  _buttons.clear();

  _shouldRedraw = true;
}

std::vector<bool> SwitchGroup::getCurrentState()
{
  std::vector<bool> state;
  for (int i = 0; i < _buttons.size(); i += 1)
    state.push_back(_buttons[i].getState());

  return state;
}

void SwitchGroup::updateState()
{
  if (!_isReady)
    return;

  for (int i = 0; i < _buttons.size(); i += 1)
    _buttons[i].updateState();

  draw();
}

void SwitchGroup::draw(bool forceRedraw)
{
  bool force = _shouldRedraw || forceRedraw;
  if (!_isReady || !force)
    return;

  int16_t xPos = 0;
  int16_t yPos = 0;
  int padding = 5;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  for (int i = 0; i < _buttons.size(); i += 1)
  {
    _buttons[i].setDimensions(_x + xPos, _y + yPos, _btnWidth, BUTTON_HEIGHT);
    _buttons[i].draw(force);

    if (_horizontal)
    {
      xPos += padding + _btnWidth;
      if ((xPos + _btnWidth) > _w)
      {
        xPos = 0;
        yPos += padding + BUTTON_HEIGHT;
      }
    }
    else
    {
      yPos += padding + BUTTON_HEIGHT;
      if ((yPos + BUTTON_HEIGHT) > _h)
      {
        yPos = 0;
        xPos += padding + BUTTON_HEIGHT;
      }
    }
  }

  _shouldRedraw = false;
}

// Toggle Button Interface
void SwitchGroup::onToggle(const char *btnId, bool state)
{
  char *token = strtok((char *)btnId, "_");
  int index = atoi(token);

  if (!_allowMultiSelection && state)
    for (int i = 0; i < _buttons.size(); i += 1)
    {
      if (i == index && !_asButtons)
        continue;
      if (_buttons[i].getState())
        _buttons[i].setState(false);
    }

  if (_delegate)
    _delegate->onSwitch(_id, index, getCurrentState());
}
