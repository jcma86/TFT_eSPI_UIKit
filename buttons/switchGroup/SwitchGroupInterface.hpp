#ifndef __UIKIT_BUTTONS_SWITCHGROUP_INTERFACE__
#define __UIKIT_BUTTONS_SWITCHGROUP_INTERFACE__

#include <vector>

class SwitchGroupInterface
{
public:
  virtual ~SwitchGroupInterface() {}
  virtual void onSwitch(int btnIndex, std::vector<bool> states) = 0;
};

#endif
