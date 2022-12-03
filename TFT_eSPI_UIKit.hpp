#ifndef __UIKIT__
#define __UIKIT__

#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>

#include "fonts/Fonts.hpp"
#include "helpers/Colors.hpp"
#include "theme/default.hpp"

#include "base/BaseComponent.hpp"
#include "base/TouchableComponent.hpp"

#include "buttons/ButtonBase.hpp"
#include "buttons/ButtonInterface.hpp"
#include "buttons/button/Button.hpp"
#include "buttons/toggle/ToggleButton.hpp"
#include "buttons/toggle/ToggleButtonInterface.hpp"

#include "indicators/led/Led.hpp"
#include "indicators/progress/ProgressBar.hpp"

#include "list/List.hpp"
#include "list/ListInterface.hpp"

#include "screen/Screen.hpp"
#include "screen/ScreenInterface.hpp"

#include "tools/CalibrateTouch.hpp"
#endif