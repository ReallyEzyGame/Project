#include "ex34.h"
#include <iostream>


// To use all the method and utility in class Array such as sort(), the data contained in Array must have the comparision operator, output operator  or have methods to assit the print out function in C/C++

template<typename T>
class Array;

template <typename T>
void swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}

template<typename T>
using Comparision = bool (*)(T, T);

template<typename T>
bool smallerThan(const T num1, const T num2)
{
    return num1 < num2;
}
template<typename T>
bool greaterThan(const T num1, const T num2)
{
    return num1 > num2;
}

// return new position of the pivot in the array
template<typename T>
int partition(T *array, const int begin, const int end, Comparision<T> mode)
{
    srand(time(NULL));
    // get a random value in range to use as pivot
    swap<T>(array[end], array[rand() % (end - begin) + begin]);
    // using  the last value in range as the pivot
    int i = begin, j = begin;

    
    for (; j <= end; ++j)
    {
        if (mode(array[j], array[i]))
        {
            i++;
            swap<T>(array[i], array[j]);
        }
    }

    swap(array[i], array[end]);
    return i;
}
// QuickSort algorithm for sorting integer Array
// Comparison mode: smaller than ==> Sort Descending order
//                  greaterThan  ==> Sort Ascending order
template<typename T>
void quickSort(T *array, const int begin, const int end, Comparision<T> mode)
{
    if (begin < end)
    {
        int pivot = partition(array, begin, end, mode);

        quickSort(array, begin, pivot - 1, mode);
        quickSort(array, pivot + 1, end, mode);
    }
}

// Constructor & Destructor of Array class
template<typename T>
Array<T>::Array() : size(0), array(nullptr) {}
template<typename T>
Array<T>::Array(const int len) {
    // Default Construct if the length of the array is invalid
    if (len <= 0) {
        *this =  Array();
    }

    size = len;
    array = new T[size];
    // Allocation Error
    if (!array)
    {
        printf("Error: Allocation memory failed\nUsing Default Constructor\n");

        *this = Array();
        return;
    }
}
template<typename T>
Array<T>::Array(T *arr, const int len) {
    *this = Array(len);

    // Deep copy from the old array
    // Avoid shallow copy
    if (size == len)
        for (int i = 0; i < size; ++i)
            array[i] = arr[i];
}
template<typename T>
Array<T>::Array(const Array<T> &arr) {
    size = arr.getSize();

    array = new T[size];
    if (!array) {
        printf("Error: Memory Allocation Error\nUsing default constructor\n");

        *this = Array();
        return;
    }
    // Deep Copy from the old array
    // Avoid Shallow copy
    for (int i = 0; i < size; ++i)
        array[i] = arr.array[i];
}
template<typename T>
Array<T>::~Array() {
    // delete the allocate memory if there is
    if (array)
        delete[] array;
    array = nullptr;
}


template<typename T>
void Array<T>::input(T *arr, const int n)
{
    T *old_array = array;
    array = new T[size];

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
    size = n;
}
template<typename T>
void Array<T>::output() const
{
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    printf("\n");
}

// Replace the already exist value in the array with a new one
template<typename T>
void Array<T>::setElement(const int idx, const T value)
{
    if (idx >= 0 && idx < size)
        array[idx] = value;
}
template<typename T>
int Array<T>::getSize() const
{
    return size;
}
template<typename T>
void Array<T>::setSize(const int n)
{
    T *old_array = array;
    int old_size = size;

    int idx = 0;
    size = n;
    array = new T[n];

    if (!array)
    {
        printf("Error: Out of Memory for Allocation\n");

        array = old_array;
        size = old_size;
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
template<typename T>
T Array<T>::getElement(const int idx) const
{
    if (idx < 0 || idx >= size)
        return array[0];

    return array[idx];
}
template<typename T>
T Array<T>::find(const T key) const
{
    for (int i = 0; i < size; ++i)
        if (array[i] == key)
            return i;

    return array[size - 1];
}
// Sorting the array in order
// if Default => Sorting in Acsending Order
template<typename T>
void Array<T>::sort(Comparision<T> comparision)
{
    quickSort(array, 0, size - 1, comparision);
}

int main()
{
    int array[5]   = {10,20,30,40,50};

    Array<int> arr(array,5);

    arr.output();
    
    Array arr2(arr);

    arr2.output();

    char arr_ch[5] = {'c', 'a', 'n', 'A', 'B'};
    Array arr3(arr_ch, 5);

    arr3.output();
    arr3.sort(greaterThan);
    arr3.output();
    arr3.sort(smallerThan);
    arr3.output();
}