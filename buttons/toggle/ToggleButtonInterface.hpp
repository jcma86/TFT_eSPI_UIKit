#ifndef __UIKIT_BUTTONS_TOGGLE_INTERFACE__
#define __UIKIT_BUTTONS_TOGGLE_INTERFACE__

class ToggleButtonInterface
{
public:
  virtual ~ToggleButtonInterface() {}
  virtual void onToggle(const char *btnId, bool state) = 0;
};

#endif
