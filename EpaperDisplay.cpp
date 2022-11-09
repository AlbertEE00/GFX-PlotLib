#include "EPaperDisplay.h"


U8G2_FOR_ADAFRUIT_GFX print_display_u8g2;
GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT> display(GxEPD2_750c(/*CS=*/ EPD_CS, /*DC=*/ EPD_DC, /*RST=*/ EPD_RST, /*BUSY=*/ EPD_BUSY)); // 3-colour displays

void InitDisplay(int baudrate){
  display.init(baudrate, true, 2, false);
  // display.init(); for older Waveshare HAT's
  SPI.end();
  SPI.begin(EPD_SCK, EPD_MISO, EPD_MOSI, EPD_CS); 
  display.fillScreen(GxEPD_WHITE);     
}

void InitDisplay(){
  display.init(115200, true, 2, false);
  // display.init(); for older Waveshare HAT's
  SPI.end();
  SPI.begin(EPD_SCK, EPD_MISO, EPD_MOSI, EPD_CS); 
  display.fillScreen(GxEPD_WHITE);     
}

// void displayToEpaperTaskCode( void * parameter)
// {
//   display.display();
//   vTaskDelete(NULL); // to delete the task

// }

// void displayToEpaper(uint8_t core)
// {
//   TaskHandle_t displaytask;
//   xTaskCreatePinnedToCore(
//             displayToEpaperTaskCode, /* Function to implement the task */
//             "Task1", /* Name of the task */
//             10000,  /* Stack size in words */
//             NULL,  /* Task input parameter */
//             0,  /* Priority of the task */
//             &displaytask,  /* Task handle. */
//             core); /* Core where the task should run */

//   delay(2); // delay to initialize task
//   while(!display.isDisplayWriteComplete()) // check to see if buffer to epd write complete
//   {
//     delay(2);
//   }
// }
// void displayToEpaper()
// {
//   TaskHandle_t displaytask;
//   display.setDisplayWriteComplete(false);
//   xTaskCreatePinnedToCore(
//             displayToEpaperTaskCode, /* Function to implement the task */
//             "Task1", /* Name of the task */
//             10000,  /* Stack size in words */
//             NULL,  /* Task input parameter */
//             0,  /* Priority of the task */
//             &displaytask,  /* Task handle. */
//             0); /* Core where the task should run */

//   delay(2); // delay to initialize task
//   while(!display.isDisplayWriteComplete()) // check to see if buffer to epd write complete
//   { 
//     // Serial.println("this is blocking");
//     delay(2);
//   }
// }

// void serial_displayTaskCode()
// {
//   uint8_t* black_buff_arr;
//   uint8_t* red_buff_array;
//   black_buff_arr = display.getblackbuffer();
//   red_buff_array = display.getcolorbuffer();
  
//   uint8_t Display_data[SCREEN_HEIGHT*SCREEN_WIDTH/8] = {0};

//   Serial.println("Begin_Display_black_data");
//   for(int i=0;i<384;i++)
//   {
//     for(int j=0;j<80;j++)
//     {
//       Serial.println(black_buff_arr[i*80+j],HEX);
//     }
//   }
//   Serial.println("End_Display_black_data");
//   Serial.println("");
//   //delay(100);
//   Serial.println("Begin_Display_color_data");
//   for(int i=0;i<384;i++)
//   {
//     for(int j=0;j<80;j++)
//     {
//       Serial.println(red_buff_array[i*80+j],HEX);
//     }
//   }
//   Serial.println("End_Display_color_data");
//   Serial.println("End_Display_serial");
// }

// void serial_display(uint8_t core)
// {
//   TaskHandle_t displaytask;
//   xTaskCreatePinnedToCore(
//             displayToEpaperTaskCode, /* Function to implement the task */
//             "Task1", /* Name of the task */
//             100,  /* Stack size in words */
//             NULL,  /* Task input parameter */
//             0,  /* Priority of the task */
//             &displaytask,  /* Task handle. */
//             core); /* Core where the task should run */
//   vTaskDelete(displaytask);
// }

// void serial_display()
// {
//   TaskHandle_t displaytask;
//   xTaskCreatePinnedToCore(
//             serial_displayTaskCode, /* Function to implement the task */
//             "Task1", /* Name of the task */
//             100,  /* Stack size in words */
//             NULL,  /* Task input parameter */
//             0,  /* Priority of the task */
//             &displaytask,  /* Task handle. */
//             0); /* Core where the task should run */
//   vTaskDelete(displaytask);
// }



void InitU8g2fonts()
{
  print_display_u8g2.begin(display); // connect u8g2 procedures to Adafruit GFX
  print_display_u8g2.setFontMode(1);                  // use u8g2 transparent mode (this is default)
  print_display_u8g2.setFontDirection(0);             // left to right (this is default)
  print_display_u8g2.setForegroundColor(GxEPD_BLACK); // apply Adafruit GFX color
  print_display_u8g2.setBackgroundColor(GxEPD_WHITE); // apply Adafruit GFX color
  print_display_u8g2.setFont(u8g2_font_helvB10_tf);   // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
}



//#########################################################################################
void drawString(int x, int y, String text, alignment align) {
  //int16_t  x1, y1; //the bounds of x,y and w and h of the variable 'text' in pixels.
  uint16_t w, h;
  display.setTextWrap(false);
  //w = print_display_u8g2.getUTF8Width(text.c_str());
  w = print_display_u8g2.getUTF8Width(text.c_str()); //Use U8G2Fonts Width
  h = getFontSize(&print_display_u8g2);
  if (align == RIGHT)  x = x - w;
  if (align == CENTER) x = x - w / 2;
  print_display_u8g2.setCursor(x, y + h);
  print_display_u8g2.print(text);
}
//#########################################################################################
void drawStringMaxWidth(int x, int y, unsigned int text_width, String text, alignment align) {
  
  uint16_t w, h;
  display.setTextWrap(false);
  //w = print_display_u8g2.getUTF8Width(text.c_str());
  w = print_display_u8g2.getUTF8Width(text.c_str()); //Use U8G2Fonts Width
  h = getFontSize(&print_display_u8g2);
  if (align == RIGHT)  x = x - w;
  if (align == CENTER) x = x - w / 2;
  print_display_u8g2.setCursor(x, y);
  if (text.length() > text_width * 2) {
    print_display_u8g2.setFont(u8g2_font_helvB10_tf);
    //text_width = 42;
    y = y - 3;
  }
  print_display_u8g2.println(text.substring(0, text_width));
  if (text.length() > text_width) {
    print_display_u8g2.setCursor(x, y + h + 1+getFontSize(&print_display_u8g2));
    String secondLine = text.substring(text_width);
    secondLine.trim(); // Remove any leading spaces
    print_display_u8g2.println(secondLine);
  }
}

void DrawGraph(int x_pos, int y_pos, int gwidth, int gheight, float Y1Min, float Y1Max, String title, float DataArray[], int readings, boolean auto_scale, boolean barchart_mode) {
#define auto_scale_margin 0 // Sets the autoscale increment, so axis steps up in units of e.g. 3
#define y_minor_axis 5      // 5 y-axis division markers
  int maxYscale = -10000;
  int minYscale =  10000;
  int last_x, last_y;
  float x2, y2;
  if (auto_scale == true) {
    for (int i = 1; i < readings; i++ ) { // Adjusted graph range
      if (DataArray[i] >= maxYscale) maxYscale = DataArray[i];
      if (DataArray[i] <= minYscale) minYscale = DataArray[i];
    }
    maxYscale = round(maxYscale + auto_scale_margin); // Auto scale the graph and round to the nearest value defined, default was Y1Max
    Y1Max = round(maxYscale + 0.5);
    if (minYscale != 0) minYscale = round(minYscale - auto_scale_margin); // Auto scale the graph and round to the nearest value defined, default was Y1Min
    Y1Min = round(minYscale);
  }
  // Draw the graph
  last_x = x_pos + 1;
  last_y = y_pos + (Y1Max - constrain(DataArray[1], Y1Min, Y1Max)) / (Y1Max - Y1Min) * gheight;
  display.drawRect(x_pos, y_pos, gwidth + 3, gheight + 2, GxEPD_BLACK);
  drawString(x_pos + gwidth / 2, y_pos - 13, title, CENTER);
  // Draw the data
  for (int gx = 1; gx < readings; gx++) {
    x2 = x_pos + gx * gwidth / (readings - 1) - 1 ; // max_readings is the global variable that sets the maximum data that can be plotted
    y2 = y_pos + (Y1Max - constrain(DataArray[gx], Y1Min, Y1Max)) / (Y1Max - Y1Min) * gheight + 1;
    if (barchart_mode) {
      display.fillRect(x2, y2, (gwidth / readings) - 1, y_pos + gheight - y2 + 2, GxEPD_RED);
    } else {
      display.drawLine(last_x, last_y, x2, y2, GxEPD_RED);
    }
    last_x = x2;
    last_y = y2;
  }
  //Draw the Y-axis scale
#define number_of_dashes 20
  for (int spacing = 0; spacing <= y_minor_axis; spacing++) {
    for (int j = 0; j < number_of_dashes; j++) { // Draw dashed graph grid lines
      if (spacing < y_minor_axis) display.drawFastHLine((x_pos + 3 + j * gwidth / number_of_dashes), y_pos + (gheight * spacing / y_minor_axis), gwidth / (2 * number_of_dashes), GxEPD_BLACK);
    }
    if (Y1Min < 1 && Y1Max < 10)
      drawString(x_pos - 3, y_pos + gheight * spacing / y_minor_axis - 5, String((Y1Max - (float)(Y1Max - Y1Min) / y_minor_axis * spacing + 0.01), 1), RIGHT);
    else
      drawString(x_pos - 3, y_pos + gheight * spacing / y_minor_axis - 5, String((Y1Max - (float)(Y1Max - Y1Min) / y_minor_axis * spacing + 0.01), 0), RIGHT);
  }
  for (int i = 0; i <= 2; i++) {
    drawString(15 + x_pos + gwidth / 3 * i, y_pos + gheight + 3, String(i), LEFT);
  }
  //drawString(x_pos + gwidth / 2, y_pos + gheight + 14, TXT_DAYS, CENTER);
}