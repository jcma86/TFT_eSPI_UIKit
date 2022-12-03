#ifndef TOUCH_CS
void initFileSystem()
{
  Serial.println("TOUCH_CS is undefined.");
}

void deleteCalibrationData()
{
  Serial.println("TOUCH_CS is undefined.");
}

uint16_t *getCalibrationData()
{
  Serial.println("TOUCH_CS is undefined.");
  return NULL;
}

bool needsToCalibrate()
{
  Serial.println("TOUCH_CS is undefined.");
  return false;
}

bool touchCalibration(TFT_eSPI *tft)
{
  Serial.println("TOUCH_CS is undefined.");
  return false;
}
#else

#ifndef __UIKIT_TOOLS_CALIBRATETOUCH__
#define __UIKIT_TOOLS_CALIBRATETOUCH__

#include "FS.h"
#include <inttypes.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#ifndef CALIBRATION_FILE
#define CALIBRATION_FILE "/ScreenTouchCalibrationData"
#endif
#ifndef CALIBRATED
#define CALIBRATED "/ScreenTouchCalibrated"
#endif

static bool calibrationComplete = false;

void initFileSystem()
{
  if (!SPIFFS.begin())
  {
    Serial.println("Formatting file system");
    SPIFFS.format();
    SPIFFS.begin();
  }
}

void deleteCalibrationData()
{
  initFileSystem();
  if (SPIFFS.exists(CALIBRATION_FILE))
    SPIFFS.remove(CALIBRATION_FILE);
  if (SPIFFS.exists(CALIBRATED))
    SPIFFS.remove(CALIBRATED);

  calibrationComplete = false;
}

uint16_t *getCalibrationData()
{
  static uint16_t calData[5];

  initFileSystem();
  File f = SPIFFS.open(CALIBRATION_FILE, "r");
  if (f)
  {
    if (f.readBytes((char *)calData, 14) == 14)
    {
      f.close();
      return calData;
    }
  }

  return NULL;
}

bool needsToCalibrate()
{
  bool needs = false;
  if (calibrationComplete)
    return false;

  initFileSystem();

  if (!SPIFFS.exists(CALIBRATED))
    needs = true;

  if (!SPIFFS.exists(CALIBRATION_FILE))
  {
    needs = true;
  }
  else
  {
    File f = SPIFFS.open(CALIBRATION_FILE, "r");
    if (getCalibrationData() == NULL)
      needs = true;
  }

  return needs;
}

bool touchCalibration(TFT_eSPI *tft)
{
  uint16_t calData[5];
  initFileSystem();

  if (!needsToCalibrate())
  {
    tft->setTouch(getCalibrationData());
    calibrationComplete = true;
    Serial.println("Calibration completed");
  }
  else
  {
    // data not valid so recalibrate
    tft->fillScreen(TFT_BLACK);
    tft->setCursor(20, 0);
    tft->setTextFont(2);
    tft->setTextSize(1);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);

    tft->println("Touch corners as indicated");
    tft->setTextFont(1);
    tft->println();

    tft->calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft->setTextColor(TFT_GREEN, TFT_BLACK);
    tft->println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f)
    {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }

  return calibrationComplete;
}

#endif
#endif
