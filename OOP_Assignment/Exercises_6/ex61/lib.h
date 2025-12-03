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
private:
  // Increase the Size of the Array
  bool scale_up();
protected:
  int *data;
  int capacity;
  int max_size;
public:
  Array();
  Array(const int);
  Array(const Array &);
  Array(const int *, const int);
  ~Array();

  void push_back(const int);
  void pop_back();

  int operator[](const int) const;
  int &operator[](const int);
  Array &operator=(Array);

  void display() const;
  int size() const;
};

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
  // each value at values[idx] has the frequency of histogram[idx]
  Array values;
  Array histogram;
  void update();
  // This function require the input array must be sorted in acsending order
  static int count_unique(const Array&);
public:
  HistogramArray();
  HistogramArray(const int);
  HistogramArray(const int*, const int);
  HistogramArray(const Array&);
  HistogramArray(const HistogramArray &);
  ~HistogramArray() = default;

  void display();

  int operator[](const int) const;
  int &operator[](const int);
  HistogramArray &operator=(HistogramArray);

  // Requirement: recompute the histogram every time a value is changed
};


void merge(Array&, const int left, const int middle, const int right);
void mergeSort(Array&, const int left, const int right);