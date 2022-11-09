#pragma once

#include "arduino.h"
template<typename T>
class RangeIterator
{
public:
  RangeIterator(T initValue) : initValue{initValue}, position_{0} {}

  RangeIterator(T initValue, T size) : initValue{initValue}, position_{size} {}

  bool operator!=(const RangeIterator<T> & other) const
  {
    return !(*this == other);
  }

  bool operator==(const RangeIterator<T> & other) const
  {
    return position_ == other.position_;

  }

  RangeIterator & operator++()
  {
    ++position_;
    return *this;
  }

  T  operator*() const
  {
    return (initValue + position_);
  }

private:
  T initValue;
  T position_;
};

struct range
{
    public:
    
    range(int start,int end) : start(start), length(end) {}
    range(int end) : start(0), length(end) {}
    
    typedef RangeIterator<int> iterator;
    iterator begin()
    {
        return iterator(start);
    }
    iterator end()
    {
        return iterator(start,length-start);
    }
    typedef RangeIterator< int> const_iterator;
    const_iterator begin() const
    {
        return iterator(start);
    }
    const_iterator end() const
    {
        return iterator(start,length-start);
    }
    private:
    int start;
    int length;
};