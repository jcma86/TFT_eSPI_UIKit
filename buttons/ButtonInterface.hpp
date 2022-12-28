#ifndef __UIKIT_BUTTONS_BUTTONINTERFACE__
#define __UIKIT_BUTTONS_BUTTONINTERFACE__

#include <inttypes.h>

class ButtonInterface
{
public:
  virtual ~ButtonInterface() {}
  virtual void onButtonTouch(const char *btnId, void *ptr = NULL) {}
  virtual void onButtonTouchStart(const char *btnId, void *ptr = NULL) {}
  virtual void onButtonTouchEnd(const char *btnId, void *ptr = NULL) {}
  virtual void onButtonTouchCancel(const char *btnId, void *ptr = NULL) {}
};

#endif