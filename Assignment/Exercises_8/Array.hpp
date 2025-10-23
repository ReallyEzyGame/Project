#include <cstring>
#include <stdio.h>

/*
    15/10/2025, Copied the Aray class from ex7 to this file
    16/10/2025, Adding more Parameter Constructor for an array
*/

typedef unsigned long long size_t;

template <typename T>
class Array
{
private:
    T *data;
    size_t size, capacity;

public:
    Array() : size(0), capacity(0), data(nullptr) {}
    Array(const int n) : capacity(0)
    {
        if (n <= 0)
        {
            size = 0;
            data = nullptr;
        }
        else
        {
            size = n;
            data = new T[size];

            for (int i = 0; i < size; ++i)
                this->push_back(T());
        }
    }
    Array(const T *arr) : capacity(0)
    {
        if (arr == nullptr)
        {
            size = 0;
            data = nullptr;
        }
        else
        {
            size = strlen(arr);
            data = new T[size];
            // Copy the Data from the original to the new construct array
            for (int i = 0; i < size; ++i)
                this->push_back(arr[i]);
        }
    }
    // Construct the Array T value from normal array
    // if the size ==> Aaccess memory Violation
    // if the size is smaller than the actual array then the Array will left off all the value behind n
    Array(const int n, const T *arr) : capacity(0)
    {
        if (n <= 0)
        {
            size = 0;
            data = nullptr;
        }
        else
        {
            size = n;
            data = new T[size];

            for (int i = 0; i < size; ++i)
                *this->push_back(arr[i]);
        }
    }
    Array(const Array<T> &arr) : size(arr.size), capacity(arr.capacity)
    {
        data = new T[size];

        for (int i = 0; i < size; ++i)
            data[i] = arr.data[i];
    }
    Array(const int n, const T val) : data(nullptr), capacity(0)
    {
        if (n <= 0)
            size = n;
        else
        {
            size = n;
            data = new T[size];
            if (!data)
            {
                printf("Error: Memory Allocation Error\n");
                return;
            }

            for (int i = 0; i < n; ++i)
                *this->push_back(val);
        }
    }
    ~Array()
    {
        if (data)
            delete[] data;
    }

    size_t getSize() const
    {
        return size;
    }
    bool empty() const
    {
        return capacity == 0;
    }
    size_t find(const T key) const
    {
        for (int i = 0; i < capacity; ++i)
        {
            if (key == data[i])
                return i;
        }
        return __LONG_LONG_MAX__;
    }

    T *begin() const { return data; }
    T *end() const { return data + capacity; }

    void push_back(const T val)
    {
        // Extend the size of the array
        if (capacity == size)
            if (!extend())
            {
                printf("Error: Out of Memory\nCannot extend the size of the array\n");
                return;
            }
        data[capacity++] = val;
    }
    void pop_back()
    {
        if (capacity >=  0)
        {
            data[--capacity] = T();
            return;
        }
    }
    // Compare operator return true if the array has the same length & candidate(s)
    bool operator==(const Array<T> other)
    {
        // number of data in the array is not the same
        if (capacity != other.capacity)
        {
            return false;
        }

        for (int i = 0; i < capacity; ++i)
            // Found a differentt candidate
            if (data[i] != other.data[i])
                return false;

        return true;
    }
    T& operator[](const int idx) const
    {
        if (0 <= idx && idx < capacity)
        {
            return data[idx];
        }
        printf("Error: Access Memory Violation\n");
        throw(101);
    }
    Array<T> &operator=(const Array<T> other)
    {
        // if other array has more data than this size then increase the size
        if (data == nullptr || this->size < other.capacity)
        {
            
            size = other.size;

            delete[] data;
            data = new T[size];
        }
        // Copy the data
        capacity = 0;
        for (int i = 0; i < capacity; ++i)
            this->push_back(other[i]);

        return *this;
    }
    Array<T> &operator=(const T *arr)
    {
        if (arr == nullptr)
            return *this;

        if (data)
            delete data;

        size = strlen(arr);
        data = new T[size];

        capacity = 0;

        for (int i = 0; i < size; ++i)
            this->push_back(data[i]);

        return *this;
    }

private:
    bool extend()
    {
        int tmp_size = size;
        size = size == 0 ? 8 : size * 2;

        T *tmp_arr = data;
        data = new T[size];
        // Memory Allocation Failed
        if (data == tmp_arr)
        {
            return false;
        }
        // Copy the old data
        for (int i = 0; i < tmp_size; ++i)
            this->push_back(tmp_arr[i]);
        // Release Memory of the old array
        if (tmp_arr)
            delete[] tmp_arr;
        return true;
    }
};