#include "Screen.hpp"

Screen::Screen(TFT_eSPI *tft, const char *title)
{
  _tft = tft;
  strcpy(_title, title);

  _shouldRedraw = true;

  _x = 0;
  _y = 0;
  _w = TFT_WIDTH + 100;
  _h = TFT_HEIGHT;
}

void Screen::setDelegate(ScreenInterface *delegate)
{
  _delegate = delegate;
}

void Screen::drawTitleBar()
{
  if (_fullScreen)
    return;
  if (_titleBar)
  {
    _tft->setTextColor(TITLE_BAR_FONT_COLOR);
    _tft->setTextSize(TITLE_BAR_FONT_SIZE);
    _tft->setFreeFont(&TITLE_BAR_FONT_FAMILY);

    char title[80];
    if (_shouldRedraw)
    {
      sprintf(title, "%s", _title);
      _tft->fillRect(0, 0, _w, TITLE_BAR_HEIGHT, TITLE_BAR_COLOR);
      _tft->setTextDatum(ML_DATUM);
      _tft->drawString(title, PADDING_NORMAL, (TITLE_BAR_HEIGHT / 2) - 3);
    }
  }
}

void Screen::drawScreen()
{
  if (_tft == NULL || _onBackground)
  {
    return;
  }

  uint8_t bWidth = 0; //_border ? UI_BORDER_WIDTH : 0;
  uint32_t offset = _titleBar && !_fullScreen ? TITLE_BAR_HEIGHT + bWidth : 0;

  uint32_t x = _x + bWidth;
  uint32_t y = _y + bWidth;
  uint32_t w = _w - (2 * bWidth);
  uint32_t h = _h - (2 * bWidth);

  _tft->resetViewport();
  _tft->setViewport(x, y, w, h);
  if (_shouldRedraw)
  {
    _tft->fillScreen(SCREEN_BACKGROUND_COLOR);
    _tft->frameViewport(COLOR_BLACK, -bWidth);
  }
  drawTitleBar();

  // if (_btnClose.isReady())
  // {
  //   _btnClose.updateState();
  // }

  _contentX = x;
  _contentY = y + offset;
  _contentW = w;
  _contentH = h - offset;
  _tft->setViewport(_contentX, _contentY, _contentW, _contentH);
  if (_shouldRedraw)
  {
    _tft->fillRect(0, 0, _contentW, _contentH, SCREEN_BACKGROUND_COLOR);
  }

  drawContent();
}

void Screen::setFullScreen(bool fullScreen)
{
  _fullScreen = fullScreen;
  _shouldRedraw = true;
}

void Screen::showScreen(bool forceRedraw, bool titleBar, bool closeBtn, bool onBackground)
{
  _onBackground = onBackground;
  _shouldRedraw = _shouldRedraw || _forceRedraw || forceRedraw;

  _titleBar = titleBar;
  _closeBtn = closeBtn;

  updateState();
  drawScreen();

  _shouldRedraw = false || _forceRedraw;
  _forceRedraw = false;
}
