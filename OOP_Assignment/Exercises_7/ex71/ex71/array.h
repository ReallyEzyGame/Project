#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <iostream>
#include <string.h>

template <typename T>
class Array
{
private:
    T *_data;
    int _size, _capacity;

public:
    class Iterator;


    Array() {
        _capacity = 0;
        _size = 0;
        _data = nullptr;
    }
    Array(const int n)
    {
        _capacity = std::abs(n);
        _size = std::abs(n);

        _data = new T[_capacity];
    }
    Array(const int N, const T* array) {
      _size = std::abs(N);
      _capacity = std::abs(N);

      _data = new T[_capacity];

      for  (int i = 0; i < _size; ++i) {
        _data[i] = array[i];
      }
    }
    // Construct the Array T value from normal array
    // if the _size ==> Aaccess memory Violation
    // if the _size is smaller than the actual array then the Array will left off all the value behind n
    Array(const std::initializer_list<T> list) {
        _size = list.size();
        _capacity = list.size();
        _data = new T[_capacity];

        for (int i = 0; i < _size; ++i) {
            _data[i] = list[i];
        }
    }
    Array(const Array<T> &arr)
    {
        _size = arr._size;
        _capacity = arr._capacity;
        _data = new T[_capacity];

        for (int i = 0; i < _size; ++i)
            _data[i] = arr._data[i];
    }
    Array(const int n, const T val)
    {
        _size = std::abs(n);
        _capacity = std::abs(n);
        _data = new T[_capacity];
        
        for (int i = 0; i < _size; ++i)
            _data[i] = val;
    }
    ~Array()
    {
        if (_data)
            delete _data;
    }


    size_t size() const {
        return _size;
    }
    size_t capacity() const {
        return _capacity;
    }
    bool empty() const
    {
        return _size == 0;
    }


    void push_back(const T val)
    {
        // Extend the _size of the array
        if (_size == _capacity)  {
            scale();
        }

        _data[_size++] = val;
    }
    void pop_back()
    {
        if (_size > 0)
        {
            --_size;
        }
    }
    T operator[](const int idx) const
    {
        if (idx < 0 ||  _size <= idx) {
            throw std::out_of_range("Out of Range");
        }
        return _data[idx];
    }
    T& operator[] (const int idx) {
        if (idx < 0 ||  _size <= idx) {
            throw std::out_of_range("Out of Range");
        }
        return _data[idx];
    }
    Array<T>& operator=(const Array<T> &other)
    {
        if (this == &other) {
            return *this;
        }
        if (_data) {
            delete[] _data;
        }

        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];

        for (int i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
        return *this;
    }


private:
    void scale()
    {
        _capacity = _capacity == 0 ? 8 : _capacity * 2;

        T *tmp_arr = _data;
        _data = new T[_capacity];
        
        // Copy the old _data
        for (int i = 0; i < _size; ++i)
            _data[i] = tmp_arr[i];
        // Release Memory of the old array
        if (tmp_arr)
            delete[] tmp_arr;
    }
};


template<class  T>
class Array<T>::Iterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
private:
    T* _ptr;
public:
    Iterator(T* ptr) : _ptr(ptr) {}


    reference operator* () const{
        return *_ptr;
    }
    pointer operator->() const {
        return _ptr;
    }
    reference operator[] (const int n)  const {
        return *(_ptr + n);
    }


    Iterator& operator++() {
        _ptr++;
        return *this;
    }
    Iterator operator++(int) {
        Iterator tmp = *this;
        _ptr++;
        return tmp;
    }
    Iterator operator--() {
        _ptr--;
        return *this;
    }
    Iterator operator--(int) {
        Iterator tmp = *this;
        _ptr--;
        return tmp;
    }


    Iterator& operator+=(const  int n) {
        _ptr += n;
        return *this;
    }
    operator-=(const int n) {
        _ptr -= n;
        return *this;
    }
    Iterator operator+(const int n) const {
        return Iterator(_ptr + n);
    }
    Iterator operator-(const int n) const {
        return Iterator(_ptr - n);
    }
    bool operator==(const Iterator& other) const {
        return _ptr == other._ptr;
    }
    bool operator!=(const Iterator& other) const {
        return _ptr != other._ptr;
    }
};


class String {
private:
    Array<char> _str;
public:
    String() {};
    String(const char* str){
        int len = strlen(str);

        for (int i = 0; i < len; ++i) {
            _str.push_back(str[i]);
        }
    }
    String(const Array<char>& str) {
        _str = str;
    }
    String(const String& other) {
        _str = other._str;
    }
    ~String() {};


    int length() const {
        return _str.size();
    }
    int size() const {
        return _str.size();
    }
    bool empty() const {
        return _str.empty();
    }


    void push_back(const char ch) {
        _str.push_back(ch);
    }
    void pop_back() {
        _str.pop_back();
    }


    String& operator=(const String& other) {
        _str = other._str;
        return *this;
    }
    char operator[] (const int idx) const {
        if (idx < 0 || _str.size() <= idx) {
            throw std::out_of_range("Out of Range");
        }
        return _str[idx];
    }
    char& operator[] (const int idx) {
        if (idx < 0 || _str.size() <= idx) {
            throw std::out_of_range("Out of Range");
        }
        return _str[idx];
    }


    friend std::ostream& operator<< (std::ostream& os, const String& str) {
        int len = str.size();
        for (int i = 0; i < len; ++i) {
            os << str._str[i];
        }
        return os;
    }
};
#endif