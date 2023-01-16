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

void SwitchGroup::addButton(const char *id, const char *label, ButtonMode mode)
{
  char btnId[80];
  snprintf(btnId, 30, "%d_%s", _buttons.size(), label);

  ToggleButton btn = ToggleButton(_tft, btnId, mode);
  // btn.setParentViewport(_vX, _vY, _vW, _vH);
  btn.setDelegate(this);
  btn.setButtonMode(mode);
  btn.setLabels(label, label);
  btn.setState(false);

  _buttons.push_back(btn);

  _shouldRedraw = true;
}

void SwitchGroup::setCustomColors(COLOR backgroundOn, COLOR backgroundOff, COLOR textOn, COLOR textOff)
{
  _backgroundOn = backgroundOn;
  _backgroundOff = backgroundOff;
  _textOn = textOn;
  _textOff = textOff;

  _shouldRedraw = true;
}

ToggleButton *SwitchGroup::getRefToToggleButton(int btnIndex)
{
  if (btnIndex < 0 || btnIndex > (_buttons.size() - 1))
    return NULL;

  return &_buttons[btnIndex];
}

void SwitchGroup::setLabel(int btnIndex, const char *label)
{
  if (btnIndex < 0 || btnIndex > (_buttons.size() - 1))
    return;

  _buttons[btnIndex].setLabels(label, label);
}

void SwitchGroup::setColumnGap(int gap)
{
  _hPadding = gap;
  _shouldRedraw = true;
}
void SwitchGroup::setRowGap(int gap)
{
  _vPadding = gap;
  _shouldRedraw = true;
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

  _tft->resetViewport();
  _tft->setViewport(_x + _vX, _y + _vY, _vW, _vH);

  std::vector<bool> states = getCurrentState();
  for (int i = 0; i < _buttons.size(); i += 1)
  {
    _buttons[i].setDimensions(xPos, yPos, _btnWidth, BUTTON_HEIGHT);
    _buttons[i].setDisabled(_isDisabled);
    _buttons[i].setCustomColors(_backgroundOn, _backgroundOff, _textOn, _textOff);
    _buttons[i].setParentViewport(_x + _vX, _y + _vY, _btnWidth, BUTTON_HEIGHT);
    _buttons[i].setState(states[i]);
    _buttons[i].draw(force);

    if (_horizontal)
    {
      xPos += _hPadding + _btnWidth;
      if ((xPos + _btnWidth) > _w)
      {
        xPos = 0;
        yPos += _vPadding + BUTTON_HEIGHT;
      }
    }
    else
    {
      yPos += _vPadding + BUTTON_HEIGHT;
      if ((yPos + BUTTON_HEIGHT) > _h)
      {
        yPos = 0;
        xPos += _hPadding + BUTTON_HEIGHT;
      }
    }
  }

  _shouldRedraw = false;
}

// Toggle Button Interface
void SwitchGroup::onToggle(const char *btnId, bool state, void *ptr)
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
    _delegate->onSwitch(_id, index, getCurrentState(), _pointer);
}
