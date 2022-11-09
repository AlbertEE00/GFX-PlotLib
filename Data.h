#pragma once

#include <Arduino.h>
#include "Vector.h"
#include "TypesAndDefs.h"
#include "AdafruitPlotLib.h"
#include "Range.h"
#include "Label.h"


template<typename T>
struct Lim
{
    Lim();
    Lim(T min, T max);
    T min,max;
};

template<class T> Lim<T>::Lim() = default;
template<class T> Lim<T>::Lim(T min, T max) : min(min), max(max){}

template<class T> Lim<T> getLimitsOf(dataVector<T> &vec);
template<class T> Lim<T> getLimitsOf(T* vec, size_t length);

template<typename T>
class PlotData;

template<typename T>
struct DataElement
{
    T x,y;
    PlotData<T>* _data;
};

enum Marker {circle,square,triangle,none};
enum plotType {line,scatter,histogram,bars,pi,noplot};
enum lineStyle {solid,dotted,dashed,dashdot};

template<typename T>
class PlotData
{
public: //constructors
    PlotData();
    PlotData(T *x, T *y, int length);
    PlotData(dataVector<T>&x, dataVector<T>&y); 
    //PlotData(size_t length);     
    unsigned int length();
public: //parameters
    void setLabel(String text,GFX_COLOR fgColor = BLACK, GFX_COLOR bkgColor=WHITE);
    Label label;
    plotType plottype = line;
    GFX_COLOR color = BLACK;
    bool legend=false;
    //marker settings
    GFX_COLOR markercolor = BLACK;
    uint8_t markersize = 1;
    Marker marker = none;
    bool filledmarker = true;
    //line settings
    lineStyle linestyle = solid;
    uint8_t linewidth = 1;
    DataElement<T>& operator[](size_t index);
    Lim<T> xLim();
    Lim<T> yLim();
    bool addData(T xd,T yd);
    size_t addData(T* xd,T* yd,size_t length);
    bool clearData();
private:
    DataElement<T> elem;
    dataVector<T> x;
    dataVector<T> y;
    Lim<T> _xlim,_ylim;
};
template<class T> void PlotData<T>::setLabel(String text, GFX_COLOR fgColor, GFX_COLOR bkgColor)
{
    label.text = text;
    label.bkg_color = bkgColor;
    label.fg_color = fgColor;
}

template<class T> bool PlotData<T>::clearData()
{
    x.clear();
    y.clear();
    _xlim.max = 0,_xlim.min = 0;
    _ylim.max = 0,_ylim.min = 0;
    if(x.size()==0 && y.size() == 0) return true;
    else return false;
}

template<class T> bool PlotData<T>::addData(T xd, T yd)
{
    size_t xSize = x.size(),ySize = y.size();
    x.push_back(xd),y.push_back(yd);
    _xlim = getLimitsOf(this->x);
    _ylim = getLimitsOf(this->y);
    if(1==(x.size()-xSize) && 1==(y.size()-ySize)) return true;
    else return false;

}

template<class T> size_t PlotData<T>::addData(T* xd,T* yd,size_t length)
{
    size_t xSize = x.size(),ySize = y.size();
    for(int i = 0;i<length;i++) x.push_back(xd[i]),y.push_back(yd[i]);
    _xlim = getLimitsOf(this->x);
    _ylim = getLimitsOf(this->y);
    if(length==(x.size()-xSize) && length==(y.size()-ySize)) return length;
    else return (x.size()-xSize);
}

template<class T> PlotData<T>::PlotData() = default;

template<typename T> PlotData<T>::PlotData(T *x, T *y, int length)
{   
    this->x.setStorage(x,length,true);
    this->y.setStorage(y,length,true);
    _xlim = getLimitsOf(this->x);
    _ylim = getLimitsOf(this->y);
    elem.x = this->x[0];
    elem.y = this->y[0];
    elem._data = this;
}

template<typename T> PlotData<T>::PlotData(dataVector<T>&x, dataVector<T>&y)
{
    this->x = x;
    this->y = y;
    _xlim = getLimitsOf(this->x);
    _ylim = getLimitsOf(this->y);
    elem.x = this->x[0];
    elem.y = this->y[0];
    elem._data = this;
}

template<class T> Lim<T> PlotData<T>::xLim(){return _xlim;}
template<class T> Lim<T> PlotData<T>::yLim(){return _ylim;}



template<class T> DataElement<T> &PlotData<T>::operator[](size_t index)
{
    elem.x = this->x[index];
    elem.y = this->y[index];
    return elem;
}
template<typename T> unsigned int PlotData<T>::length()
{
    return x.size();
}


template<class T> Lim<T> getLimitsOf(dataVector<T> &vec)
{
    T min = vec[0],max = vec[0];
     for(int i = 0;i<vec.size();i++)
    {
        if(vec[i]>max) max = vec[i];
        else if(vec[i]<min) min = vec[i];
    }
    return Lim<T>(min,max);
}

template<class T> Lim<T> getLimitsOf(T* vec, size_t length)
{
    T min = vec[0],max = vec[0]; // initially the first vector

    for(int i = 0;i<length;i++)
    {
        if(vec[i]>max) max = vec[i];
        else if(vec[i]<min) min = vec[i];
    }
    return Lim<T>(min,max);
}