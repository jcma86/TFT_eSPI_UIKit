#include <FS.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <fstream>
#include <inttypes.h>
#include <SPI.h>
#include <TFT_eSPI.h>

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

#ifndef CALIBRATION_FILE
#define CALIBRATION_FILE "/ScreenTouchCalibrationData"
#endif
#ifndef CALIBRATED
#define CALIBRATED "/ScreenTouchCalibrated"
#endif

static bool calibrationComplete = false;
void initFileSystem();
void deleteCalibrationData();
uint16_t *getCalibrationData();
bool needsToCalibrate();
bool touchCalibration(TFT_eSPI *tft);

#endif
#endif
