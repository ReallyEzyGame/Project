#include "ex33.h"

class Array;

template <typename T>
void swap(T &a, T &b)
{
    T c = a;
    a = b;
    b = c;
}



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



// Constructor & Destructor of Array class
Array::Array() : size(0), array(nullptr) {}
Array::Array(const int len) {
    // Default Construct if the length of the array is invalid
    if (len <= 0) {
        *this =  Array();
    }

    size = len;
    array = new int[size];
    // Allocation Error
    if (!array)
    {
        printf("Error: Allocation memory failed\nUsing Default Constructor\n");

        *this = Array();
        return;
    }

    for (int i = 0; i < size; ++i)
        array[i]  = 0;
}
Array::Array(int *arr, const int len) {
    *this = Array(len);

    // Deep copy from the old array
    // Avoid shallow copy
    if (size == len)
        for (int i = 0; i < size; ++i)
            array[i] = arr[i];
}
Array::Array(const Array &arr) {
    size = arr.getSize();

    array = new int[size];
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
Array::~Array() {
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
    size = n;
}
void Array::output() const
{
    for (int i = 0; i < size; ++i)
        printf("%-5d", array[i]);
    printf("\n");
}

// Replace the already exist value in the array with a new one
void Array::setElement(const int idx, const int value)
{
    if (idx >= 0 && idx < size)
        array[idx] = value;
}
int Array::getSize() const
{
    return size;
}

void Array::setSize(const int n)
{
    int *old_array = array;
    int old_size = size;

    int idx = 0;
    size = n;
    array = new int[n];

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
int Array::getElement(const int idx) const
{
    if (idx < 0 || idx >= size)
        return -1;
    return array[idx];
}

int Array::find(const int key) const
{
    for (int i = 0; i < size; ++i)
        if (array[i] == key)
            return i;
    return -1;
}
// Sorting the array in order
// if Default => Sorting in Acsending Order
void Array::sort(Comparision comparision = greaterThan)
{
    quickSort(array, 0, size - 1, comparision);
}

int main()
{
    int array[5]   = {10,20,30,40,50};

    Array arr(array,5);

    arr.output();
    
    Array arr2(arr);

    arr2.output();
}