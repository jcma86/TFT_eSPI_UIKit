#ifndef __UIKIT_INPUTS_INTERFACE__
#define __UIKIT_INPUTS_INTERFACE__

#include <inttypes.h>

class InputInterface
{
public:
  virtual ~InputInterface() {}
  virtual void onInputComplete(const char *btnId, const char *value) = 0;
  virtual void onInputCancel(const char *btnId) {}
};

#endif