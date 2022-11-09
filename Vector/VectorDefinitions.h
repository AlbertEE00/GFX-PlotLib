// ----------------------------------------------------------------------------
// VectorDefinitions.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef VECTOR_DEFINITIONS_H
#define VECTOR_DEFINITIONS_H

#ifndef ARDUINO
#include <cstring>
#endif
#include <algorithm>
#include <limits>

template <typename T>
dataVector<T>::dataVector()
{
  values_ = NULL;
  max_size_ = 0;
  size_ = 0;
}

template<class T>
dataVector<T>::dataVector(size_t max_size)
  {
      values_ = new T[max_size];
      max_size_ = max_size;
      size_ = max_size_ - 1;
      allocated = true;
      return;
  }

template<class T> dataVector<T>::dataVector(dataVector<T> &&src)
{
  #ifdef DEBUG_VECTOR
  Serial << "template<class T> dataVector<T>::dataVector(dataVector<T> &&src)"<< endl;
  #endif

  this->max_size_ = src.max_size_;
  this->size_ = src.size_;
  this->values_ = src.values_;
  this->allocated = src.allocated;
  src.values_ = nullptr;
}

template <typename T>
template <size_t MAX_SIZE>
dataVector<T>::dataVector(T (&values)[MAX_SIZE],
  size_t size)
{
  setStorage(values,size);
}


template<class T> dataVector<T>::dataVector(const dataVector<T> &src)
{
  #ifdef DEBUG_VECTOR
  Serial << "template<class T> dataVector<T>::dataVector(const dataVector<T> &src)"<<endl;
  #endif
  this->max_size_ = src.max_size_;
  this->size_ = src.size_;
  this->values_ = src.values_;
  this->allocated = src.allocated;
  if(src.values_ != nullptr || src.values_ != NULL )
  {
    this->values_ = new T[src.max_size_];
    this->allocated = true;
    for(int i=0;i<src.max_size_;i++) this->values_[i] = src.values_[i];
  }
}

template <typename T>dataVector<T>::dataVector(std::initializer_list<T> l)
{
  #ifdef DEBUG_VECTOR
  Serial << "template <typename T>dataVector<T>::dataVector(std::initializer_list<T> l)"<<endl;
  #endif
  values_ = new T[l.size()];
  max_size_ = l.size();
  size_ = max_size_ - 1;
  int count{ 0 };
	for (int element : l)
	{
		values_[count] = element;
		++count;
	}
  allocated = true;
}

template <typename T>dataVector<T>::~dataVector()
{
  #ifdef DEBUG_VECTOR
  Serial << "template <typename T>dataVector<T>::~dataVector()"<<endl;
  #endif
  if(allocated)
  {
    if(values_!=nullptr) delete[] values_;
  }
}
template<class T> dataVector<T> &dataVector<T>::operator=(dataVector<T> &&rhs)
{
  #ifdef DEBUG_VECTOR
  Serial << "template<class T> dataVector<T> &dataVector<T>::operator=(dataVector<T> &&rhs)"<<endl;
  #endif
  if(this != &rhs)
  {
    if(this->allocated)
    {
      delete[] this->values_;
      this->max_size_ = rhs.max_size_;
      this->size_ = rhs.size_;
      this->values_ = rhs.values_;
      this->allocated = rhs.allocated;
      rhs.values_ = nullptr;
    }
    else if(this->values_==NULL)
    {
      T* temp = new T[rhs.max_size_];
      if(temp!=nullptr)
      {
        this->max_size_ = rhs.max_size_;
        this->size_ = rhs.size_;
        this->allocated = true;
        this->values_ = temp;
        for(int i=0;i<rhs.max_size_;i++) this->values_[i] = rhs.values_[i];
      }

    }
    else
    {
      this->max_size_ = rhs.max_size_;
      this->size_ = rhs.size_;
      this->allocated = rhs.allocated;
      this->values_ = rhs.values_;
    }
  }
  return *this;
}


template<typename T> dataVector<T>& dataVector<T>::operator=(const dataVector<T> &rhs)
{
  #ifdef DEBUG_VECTOR
  Serial << "template<typename T> dataVector<T>& dataVector<T>::operator=(const dataVector<T> &rhs)"<<endl;
  #endif
  if(this != &rhs)
  {

    if(this->allocated)
    {

      T* temp = new T[rhs.max_size_];
      if(temp!=nullptr)
      {
        this->max_size_ = rhs.max_size_;
        this->size_ = rhs.size_;
        Serial << "deleting this!" << endl;
        delete[] this->values_;
        this->allocated = true;
        this->values_ = temp;
        for(int i=0;i<rhs.max_size_;i++) this->values_[i] = rhs.values_[i];
      }
    }
    else if(this->values_==NULL)
    {
      T* temp = new T[rhs.max_size_];
      if(temp!=nullptr)
      {
        this->max_size_ = rhs.max_size_;
        this->size_ = rhs.size_;
        this->allocated = true;
        this->values_ = temp;
        for(int i=0;i<rhs.max_size_;i++) this->values_[i] = rhs.values_[i];  
      }
    }
    else
    {
      this->max_size_ = rhs.max_size_;
      this->size_ = rhs.size_;
      this->allocated = rhs.allocated;
      this->values_ = rhs.values_;
    }
  }
  return *this;
}

template<class T>  dataVector<T>& dataVector<T>::operator+(const dataVector<T>& rhs)
{
  int _size_ = this->size();
  dataVector<T> *temp;
  if(this->size()!=rhs.size())
  {
    Serial << "Adding two vectors of unequal length";
    if(this->size()>rhs.size()){_size_ = rhs.size();temp = new dataVector<T>(*(this));}
    else {_size_ = this->size();temp = new dataVector<T>(rhs);}
  }
  else temp = new dataVector<T>(rhs);
  Serial << "first" << endl;
  for(int i=0;i<_size_;i++) 
  {
    (*temp).values_[i] = rhs.values_[i] + this->values_[i]; 
  }

  return (*temp);
}

template<class T>  dataVector<T>& dataVector<T>::operator+=(const dataVector<T>& rhs)
{
  int _size_ = this->size();
  if(this->size()!=rhs.size())
  {
    Serial << "Adding two vectors of unequal length";
  }

  for(int i=0;i<_size_;i++) 
  {
    this->values_[i] += rhs.values_[i]; 
  }

  return (*this);
}
template<class T>  dataVector<T>& dataVector<T>::operator-(const dataVector<T>& rhs)
{
  int _size_;
  dataVector<T> *temp;
  if(this->size()!=rhs.size())
  {
    Serial << "subtracting two vectors of unequal length";
    if(this->size()>rhs.size()){_size_ = rhs.size();temp = new dataVector<T>(*(this));}
    else {_size_ = this->size();temp = new dataVector<T>(rhs);}
  }
  else temp =  new dataVector<T>(rhs);
  Serial << "first" << endl;
  for(int i=0;i<_size_;i++) 
  {
    (*temp).values_[i] = rhs.values_[i] - this->values_[i]; 
  }

  return (*temp);
}
template<class T>  dataVector<T>& dataVector<T>::operator-=(const dataVector<T>& rhs)
{
  int _size_ = this->size();
  if(this->size()!=rhs.size())
  {
    Serial << "subtracting two vectors of unequal length";
  }


  for(int i=0;i<_size_;i++) 
  {
    this->values_[i] -= rhs.values_[i]; 
  }

  return (*this);
}
template<class T>  dataVector<T>& dataVector<T>::operator*(const T rhs)
{
  int _size_ = this->size();
  auto& temp =  dataVector<T>(*this);

  for(int i=0;i<_size_;i++) 
  {
    temp.values_[i] = (this->values_[i])*rhs; 
  }

  return temp;
}
template<class T>  dataVector<T>& dataVector<T>::operator*=(const T rhs)
{
  int _size_ = this->size();

  for(int i=0;i<_size_;i++) 
  {
    this->values_[i] = (this->values_[i])*rhs; 
  }

  return (*this);
}
template<class T>  dataVector<T>& dataVector<T>::operator/(const T rhs)
{
 int _size_ = this->size();
  dataVector<T> temp = dataVector<T>(*this);

  for(int i=0;i<_size_;i++) 
  {
    temp.values_[i] = (rhs!=0) ? (this->values_[i])/rhs : NAN;
  }

  return temp;
}
template<class T>  dataVector<T>& dataVector<T>::operator/=(const T rhs)
{
  int _size_ = this->size();

  for(int i=0;i<_size_;i++) 
  {
      this->values_[i] = (rhs!=0) ? (this->values_[i])/rhs : NAN;
  }

  return (*this);

}



template <typename T>
template <size_t MAX_SIZE>
void dataVector<T>::setStorage(T (&values)[MAX_SIZE],
  size_t size)
{
  values_ = values;
  max_size_ = MAX_SIZE;
  size_ = size;
}

template <typename T>
void dataVector<T>::setStorage(T * values,
  size_t max_size,
  size_t size)
{
  values_ = values;
  max_size_ = max_size;
  size_ = size;
}

template <typename T>
void dataVector<T>::setStorage(T * values,
  size_t max_size,
  bool aloc)
  {
    if(values_ == NULL || values_ == nullptr)
    {
      values_ = new T[max_size];
      max_size_ = max_size;
      size_ = max_size_ - 1;
      for (int i=0;i<max_size;i++)
      {
        values_[i] = values[i];
      }
      allocated = true;
      return;
    }
    else if (allocated)
    {
      delete[] values_;
      values_ = new T[max_size];
      max_size_ = max_size;
      size_ = max_size_ - 1;
      for (int i=0;i<max_size;i++)
      {
        values_[i] = values[i];
      }
      allocated = true;
      return;
    }
  }


template <typename T>
const T & dataVector<T>::operator[](size_t index) const
{
  return values_[index];
}

template <typename T>
T & dataVector<T>::operator[](size_t index)
{
  return values_[index];
}

// template <typename T>
// const T & dataVector<T>::operator+(size_t index) const
// {
//   return values_[index];
// }

template <typename T>
T & dataVector<T>::at(size_t index)
{
  return values_[index];
}

template <typename T>
const T & dataVector<T>::at(size_t index) const
{
  return values_[index];
}

template <typename T>
T & dataVector<T>::front()
{
  return values_[0];
}

template <typename T>
T & dataVector<T>::back()
{
  return values_[size_-1];
}

template <typename T>
void dataVector<T>::clear()
{
  size_ = 0;
}

template <typename T>
template <typename U>
void dataVector<T>::fill(const U & value)
{
  assign(max_size_,value);
}

template <typename T>
template <typename U,
  size_t N>
void dataVector<T>::fill(const U (&values)[N])
{
  assign(N,values);
}

template <typename T>
template <typename U>
void dataVector<T>::fill(const dataVector<U> & values)
{
  assign(values.size(),values);
}

template <typename T>
template <typename U>
void dataVector<T>::assign(size_t n,
  const U & value)
{
  size_t assign_size = ((n < max_size_) ? n : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = value;
  }
}

template <typename T>
template <typename U,
  size_t N>
void dataVector<T>::assign(size_t n,
  const U (&values)[N])
{
  size_t n_smallest = ((n < N) ? n : N);
  size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = values[i];
  }
}

template <typename T>
template <typename U>
void dataVector<T>::assign(size_t n,
  const dataVector<U> & values)
{
  size_t n_smallest = ((n < values.size()) ? n : values.size());
  size_t assign_size = ((n_smallest < max_size_) ? n_smallest : max_size_);
  size_ = assign_size;
  for (size_t i=0; i<assign_size; ++i)
  {
    values_[i] = values[i];
  }
}

template <typename T>
void dataVector<T>::push_back(const T & value)
{
  if ((values_ != NULL) && (size_ < max_size_))
  {
    values_[size_++] = value;
  }
}

template <typename T>
void dataVector<T>::pop_back()
{
  if (size_ > 0)
  {
    --size_;
  }
}

template <typename T>
void dataVector<T>::remove(size_t index)
{
  if (size_ > index)
  {
    for (size_t i=index; i<(size_-1); ++i)
    {
      values_[i] = values_[i+1];
    }
    --size_;
  }
}

template <typename T>
size_t dataVector<T>::size() const
{
  return size_;
}

template <typename T>
size_t dataVector<T>::max_size() const
{
  return max_size_;
}

template <typename T>
bool dataVector<T>::empty() const
{
  return size_ == 0;
}

template <typename T>
bool dataVector<T>::full() const
{
  return size_ == max_size_;
}

template <typename T>
T * dataVector<T>::data()
{
  return values_;
}

template <typename T>
const T * dataVector<T>::data() const
{
  return values_;
}

template <typename T>
typename dataVector<T>::iterator dataVector<T>::begin()
{
  return iterator(values_);
}

template <typename T>
typename dataVector<T>::iterator dataVector<T>::end()
{
  return iterator(values_,size_);
}

template <typename T>
typename dataVector<T>::const_iterator dataVector<T>::begin() const
{
  return const_iterator(values_);
}

template <typename T>
typename dataVector<T>::const_iterator dataVector<T>::end() const
{
  return const_iterator(values_,size_);
}

#endif
