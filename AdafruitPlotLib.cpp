#include "AdafruitPlotLib.h"

void AdafruitPlot::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
    {
        display->drawPixel(x+this->x, y+this->y, color);
    }
}

// DataType roundTo1Dec(DataType var)
// {
//     // 37.66666 * 100 =3766.66
//     // 3766.66 + .5 =3767.16    for rounding off value
//     // then type cast to int so value is 3767
//     // then divided by 100 so the value converted into 37.67
//     DataType value = (int)(var * 10 + .5);
//     return (DataType)value / 10;
// }

void Subplot::show()
{
    fillRect(0,0,width(),height(),WHITE); // fill backround color of subplot
    drawRect(0,0,width(),height(),BLACK); // draw outline of subplot
    axis.drawAxis();
    DataType interW = DataType(axis.axisWidth())/tickFreq;
    DataType interH = DataType(axis.axisHeight())/tickFreq;

    for(DataType i=1;i<=tickFreq;i+=1.0)
    {
        drawLine(axis.x+int16_t(round(interW*i)),axis.bl_y,axis.x+int16_t(round(interW*i)),int16_t(round(DataType(axis.bl_y)-0.02*DataType(axis.axisHeight()))),RED);
        drawLine(axis.x,axis.y+int16_t(round(tickFreq*interH-interH*(i))),int16_t(round(DataType(axis.x)+0.02*DataType(axis.axisHeight()))),axis.y+int16_t(round(tickFreq*interH-interH*i)),RED);
    }
    

    DataType maxBox = (h-axis.bl_y)*0.3*0.75; // 0.75 to convert pt to pixel
    const uint8_t * prevFont = getFont(&u8g2);
    setFontSize(u8g2,uint8_t(maxBox),false);
    DataType numberintW = axis.limits.xRange()/tickFreq;
    DataType numberintWmin = axis.limits.xLim().min;
    DataType numberintH = axis.limits.yRange()/tickFreq;
    DataType numberintHmin = axis.limits.yLim().min;
    if(!manualTicks)for(DataType i=0;i<=tickFreq;i+=tickLableFreq)
    {
        drawStringBlock(this,&u8g2,axis.x+int16_t(round(interW*(i-1.0))),axis.y+axis.axisHeight(),String((numberintWmin+numberintW*i),1),int16_t(round(2*interW)),0.0,CENTER,0,false,false);
        drawStringBlock(this,&u8g2,axis.x*0.4,int16_t(round((double(axis.bl_y)-interH*(i+1)))),String((numberintHmin+numberintH*(i)),1),axis.x*0.6,int16_t(round(2*interH)),RIGHT,0,false,false);
    }
    u8g2.setFont(prevFont);
    axis.show(); // draw the graph
    xLabel.show();yLabel.show();title.show(); // draw labels
}

void Subplot::setTitle(String text,GFX_COLOR color)
{
    title.setLabel(axis.x,0,axis.axisWidth(),0.0,text,Title,color,axis.y*titleLabelfraction*0.75);
}

void Subplot::setYLabel(String text,GFX_COLOR color)
{
    yLabel.setLabel(0,axis.bl_y,axis.axisHeight(),0.0,text,yAxis,color,(h-axis.bl_y)*axisLabelfraction*0.75);

}

void Subplot::setXLabel(String text,GFX_COLOR color)
{
    xLabel.setLabel(axis.x,h-getFontSize(&u8g2)-2,axis.axisWidth(),0.0,text,xAxis,color,(h-axis.bl_y)*axisLabelfraction*0.75); 
}
void Subplot::setLabels(String title, String x_label, String y_label)
{
    setTitle(title),setXLabel(x_label),setYLabel(y_label);
}
void Subplot::setLabels(String title, String x_label, String y_label, GFX_COLOR colorT, GFX_COLOR colorX, GFX_COLOR colorY)
{
    setTitle(title,colorT),setXLabel(x_label,colorX),setYLabel(y_label,colorY);
}

void Subplot::setTitle(String text)
{
    title.setLabel(axis.x,0,axis.axisWidth(),0.0,text,Title,textColor,axis.y*titleLabelfraction*0.75);
}

void Subplot::setYLabel(String text)
{
    yLabel.setLabel(0,axis.bl_y,axis.axisHeight(),0.0,text,yAxis,textColor,(h-axis.bl_y)*axisLabelfraction*0.75);

}

void Subplot::setXLabel(String text)
{
    auto tempfont = u8g2.u8g2.font;
    setFontSize(u8g2,(h-axis.bl_y)*axisLabelfraction*0.75,false);
    xLabel.setLabel(axis.x,h-getFontSize(&u8g2)-4,axis.axisWidth(),0.0,text,xAxis,textColor,(h-axis.bl_y)*axisLabelfraction*0.75);
    u8g2.setFont(tempfont);
}

void Subplot::legend(String label, size_t index)
{
    axis.data[index]->setLabel(label,textColor,axis.bkg_color);
}
void Subplot::legend(String label, size_t index,GFX_COLOR color)
{
    axis.data[index]->setLabel(label,color,axis.bkg_color);
}

void Subplot::setTickColor(GFX_COLOR color)
{
    tickColor = color;
}
void Subplot::setTickFreq(DataType TF, DataType TLF)
{
    tickFreq = TF; tickLableFreq = TLF;
}

void Subplot::setLim(DataType minx, DataType maxx, DataType miny,DataType maxy)
{
    axis.limits.setLim( minx,  maxx,  miny, maxy);
}
void Subplot::setYLim(DataType min, DataType max)
{
     axis.limits.setYLim(min,max);
}
void Subplot::setXLim(DataType min, DataType max)
{
    axis.limits.setXLim(min,max);
}


Subplot::Subplot(DispCoordType x, DispCoordType y, DispCoordType width, DispCoordType height, Adafruit_GFX &plotfig) 
: Adafruit_GFX(width,height), plotfig{&plotfig} ,x(x), y(y), w(width), h(height), 
axis(*this,round(DataType(height)*0.23),round(DataType(height)*0.10),round(DataType(width)-(DataType(height)*0.3)),round(DataType(height)*(1-0.1-0.15)),BLACK,WHITE),
yLabel(this,&u8g2),xLabel(this,&u8g2),title(this,&u8g2),description(this,&u8g2)
{
  u8g2.begin(*this); // connect u8g2 procedures to Adafruit GFX
  u8g2.setFontMode(1);                  // use u8g2 transparent mode (this is default)
  u8g2.setFontDirection(0);             // left to right (this is default)
  u8g2.setForegroundColor(GxEPD_BLACK); // apply Adafruit GFX color
  u8g2.setBackgroundColor(GxEPD_WHITE); // apply Adafruit GFX color
  u8g2.setFont(u8g2_font_helvB08_tf);   // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
}

void Subplot::setDisplay(Adafruit_GFX &plotfig)
{
    this->plotfig = &plotfig;
}

void Subplot::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
    {
        plotfig->drawPixel(x+this->x, y+this->y, color);
    }
}

PlotData<DataType> *Subplot::plot(PlotData<DataType> &data)
{
    return axis.plot(data);
}


Axis::Axis(Adafruit_GFX &sub_plot, uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t axis_color, uint16_t bkg_color) : 
Adafruit_GFX(width,height), x(x), y(y), w(width), h(height),axis_color(axis_color),bkg_color(bkg_color),_subplot(&sub_plot),bl_x(x),bl_y(y+height-1)
{
}

Axis::~Axis()
{
    for(int i=0;i<data_plot_cnt;i++)
    {
        if(data[i]!=NULL) delete data[i];
    }
}

void Axis::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
    _subplot->drawPixel(x+this->x, y+this->y, color);
}



//generic plot
PlotData<DataType>* Axis::plot(PlotData<DataType> &data)
{
    data_plot_cnt+=1;
    this->data[data_plot_cnt-1] = new PlotData<DataType>(data);
    limits.updateLimits(*(this->data[data_plot_cnt-1]));
    return ((this->data[data_plot_cnt-1]));
}

void Axis::drawAxis()
{
    fillRect(0,0,axisWidth(),axisHeight(),bkg_color);
    //drawRect(0,0,axisWidth(),axisHeight(),axis_color);
    drawLine(0,0,0,axisHeight(),axis_color);
    drawLine(0,axisHeight()-1,axisWidth(),axisHeight()-1,axis_color);
}

PlotData<DataType>* Subplot::operator[](size_t index)
{
    if(index < axis.data_plot_cnt)
        return (axis.data[index]);
    else return nullptr;
}

PlotData<DataType>* Subplot::operator[](String index)
{
    int i;
    for(i = 0;i<=axis.data_plot_cnt;i++)
    {
        if(i>=axis.data_plot_cnt) return nullptr;
        if(index == axis.data[i]->label.text) break;
    }
    
    return (axis.data[i]);
}

size_t Subplot::plotCnt()
{
    return axis.data_plot_cnt;
}

uint16_t Axis::get_x()
{
    return x;
}

uint16_t Axis::get_y()
{
    return y;
}

uint16_t Axis::axisWidth()
{
    return width();
}

uint16_t Axis::axisHeight()
{
   return height();
}

void Axis::linePlot(PlotData<DataType> &dp)
{
    //Serial << " len = " << dp.length() << " dp.yLim().max = " << dp.yLim().max << " dp.yLim().max = " << dp.yLim().min <<endl;
    for(auto i : range(0,dp.length()-1))
    {
        auto elem1 = project(dp[i]);
        auto elem2 = project(dp[i+1]);
        DrawThickLine(*this,elem1.x,elem1.y,elem2.x,elem2.y,dp.linewidth,dp.color);
        if(dp.marker!=none){plotpoint(dp,i),plotpoint(dp,i+1);}
    }
}
void Axis::scatterPlot(PlotData<DataType> &dp)
{
    //Serial << " len = " << dp.length() << " dp.yLim().max = " << dp.yLim().max << " dp.yLim().max = " << dp.yLim().min <<endl;
    for(auto i : range(0,dp.length()-1))
    {
        plotpoint(dp,i);
        plotpoint(dp,i+1);
    }
}

void Axis::Bars(PlotData<DataType> &dp)
{

}



void Axis::plotData(PlotData<DataType> &dp)
{
    switch (dp.plottype)
    {
    case line/* constant-expression */:
        linePlot(dp);
        break;
    case scatter/* constant-expression */:
        scatterPlot(dp);
        break;
    case bars/* constant-expression */:
        Bars(dp);
        break;
    case histogram/* constant-expression */:
        /* code */
        break;
    case pi/* constant-expression */:
        /* code */
        break;
    default:
        break;
    }
    // if(dp.label.text != "")
    // {
    //    dp.label.setLabel(0,axis.bl_y,axis.axisHeight(),0.0,text,yAxis,color,(h-axis.bl_y)*axisLabelfraction*0.75);
    // }

}

DataElement<DispCoordType> Axis::project(const DataElement<DataType> &element)
{
    DataType x =  element.x;
    DataType y =  element.y;
    DispCoordType xCoord = DispCoordType(round(((x-limits.xLim().min)/limits.xRange())*DataType(axisWidth())));
    DispCoordType yCoord = axisHeight() - DispCoordType(round(((y-limits.yLim().min)/limits.yRange())*DataType(axisHeight())));
    return DataElement<DispCoordType>{xCoord,yCoord};

}

void Axis::clear(bool clearData,bool clearAxis)
{
    if(clearData) for(int i = 0;i<data_plot_cnt;i++) 
    {
        delete data[i];
        data[i] = NULL;
    }
    data_plot_cnt = 0;
    label_cnt=0;
    if(clearAxis)drawAxis();
}
void Subplot::clear(bool clearData,bool clearAxis)
{
    axis.clear(clearData,clearAxis);
    axis.limits.setLim(-1,1,-1,1);
    axis.limits.initial = true;
}

void Axis::plotpoint(PlotData<DataType>& dp, unsigned int index)
{
    DataElement<DispCoordType> dataCoord = project(dp[index]);
    DispCoordType x = dataCoord.x , y = dataCoord.y;
    if(x == NAN || y == NAN) return;
    switch (dp.marker)
    {
    case none/* constant-expression */:
        drawPixel(x,y,dp.markercolor);
        break;
    case circle/* constant-expression */:
        if(dp.filledmarker)fillCircle(x,y,dp.markersize,dp.markercolor);
        else drawCircle(x,y,dp.markersize,dp.markercolor);
        break;
    case triangle/* constant-expression */:
        if(dp.filledmarker) fillTriangle(x-dp.markersize/2,y + dp.markersize/2,x+dp.markersize/2,
        y + dp.markersize/2,x,y - dp.markersize/2,dp.markercolor);
        else drawTriangle(x-dp.markersize/2,y + dp.markersize/2,x+dp.markersize/2,
        y + dp.markersize/2,x,y - dp.markersize/2,dp.markercolor);
        break;
    case square/* constant-expression */:
        if(dp.filledmarker) fillRect(x-dp.markersize/2,y-dp.markersize/2,dp.markersize,dp.markersize,dp.markercolor);
        else drawRect(x-dp.markersize/2,y-dp.markersize/2,dp.markersize,dp.markersize,dp.markercolor);
        break;
    default:
        drawPixel(x,y,dp.markercolor);
        break;
    }
}


void Axis::show()
{
    //Serial << data_plot_cnt << endl;
    for(auto i : range(data_plot_cnt)) 
    {
        plotData(*data[i]);
    } 
}




int16_t roundToint16(float v)
{
  return int16_t(round(v));
}

void swapFloat(float a, float b)                                   
  {                                                                 
    float t = a;                                                     
    a = b;                                                         
    b = t;                                                             
  }

void DrawThickLine(Adafruit_GFX &display, float x, float y, float x1, float y1, float size, int color) {

  if(size == 1)
  {
    display.writeLine(roundToint16(x),roundToint16(y),roundToint16(x1),roundToint16(y1),color);
    return;
  }
  else if(size == 2)
  {
    display.writeLine(roundToint16(x),roundToint16(y),roundToint16(x1),roundToint16(y1),color);
    display.writeLine(roundToint16(x+1),roundToint16(y),roundToint16(x1),roundToint16(y1-1),color);
    display.writeLine(roundToint16(x),roundToint16(y-1),roundToint16(x1-1),roundToint16(y1),color);
    return;
  }
    else if(size == 3)
  {
    display.writeLine(roundToint16(x),roundToint16(y),roundToint16(x1),roundToint16(y1),color);
    display.writeLine(roundToint16(x+1),roundToint16(y),roundToint16(x1),roundToint16(y1-1),color);
    display.writeLine(roundToint16(x),roundToint16(y-1),roundToint16(x1-1),roundToint16(y1),color);
    return;
  }
  else if(x==x1)
  {
    int start = int(round(size/2));
    for(int i = -start ;i<size-start-1;i++) display.writeLine(x-start+i,y,x1-start + i,y1,color);
    return;
  }
  else if(y==y1)
  {
    int start = int(round(size/2));
    for(int i = -start;i<size-start-1;i++) display.writeLine(x,y-start + i,x1,y1-start + i,color);
    return;
  }
  else
  {
    float dx = (((size / 2.0) * (y - y1) )/ sqrt(sq(x - x1) + sq(y - y1)));
    float dy = (((size / 2.0) * (x - x1) )/ sqrt(sq(x - x1) + sq(y - y1)));
    //Serial<< " dx: " << dx << " dy: " << dy  <<endl;
    int16_t vx0 = roundToint16(x+dx), vy0 = roundToint16(y - dy), vx1=roundToint16(x-dx), vy1=roundToint16(y+dy), vx2=roundToint16(x1+dx), vy2=roundToint16(y1-dy);
    
    //Serial << vx0 << " " << vy0 << " " << vx1 << " " <<  vy1 << " " <<  vx2 << " " << vy2 << " " << endl;

    display.fillTriangle(vx0, vy0, vx1,  vy1,  vx2, vy2, color);
    vx0 = roundToint16(x-dx), vy0 = roundToint16(y + dy), vx1=roundToint16(x1-dx), vy1=roundToint16(y1+dy), vx2=roundToint16(x1+dx), vy2=roundToint16(y1-dy);
    //Serial << vx0 << " " << vy0 << " " << vx1 << " " <<  vy1 << " " <<  vx2 << " " << vy2 << " " << endl;
    display.fillTriangle(vx0, vy0, vx1,  vy1,  vx2, vy2, color);
  }




}






// AdafruitPlot::AdafruitPlot(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Adafruit_GFX &disp) : Adafruit_GFX(width,height), x(x), y(y), w(width), h(height)
// {
//     //subplot[0] = new SubPlot(this,0,0,width,height);
//     subPlotCnt = 1;
//     AdafruitPlot myplot = *(new AdafruitPlot(10,10,100,100,*display));
//     //myplot(1,2).;

//     display = &disp;
//     u8g2.begin(*this); // connect u8g2 procedures to Adafruit GFX
//     u8g2.setFontMode(1);                  // use u8g2 transparent mode (this is default)
//     setTextWrap(false);
//     u8g2.setFontDirection(0);             // left to right (this is default)
//     u8g2.setForegroundColor(BLACK); // apply Adafruit GFX color
//     u8g2.setBackgroundColor(WHITE); // apply Adafruit GFX color
//     //u8g2.setFont(u8g2_font_helvB10_tf);   // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//     //setFontSize(10,false);
// }
// AdafruitPlot::AdafruitPlot(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t rows, uint8_t colums, Adafruit_GFX &disp): Adafruit_GFX(width,height), x(x), y(y), w(width), h(height)
// {
//     if(rows*colums>MAX_SUBPLOTS) return;
//     uint16_t sp_width = width/colums;
//     uint16_t sp_height = height/rows;

//     for(int i = 0;i<MAX_SUBPLOTS;i++)
//     {
//         subplot[i] = new SubPlot(this,i*sp_width,i*sp_height,sp_width,sp_height);
//     }

//     display = &disp;
//     u8g2.begin(*this); // connect u8g2 procedures to Adafruit GFX
//     u8g2.setFontMode(1);                  // use u8g2 transparent mode (this is default)
//     setTextWrap(false);
//     u8g2.setFontDirection(0);             // left to right (this is default)
//     u8g2.setForegroundColor(BLACK); // apply Adafruit GFX color
//     u8g2.setBackgroundColor(WHITE); // apply Adafruit GFX color
//     //print_epd_u8g2.setFont(u8g2_font_helvB10_tf);   // select u8g2 font from here: https://github.com/olikraus/u8g2/wiki/fntlistall
//     //setFontSize(10,false);
// }

// void AdafruitPlot::drawPixel(int16_t x, int16_t y, uint16_t color)
// {
//     if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
//     {
//         display->drawPixel(x+this->x, y+this->y, color);
//     }
// }



// SubPlot::SubPlot(AdafruitPlot *pp,uint16_t x, uint16_t y, uint16_t width, uint16_t height) : Adafruit_GFX(width,height), x(x), y(y), w(width), h(height)
// {
//     plotpane = pp;
//     u8g2.begin(*this); // connect u8g2 procedures to Adafruit GFX
//     u8g2.setFontMode(1);                  // use u8g2 transparent mode (this is default)
//     setTextWrap(false);
//     u8g2.setFontDirection(0);             // left to right (this is default)
//     u8g2.setForegroundColor(BLACK); // apply Adafruit GFX color
//     u8g2.setBackgroundColor(WHITE); // apply Adafruit GFX color
// }

// void SubPlot::drawPixel(int16_t x, int16_t y, uint16_t color)
// {
//     if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) return;
//     {
//         plotpane->drawPixel(x+this->x, y+this->y, color);
//     }
// }

// void plotpoint(Axis* axis, DataType x, DataType y, uint16_t color, Marker sym,uint8_t symbolSize,bool filledmarker)
// {
//     // //check limits this is done automaticaly to auto fit graph
//     // if(x>=limits.xLim().max) limits.setXLim(limits.xLim().min,1.5*x);
//     // if(x<=limits.xLim().min) limits.setXLim(0.5*x,limits.xLim().max);
//     // if(y>=limits.yLim().max) limits.setYLim(limits.yLim().min,1.5*y);
//     // if(y<=limits.yLim().min) limits.setYLim(0.5*y,limits.yLim().max);
//     uint16_t x = uint16_t(round((x-axis->limits.xLim().min)/axis->limits.xRange())*DataType(axis->width()));
//     uint16_t yOffset = uint16_t(round((x-axis->limits.yLim().min)/axis->limits.yRange())*DataType(axis->height()));
//     switch (sym)
//     {
//     case none/* constant-expression */:
//         axis->drawPixel(axis->get_x() + x,axis->get_y()-yOffset,color);
//         break;
//     case circle/* constant-expression */:
//     Serial << "here" << endl;
//         if(filledmarker)axis->fillCircle(axis->get_x() + x,axis->get_y()-yOffset,symbolSize,color);
//         else axis->drawCircle(axis->get_x() + xOffset,axis->get_y()-yOffset,symbolSize,color);
//         break;
//     case triangle/* constant-expression */:
//         if(filledmarker) axis->fillTriangle(axis->get_x() + xOffset-symbolSize/2,axis->get_y()-yOffset + symbolSize/2,axis->get_x() + xOffset+symbolSize/2,
//         axis->get_y()-yOffset + symbolSize/2,axis->get_x() + xOffset,axis->get_y()-yOffset - symbolSize/2,color);
//         else axis->drawTriangle(axis->get_x() + xOffset-symbolSize/2,axis->get_y()-yOffset + symbolSize/2,axis->get_x() + xOffset+symbolSize/2,
//         axis->get_y()-yOffset + symbolSize/2,axis->get_x() + xOffset,axis->get_y()-yOffset - symbolSize/2,color);
//         break;
//     case square/* constant-expression */:
//         if(filledmarker) axis->fillRect(axis->get_x() + xOffset-symbolSize/2,axis->get_y()-yOffset-symbolSize/2,symbolSize,symbolSize,color);
//         else axis->drawRect(axis->get_x() + xOffset-symbolSize/2,axis->get_y()-yOffset-symbolSize/2,symbolSize,symbolSize,color);
//         break;
//     default:
//         break;
//     }

//     //drawFastHLine(axis.x,axis.y,axis.width,BLACK);
//     //drawFastVLine(axis.x,axis.y-axis.height,axis.height,BLACK);
// }