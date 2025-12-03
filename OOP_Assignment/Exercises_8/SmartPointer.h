

/*
    15/10/2025, Define Class SmartPointer and other utilities
*/

// this is a class help construct, destruct a pointer avoid memory leak and adding more utility to the raw pointer
template <typename T>
class SmartPointer
{
private:
    T *_ptr;

public:
    SmartPointer(const SmartPointer &other) = delete;
    SmartPointer& operator(const SmartPointer& other) = delete;

    explicit SmartPointer(const T val)
    {
        _ptr = new T(val);
    }
    explicit SmartPointer(const T *ptr = nullptr)
    {
        _ptr = new T(*ptr);
    }
    SmartPointer(SmartPointer&& other) noexcept {
        _ptr = other._ptr;
        other._ptr = nullptr;   
    }
    ~SmartPointer()
    {
        if (_ptr)
            delete _ptr;
    }

    // Assign operator
    SmartPtr<T> &operator=(const SmartPtr<T>&& other) noexcept
    {
        if (this != &other) {
            delete _ptr;
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }
    T& operator*() const {
        return *_ptr;
    }
    T* operator->() const {
        return _ptr;
    }
    T* get() const {
        return _ptr;
    }
    T* release() {
        T* temp = _ptr;
        _ptr = nullptr;
        return temp;
    }
    void reset(T* new_ptr = nullptr) {
        if (_ptr) {
            delete _ptr;
        }
        _ptr = new_ptr;
    }
    // Compare operator
    bool operator==(const SmartPtr<T> &other) const noexcept
    {
        return *_ptr == *other._ptr;
    }
    bool operator<(const SmartPtr<T> &other) const noexcept
    {
        return *_ptr < *other._ptr;
    }
    bool operator<=(const SmartPtr<T> &other)const noexcept
    {
        return *_ptr <= *other._ptr;
    }
    bool operator>(const SmartPtr<T> &other) const noexcept
    {
        return *_ptr > *other._ptr;
    }
    bool operator>=(const SmartPtr<T> &other) const noexcept
    {
        return *_ptr >= *other._ptr;
    }
};