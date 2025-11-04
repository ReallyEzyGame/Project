#include "lib.h"

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


Array::Array() : size(0), array(nullptr) {}
Array::Array(const int n)
{
    size = n;
    array = nullptr;
    array = new int[n];

    if (!array)
    {
        printf("Error: Memory Allocation Error\n");

        size = 0;
        return;
    }

    // Copy data from the arr
    for (int i = 0; i < size; ++i)
        array[i] = 0;
}
Array::Array(const int *arr, const int n)
{
    size = n;
    array = nullptr;
    array = new int[n];

    if (!array)
    {
        printf("Error: Memory Allocation Error\n");

        size = 0;
        return;
    }

    // Copy data from the arr
    for (int i = 0; i < size; ++i)
        array[i] = arr[i];
}
Array::Array(const Array &arr)
{
    size = arr.size;
    // Invalid Size
    if (size <= 0) {
        size =  0;
        array = nullptr;
        return;
    }

    array = nullptr;
    array = new int[size];
    // Out of Memory
    if (!array)
    {
        printf("Error: Memory Allocation Error\n");

        size =  0;
        array = nullptr;
        return;
    }

    for (int i = 0; i < size; ++i)
        array[i] = arr.array[i];
}
Array::~Array()
{
    if (array)
        delete[] array;
    array = nullptr;
}


void Array::input()
{
    
    int n, *arr = nullptr;
    Array old_array = *this;        // Temporary Assign to get back data if the allocation fail

    printf("Input array size & candidate(s): ");
    scanf("%d", &n);
    // Valid Size only
    if (n > 0)
    {
        arr = new int[n];
        // Out of Memory
        if (!arr)
        {
            printf("Error: Memory Allocation Error\n");

            *this = old_array;
            return;
        }


        for (int i = 0; i < n; ++i)
            scanf("%d", &arr[i]);

        *this = Array(arr, n);
    }
}
void Array::output() const
{
    for (int i = 0; i < size; ++i)
        printf("%-5d", array[i]);
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
// Replace the already exist value in the array with a new one
void Array::setElement(const int idx, const int value)
{
    if (idx >= 0 && idx < size)
        array[idx] = value;
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
Array Array::sort(Comparision comparision)
{
    Array arr(array, size);

    quickSort(arr.array, 0, arr.size - 1, comparision);

    return arr;
}


// return new position of the pivot in the array
int partition(int *array, const int begin, const int end, Comparision mode)
{
    srand(time(NULL));
    // get a random value in range to use as pivot
    swap<int>(array[end], array[rand() % (end - begin) + begin]);
    // using  the last value in range as the pivot
    int i = begin - 1, j = begin;
    for (; j <= end; ++j)
    {
        if (mode(array[j], array[end]))
        {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[end]);
    return i + 1;
}
// QuickSort algorithm for sorting integer Array
// Comparison mode: smaller than ==> Sort Descending order
//                  greaterThan  ==> Sort Ascending order
void quickSort(int *array, const int begin, const int end, Comparision mode)
{
    if (begin < end)
    {
        int pivot = partition(array, begin, end, mode);

        quickSort(array, begin, pivot - 1, mode);
        quickSort(array, pivot + 1, end, mode);
    }
}