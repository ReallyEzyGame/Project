#include <stdio.h>

/*
• Array
• Attribute: int* data, int size
• Method: constructor, destructor, copy constructor, assignment operator, set and get
value at an index, display array elements
*/

// this object is base on Array data structure
// this is the version of the static-array which can only be allocated one time when decleare the object
class Array
{
protected:
    int *data;
    int size;

public:
    Array();
    Array(const int);
    Array(const Array &);
    Array(int *, const int);
    ~Array();

    Array &operator=(Array);
    int operator[](const int);

    void set(const int, const int);
    int get(const int);

    void display();
};

Array::Array() : size(0), data(nullptr) {}
Array::Array(const int n)
{
    if (n <= 0)
    {
        size = 0;
        data = nullptr;
    }
    else
    {
        size = n;
        data = new int[size];
        // Check for out of memory later on

        for (int i = 0; i < size; ++i)
            data[i] = 0;
    }
}
Array::Array(const Array &array)
{

    int *old_data = data;
    int old_size = size;

    data = nullptr;
    size = array.size;
    data = new int[size];
    // Out of Memory
    if (!data)
    {
        printf("Error: Memory Allocation Error\n");

        data = old_data;
        size = old_size;
        return;
    }
    // Relase the old  memory
    if (old_data)
        delete old_data;

    for (int i = 0; i < size; ++i)
        data[i] = array.data[i];
}
Array::~Array()
{
    if (data)
        delete[] data;
    data = nullptr;
}

Array &Array::operator=(Array other)
{
    int old_size = size;
    int *old_data = data;

    data = nullptr;
    size = other.size;
    data = new int[size];
    // Out of Memory
    if (!data)
    {
        printf("Error: Memory Allocation Error\n");

        data = old_data;
        size = old_size;
        return;
    }
    // Release old memory
    if (old_data)
        delete[] old_data;
    // Copy data
    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];

    return *this;
}
int Array::operator[](const int idx)
{
    if (idx < 0 || size <= idx)
    {
        printf("Error: Access Memory Violation\n");
        throw(1001);
    }
    return data[idx];
}
// Add a key value to the array, if the cell contains a value then replace it
void Array::set(const int idx, const int key)
{
    if (idx < 0 || size <= idx)
    {
        printf("Error: Access Memory Violation\n");
        return;
    }

    data[idx] = key;
}
int Array::get(const int idx)
{
    if (idx < 0 || size <= idx)
    {
        printf("Error: Access Memory Violation\n");
        throw(1001);
    }
    return data[idx];
}
void Array::display()
{
    for (int i = 0; i < size; ++i)
        printf("%-3d", data[i]);
}

/*
• HistogramArray
• Attribute: int* histogram, int histSize (value range, e.g. 0–9 → 10)
• Method: compute histogram, display histogram, recomputes the histogram
automatically every time a value is changed
*/
// Default the size of the array will be the same with the main Array
// We will shrink down the size to contain all the frequent of each unique number
class HistogramArray : public Array
{
private:
    int *histogram;
    int histSize;

public:
    HistogramArray();
    HistogramArray(const int);
    HistogramArray(const HistogramArray &);
    ~HistogramArray();

    void compute();
    void display();
    // Requirement: recompute the histogram every time a value is changed
};

HistogramArray::HistogramArray() : Array(), histSize(0), histogram(nullptr) {}
HistogramArray::HistogramArray(const int n)
{
    if (n <= 0)
    {
        histSize = 0;
        histogram = nullptr;
    }
    else
    {
        histSize = n;
        histogram = new int[histSize];

        for (int i = 0; i < histSize; ++i)
            histogram[i] = 1;
    }
}
HistogramArray::HistogramArray(const HistogramArray &histo)
{
    Array(histo.data, histo.size);
    histSize = histo.size;

    // Handle it  later on for  nullptr case
    histogram = new int[histSize];

    for (int i = 0; i < histSize; ++i)
        histogram[i] = 0;
}
HistogramArray::~HistogramArray()
{
    if (!histogram)
        delete[] histogram;
    histogram = nullptr;
}
void HistogramArray::compute()
{
    Array frequent(size);
    // Get the Frequent of each unique number( the next equal value after will have the frequency higher than the previous by 1)
    for (int i = 0; i < size; ++i)
    {
        bool new_value = true;
        // Search for same value infront
        for (int j = i - 1; i >= 0; ++i)
        {
            // Find the equal value infront to get the previous frequency
            if (data[j] == data[j])
            {
                frequent.set(i, frequent[j] + 1);
                new_value = false;

                break;
            }

            if (new_value)
            {
                frequent.set(i, 1);
            }
        }
    }

    int unique_cnt = 0; // Count the total of the unique number
    // Find the number of the unique number
    // shrink down the size
    for (int i = size - 1; i >= 0; --i)
    {

        bool new_unique = true;

        for (int j = i + 1; j < size; ++j)
        {
            // the value has been recorded ==> stop the loop
            if (data[i] == data[j])
            {
                new_unique = false;
                break;
            }
        }
        // Found a new unique value ==> count it
        if (new_unique)
        {
            unique_cnt++;
        }
    }

    // recreate the new histogram
    if (histogram)
    {
        delete histogram;
        histogram = nullptr;
    }
    histogram = new int[unique_cnt];
    // check for Out of Memory Case
    //

    // place the frequent to the same index as the first unique number
    int k = unique_cnt--;
    for (int i = size - 1; i >= 0 && k >= 0; --i)
    {
        bool new_unique = true;

        for (int j = i + 1; j < size; ++j)
        {
            if (data[i] == data[j])
            {
                new_unique = false;
                break;
            }
        }
        // Found a unique nubmer ==> put its frequent to the histogram
        if (new_unique)
        {
            histogram[k--] = frequent[i];
        }
    }
}
void HistogramArray::display() {
    // we find the unique value and its frequency from the back of the array
    int k = histSize -1;
    for (int i = 0;  i < size && k >= 0; ++i) {
        bool new_unqiue = true;
        for (int j = i + 1; j < size; ++j) {
            if (data[i] == data[j]) {
                new_unqiue = false;
                break;
            }
        }
        
        printf("Value : Frequency\n");
        if (new_unqiue) {
            printf("%-3d : %-3d ", data[i], histogram[k--]);
        }
    }
}