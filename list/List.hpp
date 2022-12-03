#ifndef __UIKIT_LIST__
#define __UIKIT_LIST__

#include <string>
#include <TFT_eSPI.h>
#include <inttypes.h>
#include <vector>

#include "../helpers/Colors.hpp"
#include "../theme/default.hpp"
#include "../base/BaseComponent.hpp"
#include "../buttons/button/Button.hpp"
#include "../buttons/ButtonInterface.hpp"

#include "ListInterface.hpp"

using namespace std;

class List : public BaseComponent, public ButtonInterface
{
private:
  int _rowsVisible = 2;
  int _firstVisible = 0;
  int _selected = -1;

  ListInterface *_delegate = NULL;

  vector<Button> _items;
  vector<const char *> _itemsLabels;

  Button btnUp;
  Button btnDown;

  void onButtonTouch(const char *btnId);
  void onButtonTouchEnd(const char *btnId) {}
  void onButtonTouchStart(const char *btnId) {}
  void onButtonTouchCancel(const char *btnId) {}

  void scroll(int direction);

public:
  List() {}
  List(TFT_eSPI *tft, const char *id);

  void clearList();
  void addItem(const char *item);
  void setSelectedItem(int index = 0);
  void setNumOfVisibleRows(int rows = 2);

  void setDelegate(ListInterface *delegate);

  void updateState();
  void draw(bool forceRedraw = false);
};

#endif