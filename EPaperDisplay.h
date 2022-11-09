#ifndef EPaperDisplay_H
#define EPaperDisplay_H
/* 7.5" Waveshare
  ####################################################################################################################################
  This software, the ideas and concepts is Copyright (c) David Bird 2018. All rights to this software are reserved.

  Any redistribution or reproduction of any part or all of the contents in any form is prohibited other than the following:
  1. You may print or download to a local hard disk extracts for your personal and non-commercial use only.
  2. You may copy the content to individual third parties for their personal use, but only if you acknowledge the author David Bird as the source of the material.
  3. You may not, except with my express written permission, distribute or commercially exploit the content.
  4. You may not transmit it or store it in any other website or other form of electronic retrieval system for commercial purposes.

  The above copyright ('as annotated') notice and this permission notice shall be included in all copies or substantial portions of the Software and where the
  software use is visible to an end-user.

  THE SOFTWARE IS PROVIDED "AS IS" FOR PRIVATE USE ONLY, IT IS NOT FOR COMMERCIAL USE IN WHOLE OR PART OR CONCEPT. FOR PERSONAL USE IT IS SUPPLIED WITHOUT WARRANTY
  OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  See more at http://www.dsbird.org.uk
*/

#include  <Arduino.h>
#include "TypesAndDefs.h"
#include "Label.h"


//Epaper Display includes and defines
    #define SCREEN_WIDTH  640             // Set for landscape mode
    #define SCREEN_HEIGHT 384
    //Connections wiring for E-Paper-Display esp32 dev module (Firebeetle)
    #define EPD_BUSY  4  // to EPD BUSY
    #define EPD_CS  15  // to EPD CS
    #define EPD_RST   16 // to EPD RST
    #define EPD_DC    17 // to EPD DC
    #define EPD_SCK   14 // to EPD CLK
    #define EPD_MISO  12 // Master-In Slave-Out not used, as no data from display
    #define EPD_MOSI  13 // to EPD DIN

    #define  ENABLE_GxEPD2_display 0
    #include "GxEPD2_3C.h"
    //#include "GxEPD2_display_selection_new_style.h"
    #include "U8g2_for_Adafruit_GFX.h"
    extern U8G2_FOR_ADAFRUIT_GFX print_display_u8g2;
    GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT> extern display; // 3-colour displays
    //enum alignment {LEFT, RIGHT, CENTER};
    // Using fonts:
    // u8g2_font_helvB08_tf
    // u8g2_font_helvB10_tf
    // u8g2_font_helvB12_tf
    // u8g2_font_helvB14_tf
    // u8g2_font_helvB18_tf
    // u8g2_font_helvB24_tf


// #########################################################################################

/// @brief Initialization function for EPaper Display with selectable baudrate
/// @param baudrate baudrate parameter
void InitDisplay(int baudrate);

/// @brief Initialization function for EPaper Display
void InitDisplay();


// #########################################################################################

/// @brief Initialization function for U8g2 fonts, binding to epd
void InitU8g2fonts();

// #########################################################################################

/// @brief select core to run display function and display buffer to epd
/// @param core core to run on
void displayToEpaper(uint8_t core);

// #########################################################################################

/// @brief Display buffer to epd, code runs on core 0 by default
void displayToEpaper();

// #########################################################################################

// /// @brief Display buffer to serial, code runs on core 0 by default
// /// @param core core to run on
// void serial_display(uint8_t core);

// #########################################################################################

// /// @brief Display buffer to serial, code runs on core 0 by default
// void serial_display();
void serial_displayTaskCode();

void drawString(int x, int y, String text, alignment align);

void drawStringMaxWidth(int x, int y, unsigned int text_width, String text, alignment align);

void Nodata(int x, int y, bool IconSize, String IconName);

void DrawGraph(int x_pos, int y_pos, int gwidth, int gheight, float Y1Min, float Y1Max, String title, float DataArray[], int readings, boolean auto_scale, boolean barchart_mode);

void drawString(int x, int y, String text, alignment align);

void drawStringMaxWidth(int x, int y, unsigned int text_width, String text, alignment align);

void DrawGraph(int x_pos, int y_pos, int gwidth, int gheight, float Y1Min, float Y1Max, String title, float DataArray[], int readings, boolean auto_scale, boolean barchart_mode);

#endif
