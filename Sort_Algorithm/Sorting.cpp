#include <iostream>

using namespace std;

class SortAlgorithm {
    private:
    static SortAlgorithm* _algorithm;
    void (*currentAlgorithm)(double[], int);
    SortAlgorithm();
    public:
    static SortAlgorithm* getObject(void(*pAg)(double[], int) = NULL);
    static void  destroyObject();
    
    static void SelectionSort(double[], int);
    static void InsertionSort(double[], int);
    static void InterchageSort(double[], int);

    void Sort(double[], int);
};


SortAlgorithm* SortAlgorithm::_algorithm =  nullptr;
SortAlgorithm::SortAlgorithm() {
    currentAlgorithm = InsertionSort;
}
void SortAlgorithm::destroyObject() {
    if (_algorithm != nullptr) {
        delete _algorithm;
        _algorithm = nullptr;
    }
}
SortAlgorithm* SortAlgorithm::getObject(void(*pAg)(double[], int)) {
    if (_algorithm == nullptr)
        _algorithm = new SortAlgorithm();
    if (pAg != nullptr)
        _algorithm->currentAlgorithm = pAg;
    return _algorithm;
}
void SortAlgorithm::Sort(double list[], int size) {
    if (currentAlgorithm !=  nullptr)
        currentAlgorithm(list, size);
}

void SortAlgorithm::SelectionSort(double list[], int size) {
    cout << "+ Using Selection Sort\n";

    int min;
    for (int i = 0; i < size - 1;++i) {
        min = i;
        int j = i+1;

        while (j < size) {min = list[min] <= list[j] ? min : j;++j;}
        swap(list[min], list[i]);
    }
}
void SortAlgorithm::InsertionSort(double list[], int size) {
    cout <<  "Using Insertion Sort\n";

    for (int i=  1; i  < size;++i) {
        int j = i - 1;
        double rep = list[i];
        
        while (j >= 0 && rep < list[j])
            {list[j + 1] = list[j]; --j;} 

        list[j + 1] = rep;
    }
}
void SortAlgorithm::InterchageSort(double list[], int size) {
    cout << "Using  InterChange Sort\n";

    for (int i = 0; i < size; ++i) {
        for (int j = 1; j < size; ++j)
            if (list[j - 1] > list[j])
                swap(list[j-1],list[j]);
    }
}

int main()  {
    int n = 5;
    double list[n]  = {5,4,10,2,1};
    SortAlgorithm* sort = SortAlgorithm::getObject(SortAlgorithm::InterchageSort);

    sort->Sort(list, n);

    cout << "+ Sorted List in Accending Order\n";
    for (int i = 0; i < n; ++i)
        cout  << list[i] << "   ";
}