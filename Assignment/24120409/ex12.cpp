#include <stdio.h>


// Update in Source code:
// By using compare function pointer, we  reduce the source code instead of having 2 seperate function we only need one sort function with smaller than or greater than compare mode to handle the job

using compare = bool(*) (int,int);

bool smallerThan(int val1,int val2) {
    return val1 < val2;
}
bool greaterThan(int val1, int val2) {
    return val1 > val2;
}

void  merge(int arr[], const  size_t left, const size_t mid, const size_t right, compare comp) {
    size_t l = left, m = mid +1, idx = 0;
    
    int temp_arr[right - left + 1];
    // Merging the  array in the given order
    while (l <= mid && m <= right) {
        temp_arr[idx++] = comp(arr[l], arr[m]) ? arr[l++] : arr[m++];
    }
    // Put all the remaining left to the temp arr
    while (l <= mid)
        temp_arr[idx++] = arr[l++];
    while (m <= right)
        temp_arr[idx++] = arr[m++];


    for (size_t x =  0; x < idx; ++x)
        arr[x + left] =  temp_arr[x];
    
} 


// Merge sort  an array of integer
// compare mode  smaller than ==> Ascending sort order
//  greater than ==> Descending Sort  order
void mergeSort(int arr[], const size_t begin, const size_t end, compare mode) {
    if ( begin <  end) {
        size_t mid = begin + (end - begin) / 2;

        mergeSort(arr, begin, mid, mode);
        mergeSort(arr, mid + 1, end, mode);

        merge(arr, begin, mid, end, mode);
    }
}



int main()
{
    int arr_i[10] = {100,83, 23,44,55,29,12,78,69,10};


    printf("- Sort integer array in Ascending order\n");
    printf("Before Sorting: ");
    for (int i = 0; i < 10; ++i)
        printf("%d\t", arr_i[i]);
    printf("\n");

    mergeSort(arr_i, 0, 9, smallerThan);

    printf("Sorting Result: ");
    for (int i = 0;  i < 10; ++i)
        printf("%d\t", arr_i[i]);
    


    printf("\n\n");



    printf("- Sort integer array in Descending order\n");
    printf("Before Sorting: ");
    for (int i = 0; i < 10; ++i)
        printf("%d\t", arr_i[i]);
    printf("\n");

    mergeSort(arr_i, 0, 9, greaterThan);

    printf("Sorting Result: ");
    for (int i = 0;  i < 10; ++i)
        printf("%d\t", arr_i[i]);
}