#include "lib.h"

Array::Array() :  max_size(0), capacity(0), data(nullptr) {}
Array::Array(const int n) : capacity(0)
{
  if (n <= 0)
  {
    max_size = 0;
    data = nullptr;
  }
  else
  {
    max_size = n;
    data = new int[max_size];
    // Check for out of memory later on

    for (int i = 0; i < capacity; ++i)
      data[i] = 0;
  }
}
Array::Array(const int* array, int N) {
  {
  if (N <= 0)
  {
    max_size = 0;
    capacity = 0;
    data = nullptr;
  }
  else
  {
    max_size = N;
    capacity = N;
    data = new int[max_size];
    // Check for out of memory later on

    for (int i = 0; i < N; ++i)
      data[i] = array[i];
  }
}
}
Array::Array(const Array &array)
{
  max_size = array.max_size;
  capacity = array.capacity;
  data = new int[max_size];
  // Out of Memory
  if (!data)
  {
    printf("Error: Memory Allocation Error\n");

    *this = Array();
    return;
  }

  for (int i = 0; i < max_size; ++i)
    data[i] = array.data[i];
}
Array::~Array()
{
  if (data)
    delete[] data;
  data = nullptr;
}


void Array::push_back(const int val)
{
  if (capacity == max_size)
  {
    if (!scale_up())
    {
      throw("Out of Range");
    }
  }
  data[capacity++] = val;
}
void Array::pop_back()
{
  if (capacity > 0)
  {
    capacity--;
  }
}
bool Array::scale_up()
{
  if (max_size == 0)
  {
    max_size = 256;
  }
  else
  {
    max_size *= 2;
  }

  int *tmp_arr = data;
  data = new int[max_size];

  if (!data)
  {
    return false;
  }

  for (int i = 0; i < capacity; ++i)
    data[i] = tmp_arr[i];

  if (tmp_arr)
    delete[] tmp_arr;
  return true;
}
Array &Array::operator=(Array other)
{
  int old_cap = capacity;
  int old_size = max_size;
  int *old_data = data;

  data = nullptr;
  max_size = other.max_size;
  capacity = other.capacity;
  data = new int[max_size];
  // Out of Memory
  if (!data)
  {
    printf("Error: Memory Allocation Error\n");

    capacity = old_cap;
    data = old_data;
    max_size = old_size;
    return *this;
  }
  // Release old memory
  if (old_data)
    delete[] old_data;
  // Copy data
  for (int i = 0; i < capacity; ++i)
    data[i] = other.data[i];

  return *this;
}
int Array::operator[](const int idx) const
{
  if (idx < 0 || capacity <= idx)
  {
    printf("Error: Access Memory Violation\n");
    throw(1001);
  }
  return data[idx];
}
int &Array::operator[](const int idx)
{
  if (idx < 0 || capacity <= idx)
  {
    printf("Error: Access Memory Violation\n");
    throw(1001);
  }
  return data[idx];
}


int Array::size() const {
  return capacity;
}
void Array::display() const
{
  for (int i = 0; i < capacity; ++i)
    printf("%-3d", data[i]);
}




HistogramArray::HistogramArray() : Array() { histogram = Array(); }
HistogramArray::HistogramArray(const int n) : Array()
{
  if (n <= 0)
  {
    histogram = Array();
  }
  else
  {
    histogram = Array(n);
  }
}
HistogramArray::HistogramArray(const int* array, const int N) : Array(array, N) {}
HistogramArray::HistogramArray(const Array& other) : Array(other){}
HistogramArray::HistogramArray(const HistogramArray &histo) : Array(histo), histogram(histo.histogram) {}


void HistogramArray::update()
{
  histogram = Array();
  values = Array();

  int N = Array::size();
  if (N == 0) {
    return; 
  }

  
  Array tmp_arr = *this; 
  mergeSort(tmp_arr, 0, N - 1);
 
  int idx = 0;
  while (idx < N) {
    
    int val = tmp_arr[idx];
    int cnt = 0;
    
    while (idx < N && tmp_arr[idx] == val) {
      cnt++;
      idx++;
    }

    values.push_back(val);
    histogram.push_back(cnt);
  }
}


void HistogramArray::display()
{
  update();

  for (int i = 0; i < histogram.size(); ++i) {
    printf("%d : %d\t", values[i], histogram[i]);
  }
}


HistogramArray &HistogramArray::operator=(HistogramArray other)
{
  Array::operator=(other);
  histogram = other.histogram;
  values = other.values;
  
  return *this;
}
int &HistogramArray::operator[](const int idx)
{
  return Array::operator[](idx);
}
int HistogramArray::operator[](const int idx) const
{
  return Array::operator[](idx);
}




void merge(Array& array, const int left, const int middle, const int right) {
  int idx = 0, l = left, m = middle + 1;
  int N = right - left + 1;
  int tmp_arr[N];
  

  while (l <= middle && m <= right) {
    tmp_arr[idx++] = array[l] < array[m] ? array[l++] : array[m++];
  }
  while (l <= middle)
  {
    tmp_arr[idx++] = array[l++];
  }
  while (m <= right) {
    tmp_arr[idx++] = array[m++];
  }

  for (int k = 0; k < N; ++k) {
    array[k + left] = tmp_arr[k];
  }
}
void mergeSort(Array& array, const int left, const int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);

    merge(array, left, mid, right);
  }
}