#pragma once
#include "Arduino.h"

// color definitions for GxEPD, GxEPD2 and GxEPD_HD, values correspond to RGB565 values for TFTs
#define BLACK     0x0000
#define WHITE      0xFFFF
// some controllers for b/w EPDs support grey levels
#define DARKGREY   0x7BEF // 128, 128, 128
#define LIGHTGREY  0xC618 // 192, 192, 192
// values for 3-color or 7-color EPDs
#define RED        0xF800 // 255,   0,   0
#define YELLOW     0xFFE0 // 255, 255,   0 !!no longer same as GxEPD_RED!!
#define COLORED    GxEPD_RED
// values for 7-color EPDs only
#define BLUE       0x001F //   0,   0, 255
#define GREEN      0x07E0 //   0, 255,   0
#define ORANGE     0xFD20 // 255, 165,   0
#define BLACK_EPD 0x00 //raw display color for 7.5
#define WHITE_EPD 0x33 //raw display color for 7.5
#define RED_EPD   0x44 //raw display color for 7.5

using GFX_COLOR = uint16_t;
using DataType = float;
using DispCoordType = uint16_t;

