#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using Comparision = bool (*)(int, int);
bool smallerThan(const int num1, const int num2);
bool greaterThan(const int num1, const int num2);

// return new position of the pivot in the array
int partition(int *array, const int begin, const int end, Comparision mode);
// QuickSort algorithm for sorting integer Array
// Comparison mode: smaller than ==> Sort Descending order
//                  greaterThan  ==> Sort Ascending order
void quickSort(int *array, const int begin, const int end, Comparision mode = greaterThan);

// this class based on the data structure array with more utility to perform better on handling data on array
class Array
{
    friend int partition(Array &, const int, const int, Comparision);

private:
    int size = 0;
    int *array = nullptr;

public:
    Array();
    Array(const int);
    Array(int *, const int);
    Array(const Array &);
    ~Array();

    void input(int *, const int);
    void output() const;

    int getSize() const;
    void setSize(const int);

    int getElement(const int) const;
    void setElement(int, int);
    // Look for a value & return the index, return -1 if not found
    int find(const int) const;
    void sort(Comparision);
};