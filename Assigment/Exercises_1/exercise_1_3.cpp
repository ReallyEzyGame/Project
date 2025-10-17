#include <stdio.h>

// Update: we replaced two function asceding and descending sort by a compare function an a sort function base on the compare base

// function pointer using in Sorting function
// Decide if the sorting, priority-base data structure to be Acsending or Descending order
template <typename T>
using compare = bool (*)(T, T);

// Compare Operator
template <typename T>
bool smallerThan(const T val1, const T val2)
{
    return val1 < val2;
}

template <typename T>
bool greaterThan(const T val1, const T val2)
{
    return val1 > val2;
}

// this function help to  swap two value
// to use this, the data type must be built-in data or has operator=
template <typename T>
void swap(T &val1, T &val2)
{
    T tmp = val1;

    val1 = val2;
    val2 = tmp;
}

// Create a Heap data structure from the  given array
// 'mode' which decide which heap after the heapify complete
// greaterThan ==> max heap
// smallerThan ==> min heap
template <typename T>
void heapify(T arr[], const size_t size, const size_t index, compare<T> mode)
{
    size_t left = index * 2 + 1, right = index * 2 + 2;
    size_t largest = index;

    // Find & Swap the most precidence becomes the parent of 2 other nodes
    if (left < size && mode(arr[index], arr[left]))
    {
        swap(arr[index], arr[left]);
        largest = left;
    }
    if (right < size && mode(arr[index], arr[right]))
    {
        swap(arr[index], arr[right]);
        largest = right;
    }

    if (largest != index)
    {
        heapify(arr, size, largest, mode);
    }
}
// HeapSort function help to rearrage the array of data into  order
// the data using must be built-in data type or has operator=
// in 'compare'  type argument, set greaterThan ==> Descending Sort
//                              set smallerThan ==> Acsending Sort
// this function contains an error: if the  given  n is greater than the actual array size ==> Access Memory Violation
template <typename T>
void heapSort(T arr[], const int n, compare<T> mode)
{
    if (n < 0) {
        throw(10);
    }
    // turn the input-array into an heap
    for (int i = n/2 - 1; i >= 0; --i)
        heapify(arr, n, i, mode);
    // HeapSort by continuous Swapping & Heapify
    for (int i = n - 1; i >= 0; --i)
    {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0, mode);
    }
}


int main()
{   
}