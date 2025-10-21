/*
    15/10/2025, Copied the Aray class from ex7 to this file
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
    // Construct the Array T value from normal array
    // if the size ==> Aaccess memory Violation
    // if the size is smaller than the actual array then the Array will left off all the value behind n
    Array(const int n, const T* arr) : capacity(0) {
        if (n <=  0) {
            size =  0;
            data = nullptr;
        }
        else {
            size = n;
            data = new T[size];

            for (int i = 0; i < size; ++i) 
                *this->push_back(T[i]);
        }
    }
    Array(const Array<T> &arr) : size(arr.size), capacity(arr.capacity)
    {
        data = new T[size];

        for (int i = 0; i < size; ++i)
            data[i] = arr.data[i];
    }
    Array(const int n, const T val) : data(nullptr)
    {
        data = new T[n];
        if (!data)
        {
            printf("Error: Memory Allocation Error\n");
            return;
        }

        for (int i = 0; i < n; ++i)
            data[i] = val;
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
    size_t find(const T key) {
        for (int i = 0; i < capacity; ++i) {
            if (key == data[i])
                return i;
        }
        return __LONG_LONG_MAX__;
    }

    
    T* begin() { return data;}
    T* end() {return data + capacity;}


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
        if (capacity)
        {
            data[--capacity] = T();
            return;
        }
    }


    T operator[](const int idx) const
    {
        if (0 <= idx && idx < capacity)
        {
            return data[idx];
        }
        printf("Error: Access Memory Violation\n");
        throw(101);
    }
    T &operator=(const Array<T> &other)
    {
        // if other array has more data than this size then increase the size
        if (this->size < other.capacity)
        {
            this->capacity = other.capacity;
            this->size = other.size;

            delete[] this->data;
            this->data = new T[size];
        }
        // Copy the data
        for (int i = 0; i < capacity; ++i)
            this->data[i] = other.data[i];

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
            data[i] = tmp_arr[i];
        // Release Memory of the old array
        if (tmp_arr)
            delete[] tmp_arr;
        return true;
    }
};