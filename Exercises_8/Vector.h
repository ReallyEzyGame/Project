#include <iostream>

template <typename T>
class Vector{
private:
  T* _data;
  int _size, _capacity;
  // Extern the size of the Vector
  bool scale_up();
public:
  Vector() {
    _size = 0;
    _capacity = 0;
    _data = nullptr;
  }
  Vector(const int N) {
    _size = 0;
    _capacity = std::abs(N);

    _data = new T[_capacity];
  }
  Vector(const int N, const T value) {
    _size = std::abs(N);
    _capacity = std::abs(N);

    _data = new T[_capacity];

    for (int i  = 0; i < _size; ++i) {
      _data[i] = value;
    }
  }
  Vector(const std::initialize_list<T> list) {
    _size = std::abs(list.size());
    _capacity = std::abs(list.size());

    _data = new T[_capacity];
    for (int i = 0; i  < _size; ++i) {
      _data[i] = list[i];
    }
  }
  Vector(const Vector& other) {
    _size  = other._size;
    _capacity = other._capacity;

    _data = new T[_size];
    for (int i = 0;  i < _size; ++i) {
      _data = other._data[i];
    }
  }
  ~Vector() {
    if (_data) {
      delete[] _data;
    }
  }


  void  push_back(const T value) {
    if (_size == _capacity) {
      scale_up();
    }
    _data[_size++] = value;
  }
  void pop_back() {
    if (_size > 0) {
      _size--;
    }
  }



  size_t size() const { return  _size;}
  size_t capacity() const { return _capacity;}


};



int main() {
}