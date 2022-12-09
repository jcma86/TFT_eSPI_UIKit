#ifndef __UIKIT_BUTTONS_BUTTONINTERFACE__
#define __UIKIT_BUTTONS_BUTTONINTERFACE__

#include <inttypes.h>

class ButtonInterface
{
public:
  virtual ~ButtonInterface() {}
  virtual void onButtonTouch(const char *btnId) {}
  virtual void onButtonTouchStart(const char *btnId) {}
  virtual void onButtonTouchEnd(const char *btnId) {}
  virtual void onButtonTouchCancel(const char *btnId) {}
};

#endif