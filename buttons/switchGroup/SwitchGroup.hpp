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

  void onToggle(const char *btnId, bool state);

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
  void addButton(const char *id, const char *label);
  void deleteGroup();

  std::vector<bool> getCurrentState();

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif