#include <iostream>
#include <iterator>
/*
    15/10/2025, Copied the Aray class from ex7 to this file
    16/10/2025, Adding more Parameter Constructor for an Vector
    2/12/2025, Fixing Constructor, operator= and some other methods
*/

typedef unsigned long long size_t;

template <typename T>
class Vector
{
private:
    T *_ptr;
    int _size, _capacity;

public:
    class Iterator;

    Vector() : _size(0), _capacity(0), _ptr(nullptr) {}
    Vector(const int N)
    {
        if (N <= 0)
        {
            _capacity = 0;
            _size = 0;
            _ptr = nullptr;
        }
        else
        {
            _size = N;
            _capacity = N;
            _ptr = new T[_capacity];
        }
    }
    Vector(const T *array, const int N)
    {
        if (N <= 0 || array == nullptr)
        {
            _capacity = 0;
            _size = 0;
            _ptr = nullptr;
        }
        else
        {
            _capacity = N;
            _size = N;

            _ptr = new T[_capacity];
            // Copy the _ptr from the original to the new construct Vector
            for (int i = 0; i < _size; ++i)
            {
                _ptr[i] = array[i];
            }
        }
    }
    Vector(const Vector<T> &other)
    {

        _capacity = other._capacity;
        _size = other._size;

        _ptr = new T[_capacity];

        for (int i = 0; i < _size; ++i)
            _ptr[i] = other._ptr[i];
    }
    Vector(const int N, const T val)
    {
        if (N <= 0)
        {
            _size = 0;
            _capacity = 0;
            _ptr = nullptr;
        }
        else
        {
            _size = N;
            _capacity = N;
            _ptr = new T[_capacity];

            for (int i = 0; i < _size; ++i)
                _ptr[i] = val;
        }
    }
    Vector(const std::initializer_list<T> list) {
        int N = list.size();

        _size = N;
        _capacity = N;
        _ptr = new T[_capacity];

        int i = 0;
        for (auto val : list) {
            _ptr[i] = val;
            i++;
        }
    }
    Vector(Vector&& other) : _ptr(other._ptr), _capacity(other._capacity), _size(other._size) {
        other._ptr = nullptr;
        other._capacity = 0;
        other._size = 0;
    }
    ~Vector()
    {
        if (_ptr)
            delete[] _ptr;
    }

    int size() const
    {
        return _size;
    }
    int capacity() const
    {
        return _capacity;
    }
    bool empty() const
    {
        return _size <= 0;
    }
    int find(const T key) const
    {
        for (int i = 0; i < _size; ++i)
        {
            if (key == _ptr[i])
                return i;
        }
        return -1;
    }

    Iterator begin() const { return _ptr; }
    Iterator end() const { return _ptr + _size; }

    void push_back(const T& val)
    {
        // Extend the _size of the Vector
        if (_size == _capacity)
        {
            scale_up();
        }
        _ptr[_size++] = val;
    }
    void push_back(T&& val) {
        if (_size == _capacity) {
            scale_up();
        }
        _ptr[_size++] = std::move(val);
    }
    void pop_back()
    {
        if (_size >= 0)
        {
            _size--;
        }
    }
    // Compare operator return true if the Vector has the same length & candidate(s)
    bool operator==(const Vector<T>& other)
    {
        // number of _ptr in the Vector is not the same
        if (_capacity != other._capacity)
        {
            return false;
        }

        for (int i = 0; i < _capacity; ++i)
            // Found a differentt candidate
            if (_ptr[i] != other._ptr[i])
                return false;

        return true;
    }
    const T& operator[] (const int idx) const {
        if (0 <= idx && idx < _size) {
            return _ptr[idx];
        }
        throw std::out_of_range("Out of range");
    }
    T &operator[](const int idx)
    {
        if (0 <= idx && idx < _size)
        {
            return _ptr[idx];
        }
        throw std::out_of_range("Out of range");
    }
    Vector<T> &operator=(const Vector<T>& other)
    {
        if (this != &other)
        {
            // if other Vector has more _ptr than this _size then increase the _size
            if (_ptr)
            {
                delete[] _ptr;
            }

            _size = other._size;
            _capacity = other._capacity;

            _ptr = new T[_capacity];
            // Copy the _ptr
            for (int i = 0; i < _size; ++i)
                _ptr[i] = other._ptr[i];
        }
        return *this;
    }
    Vector<T>& operator=(Vector<T>&& other) {
        if (this != &other) {
            if (_ptr)
            {
                delete[] _ptr;
            }
            _ptr = other._ptr;
            _capacity = other._capacity;
            _size = other._size;

            other._ptr = nullptr;
            other._capacity = 0;
            other._size = 0;
        }
        return *this;
    }
    Vector<T> &operator=(const std::initializer_list<T> &list)
    {
        if (_ptr)
        {
            delete[] _ptr;
        }
        _size = list.size();
        _capacity = list.size();
        _ptr = new T[_capacity];

        for (int i = 0; i < _size; ++i)
        {
            _ptr[i] = list[i];
        }

        return *this;
    }

private:
    void scale_up()
    {
        T *tmp_vec = _ptr;
        // Extend the size of the Vector
        _capacity = _capacity == 0 ? 8 : _capacity * 2;
        _ptr = new T[_capacity];

        // Copy the old _ptr
        for (int i = 0; i < _size; ++i)
            _ptr[i] = std::move(tmp_vec[i]);
        // Release Memory of the old Vector
        if (tmp_vec)
            delete[] tmp_vec;
    }

};

template <typename T>
class Vector<T>::Iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using type_value = T;
    using reference = T &;
    using pointer = T *;

private:
    pointer _ptr;

public:
    Iterator(T *ptr = nullptr)
    {
        _ptr = ptr;
    }

    reference operator*() const
    {
        if (!_ptr) {
            throw std::out_of_range("Dereference to an invalid/null pointer");
        }
        return *_ptr;
    }
    pointer operator->() const
    {
        if (!_ptr) {
            throw std::out_of_range("Derefence to an invalid/ null pointer");
        }
        return _ptr;
    }
    reference operator[](const difference_type n)
    {
        return *(_ptr + n);
    }
    Iterator &operator++()
    {
        _ptr++;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator tmp = *this;
        _ptr++;
        return tmp;
    }
    Iterator &operator--()
    {
        _ptr--;
        return *this;
    }
    Iterator operator--(int)
    {
        Iterator tmp = *this;
        _ptr--;
        return tmp;
    }
    Iterator operator+=(const difference_type n)
    {
        _ptr += n;
        return *this;
    }
    Iterator operator-=(const difference_type n)
    {
        _ptr -= n;
        return *this;
    }
    friend Iterator operator+(const difference_type n, const Iterator &it)
    {
        return it + n;
    }
    friend Iterator operator-(const difference_type n, const Iterator &it)
    {
        return it - n;
    }
    friend difference_type operator-(const Iterator &it1, const Iterator &it2)
    {
        return it1._ptr - it2._ptr;
    }
    bool operator==(const Iterator &other)
    {
        return (_ptr == other._ptr);
    }
    bool operator!=(const Iterator &other)
    {
        return !(_ptr == other._ptr);
    }
    bool operator<(const Iterator &other)
    {
        return (_ptr < other._ptr);
    }
    bool operator<=(const Iterator &other)
    {
        return (_ptr <= other._ptr);
    }
    bool operator>(const Iterator &other)
    {
        return (_ptr > other._ptr);
    }
    bool operator>=(const Iterator &other)
    {
        return (_ptr >= other._ptr);
    }

};