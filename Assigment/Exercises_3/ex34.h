#include <stdio.h>
#include <stdlib.h>
#include <time.h>


template<typename T>
using Comparision = bool (*)(T, T);

template<typename T>
bool smallerThan(const T num1, const T num2);
template<typename T>
bool greaterThan(const T num1, const T num2);

// return new position of the pivot in the array
template<typename T>
int partition(T *array, const int begin, const int end, Comparision<T> mode);
// QuickSort algorithm for sorting integer Array
// Comparison mode: smaller than ==> Sort Descending order
//                  greaterThan  ==> Sort Ascending order
template<typename T>
void quickSort(T *array, const int begin, const int end, Comparision<T> mode);

// this class based on the data structure array with more utility to perform better on handling data on array
template<typename T>
class Array
{
private:
    int size = 0;
    T *array = nullptr;

public:
    Array();
    Array(const int);
    Array(T *, const int);
    Array(const Array<T> &);
    ~Array();

    void input(T *, const int);
    void output() const;

    int getSize() const;
    void setSize(const int);

    T getElement(const int) const;
    void setElement(int, T);
    // Look for a value & return the index, return -1 if not found
    T find(const T) const;
    void sort(Comparision<T>);
};