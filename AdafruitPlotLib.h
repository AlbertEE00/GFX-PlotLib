#ifndef ADAFRUITPLOTLIB_H
#define ADAFRUITPLOTLIB_H

#include "TypesAndDefs.h"
#include "Data.h"
#include "Label.h"

#include "EPaperDisplay.h"
#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "U8g2_for_Adafruit_GFX.h"
#include <cmath>
//#include <math.h>
#include "streaming.h"
//#include <array>
#include <list>
#include <iterator>
#include "Vector.h"
// #include <vector>

#define FACTOR 0.1

class Axis;
template<typename T>
class Limits;
class AdafruitPlot;
class Subplot;

int16_t roundToint16(float v);

void swapFloat(float a, float b);

void DrawThickLine(Adafruit_GFX &display, float x, float y, float x1, float y1, float size, int color);



// #define MAX_SUBPLOTS 4
// struct SubplotManager
// {   
//     SubplotManager(SubPlot* subplots, uint8_t rows,uint8_t columns);
//     SubPlot& operator()(uint8_t rows, uint8_t columns);
//     SubPlot** subs;
//     uint8_t subplotcnt;
// };
// SubplotManager::SubplotManager(SubPlot *subplots, uint8_t rows, uint8_t columns)
// {
//     subplotcnt = rows*columns;

// }
// SubPlot &SubplotManager::operator()(uint8_t rows, uint8_t columns)
// {

// }


// class AdafruitPlot : public Adafruit_GFX
// {
//     public:
//     AdafruitPlot(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Adafruit_GFX &disp);
//     AdafruitPlot(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t rows, uint8_t colums, Adafruit_GFX &disp);
//     SubplotManager subplots(uint8_t rows, uint8_t columns);
//     Subplot& operator()(uint8_t rows, uint8_t columns);
//     Subplot* subplot[MAX_SUBPLOTS];
//     void drawPixel(int16_t x, int16_t y, uint16_t color);
//     private:
//     Adafruit_GFX* display;
//     U8G2_FOR_ADAFRUIT_GFX u8g2;
//     uint16_t x,y,w,h;
//     String title,description;
//     uint8_t subPlotCnt = 1;
// };

#define auto_margin 0.15
template<typename T>
class Limits
{

public:
    Limits(){manual_x_limits=true;manual_y_limits=true;setLim(0,0,0,0);parseLimits();}
    Limits(T minx,T maxx,T miny,T maxy){manual_x_limits=true;manual_y_limits=true;setLim(minx, maxx, miny, maxy);parseLimits();}
    Limits(PlotData<T>& dp){manual_x_limits=false;manual_y_limits=false;updateLimits(dp);}
    // skryf hierdie op
    Lim<T> xLim()
    {
    if(!manual_x_limits)
    {
        T max = ((x_auto.max + x_auto.min) + (x_auto.max - x_auto.min)*(1.0+auto_margin/3.0))/2;
        T min = ((x_auto.max + x_auto.min) - (x_auto.max - x_auto.min)*(1.0+auto_margin/3.0))/2;

        return Lim<T>(min,max);
    }
    else return x_man;
    }
    Lim<T> yLim()
    {
    if(!manual_y_limits)
    {
        T max = ((y_auto.max + y_auto.min) + (y_auto.max - y_auto.min)*(1.0+auto_margin))/2;
        T min = ((y_auto.max + y_auto.min) - (y_auto.max - y_auto.min)*(1.0+auto_margin))/2;
        return Lim<T>(min,max);
    }
    else return y_man;
    }
    T xRange(){return x_width;}
    T yRange(){return y_height;}
    bool manual_y_Limits(){return manual_y_limits;}
    bool manual_x_Limits(){return manual_x_limits;}
    void parseLimits()
    {
        x_width = xLim().max - xLim().min;
        y_height = yLim().max - yLim().min;
    }

    void setXLim(T min, T max)
    {
        manual_x_limits=true;
        x_man.min = min;
        x_man.max = max;
        parseLimits();
    }
    void setYLim(T min, T max)
    {
        manual_y_limits=true;
        y_man.min = min;
        y_man.max = max;
        parseLimits();
    }
    void setXlimMax(T max)
    {
        manual_x_limits=true;
        x_man.min = x_auto.min;
        x_man.max = max;
        parseLimits();
    }
    void setXlimMin(T min)
    {
        manual_x_limits=true;
        x_man.max = x_auto.max;
        x_man.min = min;
        parseLimits();
    }
    void setYlimMax(T max)
    {
        manual_y_limits=true;
        y_man.min = y_auto.min;
        y_man.max = max;
        parseLimits();
    }
    void setYlimMin(T min)
    {
        manual_y_limits=true;
        y_man.max = y_auto.max;
        y_man.min = min;
        parseLimits();
    }

    void setLim(T minx, T maxx, T miny,T maxy){manual_x_limits=true;manual_y_limits=true;setXLim(minx,maxx);setYLim(miny,maxy);}
    void updateLimits(PlotData<T>& dp)
    {
        if(initial)
        {
            this->x_auto.max = dp.xLim().max;
            this->x_auto.min = dp.xLim().min;
            this->y_auto.max = dp.yLim().max;
            this->y_auto.min = dp.yLim().min;
            initial = false;
        }
        if(this->x_auto.max < dp.xLim().max) this->x_auto.max = dp.xLim().max;
        if(this->x_auto.min > dp.xLim().min) this->x_auto.min = dp.xLim().min;
        if(this->y_auto.max < dp.yLim().max) this->y_auto.max = dp.yLim().max;
        if(this->y_auto.min > dp.yLim().min) this->y_auto.min = dp.yLim().min;
        manual_x_limits=false;manual_y_limits=false;
        parseLimits();
    }
private:
    friend class Axis;
    friend class Subplot;
    bool manual_x_limits,manual_y_limits;
    Lim<T> x_man = {0,0}, y_man={0,0};
    Lim<T> x_auto = {0,0}, y_auto={0,0};
    T xMin,xMax,yMin,yMax;
    T x_width,y_height;
    bool initial = true;
};



#define  MAX_DATA_PLOTS 10
class Axis : public Adafruit_GFX
{
    public:
    Axis(Adafruit_GFX &sub_plot, uint16_t x, uint16_t y, uint16_t width, uint16_t height,uint16_t axis_color = BLACK, uint16_t bkg_color = WHITE);
    ~Axis();
    void clear(bool clearData = true, bool clearAxis=false);
    uint16_t axisWidth();
    uint16_t axisHeight();  
    uint16_t get_x();
    uint16_t get_y();
    Limits<DataType> limits;
    void drawAxis();
    PlotData<DataType>* data[MAX_DATA_PLOTS];
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    private:
    void plotData(PlotData<DataType>& dp);
    void plotpoint(PlotData<DataType>& dp,unsigned int index);
    void linePlot(PlotData<DataType> &dp);
    void scatterPlot(PlotData<DataType> &dp);
    void Bars(PlotData<DataType> &dp);
    DataElement<DispCoordType> project(const DataElement<DataType>& element);
    Adafruit_GFX*_subplot;
    friend class Subplot;
    
    void show();
    uint16_t x,y,w,h,bl_x,bl_y,axis_color,bkg_color;
    uint8_t data_plot_cnt=0;
    uint8_t label_cnt = 0;
                                           PlotData<DataType>* plot(PlotData<DataType> &data);
    template<typename T>               PlotData<DataType>* plot(const T *x, const T *y,const size_t length,plotType pltType = line);
    template<typename T,size_t length> PlotData<DataType>* plot(const T (&x)[length], const T (&y)[length],plotType pltType = line);
    template<typename T> PlotData<DataType>* plot(const dataVector<T> &x, const dataVector<T> &y,plotType pltType = line);
};




template<typename T>
PlotData<DataType>* Axis::plot(const T *x, const T *y,const size_t length,plotType pltType)
{
    DataType tempX[length],tempY[length];
    for(auto i : range(length)){tempX[i] = (DataType)(x[i]);tempY[i] = (DataType)(y[i]);}
    data_plot_cnt+=1;
    data[data_plot_cnt-1] = new PlotData<DataType>(tempX,tempY,length); // create new data plot
    limits.updateLimits(*(data[data_plot_cnt-1])); // plot function plots line plots
    (*(this->data[data_plot_cnt-1])).plottype = pltType;
    return ((this->data[data_plot_cnt-1]));
}
template<typename T,size_t length>
PlotData<DataType>* Axis::plot(const T (&x)[length], const T (&y)[length],plotType pltType)
{
    DataType tempX[length],tempY[length];
    for(auto i : range(length)){tempX[i] = (DataType)(x[i]);tempY[i] = (DataType)(y[i]);}
    data_plot_cnt+=1;
    data[data_plot_cnt-1] = new PlotData<DataType>(tempX,tempY,length); // create new data plot
    limits.updateLimits(*(data[data_plot_cnt-1])); // plot function plots line plots
    (*(this->data[data_plot_cnt-1])).plottype = pltType;
    return ((this->data[data_plot_cnt-1]));
}
template<typename T>
PlotData<DataType>* Axis::plot(const dataVector<T> &x, const dataVector<T> &y,plotType pltType)
{
    DataType tempX[x.size()],tempY[x.size()];
    for(auto i : range(x.size())){tempX[i] = (DataType)(x[i]);tempY[i] = (DataType)(y[i]);}
    data_plot_cnt+=1;
    data[data_plot_cnt-1] = new PlotData<DataType>(tempX,tempY,x.size()); // create new data plot
    limits.updateLimits(*(data[data_plot_cnt-1])); // plot function plots line plots
    (*(this->data[data_plot_cnt-1])).plottype = pltType;
    return ((this->data[data_plot_cnt-1]));
}


#define axisLabelfraction 0.4
#define titleLabelfraction 0.9
class Subplot : private Adafruit_GFX
{
    public:
    Subplot(DispCoordType x, DispCoordType y, DispCoordType width, DispCoordType height, Adafruit_GFX& plotfig);
    void setTitle(String text,GFX_COLOR color);
    void setYLabel(String text,GFX_COLOR color);
    void setXLabel(String text,GFX_COLOR color);
    void setLabels(String title,String x_label, String y_label,GFX_COLOR colorT,GFX_COLOR colorX,GFX_COLOR colorY);
    void setLabels(String title,String x_label, String y_label);
    void setTitle(String text);
    void setYLabel(String text);
    void setXLabel(String text);
    void legend(String label, size_t index,GFX_COLOR color);
    void legend(String label, size_t index);
    void setTickColor(GFX_COLOR color = BLACK);
    void setXTicks();
    void setYTicks();
    void setTickFreq(DataType TF = 5.0, DataType TLF = 1.0);
    void setLim(DataType minx, DataType maxx, DataType miny,DataType maxy);
    void setYLim(DataType min, DataType max);
    void setXLim(DataType min, DataType max);
    size_t plotCnt();
    Axis axis;
    void show();
    void clear(bool clearData = true,bool clearAxis=false);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawLegend();
    void setDisplay(Adafruit_GFX& plotfig);
//TODO: variadic template instead implement
//plotting functions 

                                           PlotData<DataType>* plot(PlotData<DataType> &data);
    template<typename T>               PlotData<DataType>* plot(const T *x, const T *y,const size_t length,plotType pltType = line);
    template<typename T,size_t length> PlotData<DataType>* plot(const T (&x)[length], const T (&y)[length],plotType pltType = line);
    template<typename T> PlotData<DataType>* plot(const dataVector<T> &x, const dataVector<T> &y,plotType pltType = line);

    PlotData<DataType>* operator[](size_t index);
    PlotData<DataType>* operator[](String index);

    private:
    friend class Axis;
    friend class AdafruitPlot;
    U8G2_FOR_ADAFRUIT_GFX u8g2;
    Adafruit_GFX* plotfig;
    uint16_t x,y,w,h;
    Label title,xLabel,yLabel,description;
    GFX_COLOR tickColor = BLACK,textColor=BLACK;
    DataType tickFreq=5.0; 
    DataType tickLableFreq = 1.0;
    bool manualTicks = false;
};


template<typename T>
PlotData<DataType>* Subplot::plot(const T *x, const T *y,const size_t length,plotType pltType)
{
    return axis.plot(x,y,length,pltType);
}
template<typename T,size_t length>
PlotData<DataType>* Subplot::plot(const T (&x)[length], const T (&y)[length],plotType pltType)
{
    return axis.plot(x,y,pltType);
}
template<typename T>
PlotData<DataType>* Subplot::plot(const dataVector<T> &x, const dataVector<T> &y,plotType pltType)
{
    return axis.plot(x,y,pltType);
}
#define MAX_SUBPLOTS 4
class AdafruitPlot : private Adafruit_GFX
{
    public:
    AdafruitPlot(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Adafruit_GFX &disp);
    AdafruitPlot(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t rows, uint8_t colums, Adafruit_GFX &disp);
    Subplot* subplot(uint8_t rows, uint8_t colums);
    
    // Subplot& operator()(uint8_t rows, uint8_t columns);
    // Subplot* subplot[MAX_SUBPLOTS];
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    private:
    Adafruit_GFX* display;
    U8G2_FOR_ADAFRUIT_GFX u8g2;
    uint16_t x,y,w,h;
    String title,description;
    uint8_t subPlotCnt = 1;
    Subplot* subplots[MAX_SUBPLOTS];
};




#endif