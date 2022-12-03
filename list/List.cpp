#include "List.hpp"

List::List(TFT_eSPI *tft, const char *id) : BaseComponent(tft, id)
{
  _isReady = true;
}

void List::clearList()
{
  _items.clear();
  _itemsLabels.clear();

  _shouldRedraw = true;
}

void List::addItem(const char *item)
{
  char itemId[50];
  sprintf(itemId, "%d_%s", _items.size(), item);
  Button anItem = Button(_tft, itemId, TEXT);
  anItem.setParentViewport(_vX + _x, _vY + _y, _vW + _w, _vH + _h);
  anItem.setDimensions(0, 0, 0, 0);
  anItem.setIsEnabled(true);
  anItem.setDelegate(this);
  anItem.setIsVisible(false);

  _items.push_back(anItem);
  _itemsLabels.push_back(item);

  _shouldRedraw = true;
}

void List::setNumOfVisibleRows(int rows)
{
  _rowsVisible = rows < 2 ? 2 : rows;
  _h = _rowsVisible * BUTTON_HEIGHT;
  _shouldRedraw = true;
}

void List::setSelectedItem(int index)
{
  int prevSelected = _selected;
  _selected = index >= _items.size() ? _items.size() - 1 : index;

  if (prevSelected != _selected)
  {
    if (_delegate)
      _delegate->onItemSelect(_selected);
    _shouldRedraw = true;
    draw();
  }
}

void List::scroll(int direction)
{
  int prevFirst = _firstVisible;
  if (direction < 0)
    _firstVisible -= _firstVisible > 0 ? 1 : 0;
  else if (direction > 0)
    _firstVisible += (_firstVisible + _rowsVisible) < _items.size() ? 1 : 0;

  if (prevFirst != _firstVisible)
  {
    _items[prevFirst < _firstVisible ? prevFirst : prevFirst + (_rowsVisible - 1)].setIsVisible(false);
    _shouldRedraw = true;
    draw();
  }
}

void List::setDelegate(ListInterface *delegate) {}

void List::updateState()
{
  if (!_isReady)
    return;

  btnUp.updateState();
  btnDown.updateState();
  for (int i = _firstVisible; i < _firstVisible + _rowsVisible; i += 1)
    _items[i].updateState();
}

void List::draw(bool forceRedraw)
{
  if (!_isReady)
    return;

  bool force = _shouldRedraw || forceRedraw;
  if (!force)
    return;

  _tft->resetViewport();
  _tft->setViewport(_vX, _vY, _vW, _vH);

  if (!btnUp.isReady())
  {
    btnUp = Button(_tft, "btnUp");
    btnUp.setParentViewport(_vX + _x, _vY + _y, _vW + _w, _vH + _h);
    btnUp.setIsEnabled(true);
    btnUp.setDelegate(this);
  }
  if (!btnDown.isReady())
  {
    btnDown = Button(_tft, "btnDown");
    btnDown.setParentViewport(_vX + _x, _vY + _y, _vW + _w, _vH + _h);
    btnDown.setIsEnabled(true);
    btnDown.setDelegate(this);
  }

  _tft->fillRect(_x, _y, _w - BUTTON_HEIGHT, _h, LIST_BACKGROUND_COLOR);
  _tft->fillRect(_x + _w - BUTTON_HEIGHT, _y + BUTTON_HEIGHT, BUTTON_HEIGHT, _h - (2 * BUTTON_HEIGHT), LIST_SCROLL_BACKGROUND_COLOR);

  btnUp.setDimensions(_w - BUTTON_HEIGHT, 0, BUTTON_HEIGHT, BUTTON_HEIGHT);
  btnUp.draw("\u2191", force);

  btnDown.setDimensions(_w - BUTTON_HEIGHT, _h - BUTTON_HEIGHT, BUTTON_HEIGHT, BUTTON_HEIGHT);
  btnDown.draw("\u2193", force);

  if (_items.size() > 0)
  {
    for (int i = 0; i < _rowsVisible; i += 1)
    {
      int index = i + _firstVisible;
      if (index == _selected)
        _items[index].setCustomColors(LIST_ITEM_SELECTED_BACKGROUND_COLOR, LIST_ITEM_SELECTED_BACKGROUND_COLOR, LIST_ITEM_TEXT_SELECTED_COLOR, LIST_ITEM_TEXT_SELECTED_COLOR);
      else
        _items[index].setCustomColors(LIST_ITEM_BACKGROUND_COLOR, LIST_ITEM_BACKGROUND_COLOR, LIST_ITEM_TEXT_COLOR, LIST_ITEM_TEXT_COLOR);
      char label[100];
      sprintf(label, " %s", _itemsLabels[index]);
      _items[index].setDimensions(_x, _y + (i * BUTTON_HEIGHT), _w - BUTTON_HEIGHT, BUTTON_HEIGHT);
      _items[index].setIsVisible();
      _items[index].draw(label, force);
    }
  }

  _shouldRedraw = false;
}

// Delegate Button
void List::onButtonTouch(const char *btnId)
{
  if (strcmp(btnId, "btnDown") == 0)
    scroll(1);
  else if (strcmp(btnId, "btnUp") == 0)
    scroll(-1);
  else
  {
    char *token = strtok((char *)btnId, "_");
    if (token)
      setSelectedItem(atoi(token));
  }
}
