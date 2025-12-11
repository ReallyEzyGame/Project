#include <exception>
#include <iostream>

template<class T>
class UniquePointer{
private:
  T* _ptr;
public:

  UniquePointer(const UniquePointer<T>& other) = delete;
  UniquePointer& operator= (const UniquePointer<T>& other) = delete;

  template<class U> friend class UniquePointer;      // Allow inheritence
  template<class U> 
  UniquePointer(UniquePointer<U>&& other) noexcept {
    _ptr = other._ptr;
    other._ptr = nullptr;
  }
  template<class U>
  UniquePointer& operator= (UniquePointer<U>&& other) noexcept {
    if (_ptr != other._ptr) {
      delete _ptr;
     _ptr = other._ptr;
     other._ptr = nullptr;
    }

    return *this;
  }
  
  UniquePointer(const T data) {
    _ptr = new T(data);
  }
  explicit UniquePointer(T* ptr = nullptr) {
    _ptr = ptr;
  }
  ~UniquePointer() {
    delete _ptr;
  }


  // Move Assignment
  UniquePointer& operator=(UniquePointer&& other) noexcept {
    if (this != &other) {
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

  UniquePointer<T> copy() const {
    return UniquePointer<T>(*_ptr);
  }
};




template<class T>
class SharedPointer;