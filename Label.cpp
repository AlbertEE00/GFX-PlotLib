#include "Label.h"


// Label::Label() = default;

// Label::Label(uint16_t x, uint16_t y, String text, uint16_t color, uint16_t width,uint16_t height, labelType type)
// : type(type),text(text),align(CENTER),x(x),y(y),width(width),height(height),color(color)
// {
//     if(type == Title){this->bold = true;this->underline = true;} else{this->bold = false;this->underline = false;}
//     if(type == yAxis) this->direction = 3; else{this->direction == 0;}
// }

void setFontSize(U8G2_FOR_ADAFRUIT_GFX& print_epd_u8g2,uint8_t fontsize, bool bold)
{
    switch (fontsize)
    {
    case 2:
        print_epd_u8g2.setFont(u8g2_font_pearfont_tr);
        break;
    case 3:
        print_epd_u8g2.setFont(u8g2_font_pearfont_tr);
        break;
    case 4:
        print_epd_u8g2.setFont(u8g2_font_u8glib_4_tf);
        break;
    case 5:
        print_epd_u8g2.setFont(u8g2_font_4x6_tf);
        break;
    case 6:
        print_epd_u8g2.setFont(u8g2_font_5x8_tf);
        break;
    case 7:
        print_epd_u8g2.setFont(u8g2_font_6x10_tf);
        break;
    case 8:
        print_epd_u8g2.setFont(u8g2_font_t0_11_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_t0_11b_tf);
        break;
    case 9:
        print_epd_u8g2.setFont(u8g2_font_6x13_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_6x13B_tf);
        break;
    case 10:
        print_epd_u8g2.setFont(u8g2_font_7x14_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_7x14B_tf);
        break;
    case 11:
        print_epd_u8g2.setFont(u8g2_font_t0_17_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_t0_17b_tf);
        break;
    case 12:
        print_epd_u8g2.setFont(u8g2_font_helvR12_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB12_tf);
        break;
    case 13:
        print_epd_u8g2.setFont(u8g2_font_helvR12_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB12_tf);
        break;
    case 14:
        print_epd_u8g2.setFont(u8g2_font_helvR12_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB12_tf);
        break;
    case 15:
        print_epd_u8g2.setFont(u8g2_font_helvR14_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB14_tf);
        break;
    case 16:
        print_epd_u8g2.setFont(u8g2_font_helvR14_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB14_tf);
        break;
    case 17:
        print_epd_u8g2.setFont(u8g2_font_helvR18_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB18_tf);
        break;
    default:
        print_epd_u8g2.setFont(u8g2_font_helvR18_tf);
        if(bold) print_epd_u8g2.setFont(u8g2_font_helvB18_tf);
        break;
    }
}

uint8_t getFontSize(U8G2_FOR_ADAFRUIT_GFX *u8g2)
{
    return u8g2->u8g2.font_info.ascent_A - u8g2->u8g2.font_info.descent_g;
}

const uint8_t * getFont(U8G2_FOR_ADAFRUIT_GFX *u8g2)
{
    return u8g2->u8g2.font;
}

void addVSpace(short vspace,U8G2_FOR_ADAFRUIT_GFX *u8g2)            // set u8g2 font
    { 
    switch(u8g2->u8g2.font_decode.dir)
    {
        case 0: // 0 deg
        u8g2->ty += vspace;
        break;
        case 1: // 90 deg
        u8g2->tx -= vspace;
        break;
        case 2: // 180 deg
        u8g2->ty -= vspace;
        break;
        case 3: // 207 deg
        u8g2->tx += vspace;
        break;
    }  

    }
    //TODO: make this function work outside of library external access
void addHSpace(short hspace,U8G2_FOR_ADAFRUIT_GFX *u8g2)            // set u8g2 font
    { 
    switch(u8g2->u8g2.font_decode.dir)
    {
        case 0: // 0 deg
        u8g2->tx += hspace;
        break;
        case 1: // 90 deg
        u8g2->ty += hspace;
        break;
        case 2: // 180 deg
        u8g2->tx -= hspace;
        break;
        case 3: // 207 deg
        u8g2->ty -= hspace;
        break;
    }
    }

void drawStringBlock(Adafruit_GFX *gfx, U8G2_FOR_ADAFRUIT_GFX *u8g2, float x, float y, String str, float blockWidth, float blockHeight, alignment widthAlign, uint8_t direction, bool underLine, bool bold,GFX_COLOR fgColor,GFX_COLOR bkgColor)
{
    GFX_COLOR tempFore =  u8g2->u8g2.font_decode.fg_color, tempBack=u8g2->u8g2.font_decode.bg_color;
    u8g2->setForegroundColor(fgColor);  u8g2->setBackgroundColor(bkgColor);
    drawStringBlock(gfx, u8g2,  x,  y,  str,  blockWidth,  blockHeight,  widthAlign,  direction, underLine, bold);
}

void drawStringBlock(Adafruit_GFX* gfx, U8G2_FOR_ADAFRUIT_GFX* u8g2, float x, float y, String str, float blockWidth, float blockHeight, alignment widthAlign, uint8_t direction,bool underLine,bool bold)
{
    float pixMarginW = 2.0f;
    float pixMarginH = 1.0f;
    int newX = 0, newY = 0;
    float fontSize = float(getFontSize(u8g2));
    //Serial << fontSize << endl;

    float stringWidth =  float(u8g2->getUTF8Width(str.c_str()));
    //Serial << stringWidth << endl;
    if(direction == 4) direction = u8g2->getFontDirection();
    u8g2->setFontDirection(direction);

    if(blockWidth == 0.0f) blockWidth = stringWidth + 2.0f*pixMarginW;
    if(blockHeight == 0.0f) blockHeight = fontSize + 2.0f*pixMarginH;

    if(stringWidth>blockWidth || fontSize>blockHeight)
    {
        //Serial << "BLOCK DIMENSIONS TO SMALL FOR STRING"<<endl;
        return;
    }
    float widthOffset = 0, heightOffset = 0;
    heightOffset = (blockHeight + fontSize)/2.0;
    switch (widthAlign)
    {
    case LEFT/* constant-expression */:
        widthOffset = (pixMarginW); // two pixel margin space
        break;
    case CENTER/* constant-expression */:
        widthOffset = (blockWidth/2.0f - stringWidth/2.0f);
        break;
    case RIGHT/* constant-expression */:
        widthOffset = (blockWidth - stringWidth - pixMarginW); // one pixel margin space
        break;
    default:
        break;
    }

    switch (direction)
    {
    case 0 /* 0° */:
        newX = int(x + widthOffset);
        newY = int(y + heightOffset);
        u8g2->drawUTF8(newX,newY,str.c_str());
        if(underLine) gfx->drawFastHLine(newX,newY,stringWidth,BLACK);
        // Serial << "newX: " << newX << " , newY: " << newY << " , heightOffset: " << heightOffset << ", widthOffset: " << widthOffset << endl;
        // drawFastHLine(newX,newY,30,RED); 
        break;
    case 1/* 90° */:
        newX = int(x - heightOffset);
        newY = int(y + widthOffset);
        u8g2->drawUTF8(newX,newY,str.c_str());
        if(underLine) gfx->drawFastVLine(newX,newY,stringWidth,BLACK);
        // Serial << "newX: " << newX << " , newY: " << newY << " , heightOffset: " << heightOffset << ", widthOffset: " << widthOffset << endl;
        // drawFastHLine(newX,newY,30,RED); 
        break;
    case 2/* 180° */:
        newX = int(x - widthOffset);
        newY = int(y - heightOffset);
        u8g2->drawUTF8(newX,newY,str.c_str());
        if(underLine) gfx->drawFastHLine(newX-stringWidth,newY,stringWidth,BLACK);
        // Serial << "newX: " << newX << " , newY: " << newY << " , heightOffset: " << heightOffset << ", widthOffset: " << widthOffset << endl;
        // drawFastHLine(newX,newY,30,RED); 
        break;
    case 3/* 270° */:
        newX = int(x + heightOffset);
        newY = int(y - widthOffset);
        u8g2->drawUTF8(newX,newY,str.c_str());
        if(underLine) gfx->drawFastVLine(newX,newY-stringWidth,stringWidth,BLACK);
        // Serial << "newX: " << newX << " , newY: " << newY << " , heightOffset: " << heightOffset << ", widthOffset: " << widthOffset << endl; 
        // drawFastHLine(newX,newY,30,RED);
        break;
    default:
        break;
    }
}

void Label::show()
{
    if(text == "") return;
    const uint8_t * prevFont = getFont(u8g2);
    setFontSize(*u8g2,fontSize,bold);
    drawStringBlock(plot,u8g2,x,y,text,width,height,align,direction,underline,bold);
    u8g2->setFont(prevFont);
}

Label::Label() = default;

Label::Label(Adafruit_GFX *plot, U8G2_FOR_ADAFRUIT_GFX *u8g2) : plot{plot}, u8g2{u8g2} {}

void Label::setLabel(uint16_t x, uint16_t y, uint16_t width, uint16_t height, String &text, labelType type, uint16_t color, uint8_t fontSize, bool bold, bool underline)
{
    this->x=x;  this->y=y;  this->width=width;  this->height=height;  this->text=text;  
    this->type=type;    this->fg_color=color;  this->fontSize=fontSize;    this->bold=bold;    this->underline=underline;
    if(type == Title){this->bold = true;this->underline = true;this->direction == 0;}
    else if(type == yAxis) this->direction = 3;
    else if(type == xAxis || type == description){this->direction == 0;}
}
// void Label::setLabel(uint16_t x, uint16_t y, String text, uint16_t color, uint16_t width,uint16_t height, labelType type)
// : type(type),text(text),align(CENTER),x(x),y(y),width(width),height(height),color(color)
// {
//     if(type == Title){this->bold = true;this->underline = true;} else{this->bold = false;this->underline = false;}
//     if(type == yAxis) this->direction = 3; else{this->direction == 0;}
// }