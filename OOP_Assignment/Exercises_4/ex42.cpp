#include <stdio.h>
#include <istream>
#include <ostream>

#include <stdlib.h>

#include <time.h>

class Array;

template <typename T>
void swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}

using Comparision = bool (*)(int, int);

bool smallerThan(const int num1, const int num2)
{
    return num1 < num2;
}
bool greaterThan(const int num1, const int num2)
{
    return num1 > num2;
}

// return new position of the pivot in the array
int partition(int *array, const int begin, const int end, Comparision mode)
{
    srand(time(NULL));
    // get a random value in range to use as pivot
    swap<int>(array[end], array[rand() % (end - begin) + begin]);
    // using  the last value in range as the pivot
    int i = begin, j = begin;
    for (; j <= end; ++j)
    {
        if (array[j] < array[end])
        {
            swap(array[i], array[j]);
            i++;
        }
    }

    swap(array[i], array[end]);
    return i;
}
// QuickSort algorithm for sorting integer Array
// Comparison mode: smaller than ==> Sort Descending order
//                  greaterThan  ==> Sort Ascending order
void quickSort(int *array, const int begin, const int end, Comparision mode = greaterThan)
{
    if (begin < end)
    {
        int pivot = partition(array, begin, end, mode);

        quickSort(array, begin, pivot - 1, mode);
        quickSort(array, pivot + 1, end, mode);
    }
}

// this class based on the data structure array with more utility to perform better on handling data on array
class Array
{
    friend int partition(Array &, const int, const int, Comparision);

private:
    int size = 0; // the true size of the array
    int back = 0; // number of cell that contain real data
    int *array = nullptr;

    // Extern the size of the array by double it
    // copy data from the old array
    bool externSize();

public:
    Array();
    Array(const int);
    Array(int *, const int);
    Array(const Array &);
    ~Array();

    void input(int *, const int);
    void output() const;
    // Add a value to  the back of the array
    void push_back(int);
    int getSize() const;
    void setSize(const int);

    int getElement(const int) const;
    void setElement(int, int);
    // Look for a value & return the index, return -1 if not found
    int find(const int) const;
    void sort(Comparision);

    // Concentation
    Array operator+(Array);
    Array operator+(Array&);
    // Assignment
    Array &operator=(Array);
    Array &operator+=(Array);
    // Array Index
    int operator[](int);
    // Type-cast
    int *operator=(int *);
    // Input
    friend std::istream &operator>>(std::istream &is, const Array &);
};


// Constructor & Destructor of Array class
Array::Array() : size(0), back(0), array(nullptr) {}
Array::Array(const int len)
{
    // Default Construct if the length of the array is invalid
    if (len <= 0)
    {
        *this = Array();
    }

    size = back = len;
    array = new int[size];
    // Allocation Error
    if (!array)
    {
        printf("Error: Allocation memory failed\nUsing Default Constructor\n");

        *this = Array();
        return;
    }

    for (int i = 0; i < size; ++i)
        array[i] = 0;
}
Array::Array(int *arr, const int len)
{
    *this = Array(len);

    // Deep copy from the old array
    // Avoid shallow copy
    if (size == len)
        for (int i = 0; i < size; ++i)
            array[i] = arr[i];
    back = len;
}
Array::Array(const Array &arr)
{
    size = back = arr.getSize();

    array = new int[size];
    if (!array)
    {
        printf("Error: Memory Allocation Error\nUsing default constructor\n");

        *this = Array();
        return;
    }
    // Deep Copy from the old array
    // Avoid Shallow copy
    for (int i = 0; i < size; ++i)
        array[i] = arr.array[i];
}
Array::~Array()
{
    // delete the allocate memory if there is
    if (array)
        delete[] array;
    array = nullptr;
}


void Array::input(int *arr, const int n)
{
    int *old_array = array;
    array = new int[size];

    if (!array)
    {
        printf("Error: Out of Memory for Allocation\n");

        array = old_array;
        return;
    }

    // Dismiss the old array
    if (old_array != nullptr)
    {
        delete[] old_array;
        old_array = nullptr;
    }

    // Copy a the Data
    for (size_t i = 0; i < n; ++i)
    {
        array[i] = arr[i];
    }
    size = back = n;
}
void Array::push_back(int value)
{
    // Array out of cell left ==> Extern it
    if (back == size)
    {
        if (!externSize())
        {
            printf("Error: Unable to Allocation Memory\n");
            return;
        }
    }
    array[back++] = value;
}

// Replace the already exist value in the array with a new one
void Array::setElement(const int idx, const int value)
{
    if (idx >= 0 && idx < back)
        array[idx] = value;
}
int Array::getSize() const
{
    return back;
}
bool Array::externSize() {
    size = (size == 0) ? 1 : size * 2;

    Array old_array = *this;
    array = new int[size];
    
    // Out of Memory
    if (!array) {
        printf("Error: Unable to Allocation Memory\n");

        *this = old_array;
        return false;
    }
    // Copy the data from the old array
    for (int i = 0; i < old_array.size; ++i)
        array[i] = old_array[i];
    return true;
}
void Array::setSize(const int n)
{
    int *old_array = array;
    int old_size = size;

    int idx = 0;
    size = back = n;
    array = new int[n];

    if (!array)
    {
        printf("Error: Out of Memory for Allocation\n");

        array = old_array;
        size = back = old_size;
        return;
    }

    // Copy the data to the new array
    while (idx < old_size && idx < n)
        array[idx] = old_array[idx++];
    // new allocation array greater than new one
    // default all the new value --> 0
    while (idx < n)
        array[idx++] = 0;
}

// Return the element at idx
int Array::getElement(const int idx) const
{
    if (idx < 0 || idx >= back)
        return -1;
    return array[idx];
}
int Array::find(const int key) const
{
    for (int i = 0; i < back; ++i)
        if (array[i] == key)
            return i;
    return -1;
}
void Array::output() const
{
    for (int i = 0; i < back; ++i)
        printf("%-5d", array[i]);
    printf("\n");
}

// Sorting the array in order
// if Default => Sorting in Acsending Order
void Array::sort(Comparision comparision = greaterThan)
{
    quickSort(array, 0, back - 1, comparision);
}


int Array::operator[](int idx){
    if (idx < 0 || back <= idx)
        return INT_MIN;
    return array[idx];
}
Array Array::operator+ (Array other) {
    for (int i = 0; i < other.size; ++i)
        this->push_back(other[i]);

    return *this;
}
int* Array::operator= (int*) {
    if (size <= 0) return nullptr;

    int* copy = new int[size];
    if (!copy) {
        printf("Error: Unable to Allocate Memory\n");

        return nullptr;
    }

    for (int i = 0; i < size; ++i)
        copy[i] = array[i];
        
    return copy;
}
Array& Array::operator= (Array other) {
    Array old_array = *this;
    
    size = other.size;
    back = other.back;
    array = new int[size];
    // Out of Memory
    if  (!array) {
        printf("Error: Unable to Allocate Memory\n");

        *this = old_array;
        return *this;
    }
    // Copy the data
    for (int i = 0; i < back; ++i)  
        array[i] = other[i];

    return *this;
}
Array& Array::operator+=(Array other) {
    for (int i = 0; i < other.size; ++i)
        this->push_back(other[i]);

    return *this;
}


// Using input operator>> while assign a new list of data in the array also remove the old one
std::istream &operator>>(std::istream &is, Array &array)
{
    int value;
    while (is >> value) {
        array.push_back(value);
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, Array &array)
{
    for (int i = 0; i < array.getSize(); ++i)
        os << array[i];

    return os;
}

int main()
{
    int array[5] = {10, 20, 30, 40, 50};

    Array arr(array, 5);

    arr.output();

    Array arr2(arr);

    arr2.output();
}