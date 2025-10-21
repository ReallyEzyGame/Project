

/*
    15/10/2025, Define Class SmartPointer and other utilities
*/

// this is a class help construct, destruct a pointer avoid memory leak and adding more utility to the raw pointer

template <typename T>
class SmartPtr
{
private:
    T *data;

public:
    SmartPtr() = delete;
    SmartPtr(const T val)
    {
        data = new T(val);
    }
    SmartPtr(const T *ptr)
    {
        data = new T(*ptr);
    }
    SmartPtr(const SmartPtr &other)
    {
        data = new T(*other.data);
    }
    ~SmartPtr()
    {
        if (data)
            delete data;
    }

    T get() { return new T(&data); }
    T getData() const { return *data; }

    void copy(const SmartPtr<T> &other)
    {
        if (!data)
            data = new T();
        *data = *other.data;
    }
    void makeSmart(const T *other)
    {
        if (!data)
            data = new T();
        *data = *other;
    }
    void makeSmart(const T val)
    {
        if (!data)
            data = new T();
        *data = val;
    }
    // Compare operator
    bool operator==(const SmartPtr<T> &other) const
    {
        return *data == *other.data;
    }
    bool operator<(const SmartPtr<T> &other) const
    {
        return *data < *other.data;
    }
    bool operator<=(const SmartPtr<T> &other)const 
    {
        return *data <= *other.data;
    }
    bool operator>(const SmartPtr<T> &other) const
    {
        return *data > *other.data;
    }
    bool operator>(const SmartPtr<T> &other) const 
    {
        return *data >= *other.data;
    }
    // Assign operator
    T &operator=(const SmartPtr<T> &other)
    {
        *data = *other.data;
        return *this;
    }
};