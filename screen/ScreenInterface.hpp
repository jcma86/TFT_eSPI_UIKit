#ifndef __UIKIT_SCREEN_INTERFACE__
#define __UIKIT_SCREEN_INTERFACE__

#include <inttypes.h>

class ScreenInterface
{
public:
  virtual ~ScreenInterface() {}
  virtual void onScreenClose(const char *screenId) = 0;
  // virtual void onPushScreen(cm_screen_id requesterId, cm_screen_id screenToPush) = 0;
};

#endif