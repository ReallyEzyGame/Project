#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Array;

using Comparision = bool (*)(int, int);

bool smallerThan(const int num1, const int num2);
bool greaterThan(const int num1, const int num2);

// return new position of the pivot in the array
int partition(int *array, const int begin, const int end, Comparision mode);
// QuickSort algorithm for sorting integer Array
// Comparison mode: smaller than ==> Sort Descending order
//                  greaterThan ==> Sort Ascending order
void quickSort(int *array, const int begin, const int end, Comparision mode);


class Array
{
private:
    int size;
    int *array;

public:
    Array();
    Array(const int);
    Array(const int *, const int);
    Array(const Array &);
    ~Array();

    void input();
    void output() const;
    int getSize() const;
    void setSize(const int);
    int getElement(const int) const;
    void setElement(int, int);
    // Look for a value & return the index, return -1 if not found
    int find(const int) const;
    Array sort(Comparision);
};

