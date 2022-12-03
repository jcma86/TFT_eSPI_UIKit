#ifndef __UIKIT_BUTTONS_BUTTONINTERFACE__
#define __UIKIT_BUTTONS_BUTTONINTERFACE__

#include <inttypes.h>

class ButtonInterface
{
public:
  virtual ~ButtonInterface() {}
  virtual void onButtonTouch(const char *btnId) = 0;
  virtual void onButtonTouchStart(const char *btnId) = 0;
  virtual void onButtonTouchEnd(const char *btnId) = 0;
  virtual void onButtonTouchCancel(const char *btnId) = 0;
};

#endif