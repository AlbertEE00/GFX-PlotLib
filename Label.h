#pragma once

#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "U8g2_for_Adafruit_GFX.h"
#include "Vector.h"
#include "TypesAndDefs.h"

enum labelType {Title,xAxis,yAxis,description};
enum alignment {LEFT, RIGHT, CENTER,TOP,BOTTOM,MIDDEL};

void drawStringBlock(Adafruit_GFX *gfx, U8G2_FOR_ADAFRUIT_GFX *u8g2, float x, float y, String str, float blockWidth, float blockHeight, alignment widthAlign, uint8_t direction, bool underLine, bool bold, GFX_COLOR fgColor, GFX_COLOR bkgColor);
void drawStringBlock(Adafruit_GFX* gfx, U8G2_FOR_ADAFRUIT_GFX* u8g2, float x, float y, String str, float blockWidth, float blockHeight, alignment widthAlign, uint8_t direction,bool underLine,bool bold);
void setFontSize(U8G2_FOR_ADAFRUIT_GFX& print_epd_u8g2,uint8_t fontsize, bool bold);
uint8_t getFontSize(U8G2_FOR_ADAFRUIT_GFX *u8g2);
const uint8_t *getFont(U8G2_FOR_ADAFRUIT_GFX *u8g2);

void addVSpace(short vspace, U8G2_FOR_ADAFRUIT_GFX *u8g2);
void addHSpace(short hspace, U8G2_FOR_ADAFRUIT_GFX *u8g2);


struct Label
{
    public:
    uint16_t x,y,width,height;
    GFX_COLOR fg_color,bkg_color;
    uint8_t fontSize=8,direction=0;
    alignment align=CENTER;
    labelType type=xAxis;
    String text="";
    bool bold=false,underline=false;
    Adafruit_GFX* plot;
    U8G2_FOR_ADAFRUIT_GFX* u8g2;
    Label();
    Label(Adafruit_GFX* plot, U8G2_FOR_ADAFRUIT_GFX* u8g2);
    void setLabel(uint16_t x, uint16_t y, uint16_t width,uint16_t height, String &text,labelType type=xAxis, uint16_t color = BLACK,uint8_t fontSize=8, bool bold = false, bool underline=false);
    void show();
};