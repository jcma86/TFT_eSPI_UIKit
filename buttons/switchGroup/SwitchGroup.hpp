#ifndef __UIKIT_BUTTONS_SWITCHGROUP__
#define __UIKIT_BUTTONS_SWITCHGROUP__

#include <vector>
#include "../../base/BaseComponent.hpp"
#include "../toggle/ToggleButton.hpp"
#include "../toggle/ToggleButtonInterface.hpp"
#include "SwitchGroupInterface.hpp"

class SwitchGroup : public BaseComponent, public ToggleButtonInterface
{
private:
  SwitchGroupInterface *_delegate = NULL;
  bool _asButtons = false;
  bool _horizontal = true;
  bool _allowMultiSelection = false;
  std::vector<ToggleButton> _buttons; // TODO: Accept Buttons or ToggleButtons
  uint16_t _btnWidth = 50;
  int _hPadding = 5;
  int _vPadding = 5;
  COLOR _backgroundOn = COLOR_PRIMARY;
  COLOR _backgroundOff = COLOR_SECONDARY;
  COLOR _textOn = COLOR_BLACK;
  COLOR _textOff = COLOR_BLACK;

  void onToggle(const char *btnId, bool state, void *ptr = NULL);

public:
  SwitchGroup() {}
  SwitchGroup(TFT_eSPI *tft, const char *id);

  void setDelegate(SwitchGroupInterface *delegate);
  void setIsHorizontal(bool isHorizontal = true);
  void setAllowMultiSelection(bool allowMulti = true);
  void setBehaveAsButtons(bool asButton = true);
  void setStates(std::vector<bool> state);
  void setState(int index, bool state);
  void setButtonWidth(uint16_t width);
  void setLabel(int btnIndex, const char *label);
  void setColumnGap(int gap = 5);
  void setRowGap(int gap = 5);
  void addButton(const char *id, const char *label, ButtonMode mode = BUTTON_MODE_NORMAL);
  void setCustomColors(COLOR backgroundOn, COLOR backgroundOff, COLOR textOn, COLOR textOff);
  void deleteGroup();
  const char *getButtonLabel(int btnIndex);
  ToggleButton *getRefToToggleButton(int btnIndex);

  std::vector<bool> getCurrentState();

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif