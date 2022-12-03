#ifndef __UIKIT_LIST_INTERFACE__
#define __UIKIT_LIST_INTERFACE__

#include <inttypes.h>

class ListInterface
{
public:
  virtual ~ListInterface() {}
  virtual void onItemSelect(int itemIndex) = 0;
};

#endif