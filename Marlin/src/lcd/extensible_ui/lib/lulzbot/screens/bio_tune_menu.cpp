/*********************
 * bio_tune_menu.cpp *
 *********************/

/****************************************************************************
 *   Written By Mark Pelletier  2017 - Aleph Objects, Inc.                  *
 *   Written By Marcio Teixeira 2018 - Aleph Objects, Inc.                  *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <http://www.gnu.org/licenses/>.                              *
 ****************************************************************************/

#include "../config.h"

#if ENABLED(LULZBOT_TOUCH_UI) && defined(LULZBOT_USE_BIOPRINTER_UI)

#include "screens.h"

using namespace FTDI;
using namespace Theme;
using namespace ExtUI;

void TuneMenu::onRedraw(draw_mode_t what) {
  if (what & BACKGROUND) {
    CommandProcessor cmd;
    cmd.cmd(CLEAR_COLOR_RGB(bg_color))
       .cmd(CLEAR(true,true,true))
       .font(font_medium);
  }

  #define GRID_ROWS 7
  #define GRID_COLS 2

  if (what & FOREGROUND) {
    CommandProcessor cmd;
    cmd.cmd(COLOR_RGB(bg_text_enabled))
       .font(font_large).text  ( BTN_POS(1,1), BTN_SIZE(2,1), GET_TEXTF(PRINT_MENU))
       .colors(normal_btn)
       .font(font_medium)
       .enabled( isPrinting()).tag(2).button( BTN_POS(1,2), BTN_SIZE(2,1), GET_TEXTF(PRINT_SPEED))
                              .tag(3).button( BTN_POS(1,3), BTN_SIZE(2,1), GET_TEXTF(BED_TEMPERATURE))
        #if ENABLED(BABYSTEPPING)
          .enabled(true)
        #else
          .enabled(false)
        #endif
                              .tag(4).button( BTN_POS(1,4), BTN_SIZE(2,1), GET_TEXTF(NUDGE_NOZZLE))
       .enabled(!isPrinting()).tag(5).button( BTN_POS(1,5), BTN_SIZE(2,1), GET_TEXTF(LOAD_SYRINGE))
       .enabled(!isPrinting()).tag(6).button( BTN_POS(1,6), BTN_SIZE(2,1), GET_TEXTF(RELEASE_XY_AXIS))
       .colors(action_btn)    .tag(1).button( BTN_POS(1,7), BTN_SIZE(2,1), GET_TEXTF(BACK));
  }
  #undef GRID_COLS
  #undef GRID_ROWS
}

bool TuneMenu::onTouchEnd(uint8_t tag) {
  switch (tag) {
    case 1: GOTO_PREVIOUS();                    break;
    case 2: GOTO_SCREEN(FeedratePercentScreen); break;
    case 3: GOTO_SCREEN(TemperatureScreen);     break;
    case 4: GOTO_SCREEN(NudgeNozzleScreen);     break;
    case 5: GOTO_SCREEN(BioConfirmHomeXYZ);     break;
    case 6: StatusScreen::unlockMotors();       break;
    default:
      return false;
  }
  return true;
}

#endif // LULZBOT_TOUCH_UI
