#include <exception>
#include <iostream>

template<class T>
class SmartPointer{
private:
  T* _ptr;
public:
  SmartPointer(const SmartPointer<T>& other) = delete;
  SmartPointer& operator= (const SmartPointer<T>& other) = delete;


  SmartPointer(const T data) {
    _ptr = new T(data);
  }
  explicit SmartPointer(const T* ptr = nullptr) {
    _ptr = ptr;
  }
  ~SmartPointer() {
    if (_ptr) {
      delete _ptr;
    }
  }


  // Move Assignment
  SmartPointer& operator=(SmartPointer&& other) noexcept {
    if (_ptr && this != &other) {
      delete _ptr;
      _ptr = other._ptr;
      other._ptr = nullptr;
    }

    return *this;
  }
  T& operator*() {
    if (!_ptr) {
      throw std::runtime_error("Dereference to a null pointer");
    }
    return *_ptr;
  }
  T operator*() const {
    if (!_ptr) {
      throw std::runtime_error("Dereference to a null pointer");
    }
    return *_ptr;
  }
  T* operator->() const {
    if (!_ptr) {
      throw std::runtime_error("Dereference to a null pointer");
    }
    return _ptr;
  }
  T* get() const {
    if (!_ptr) {
      throw std::runtime_error("Dereference to a null pointer");
    }
    return _ptr;
  }
  void reset(T* new_ptr = nullptr) {
    if (_ptr) {
      delete _ptr;
    }
    _ptr = new_ptr;
  }
};



