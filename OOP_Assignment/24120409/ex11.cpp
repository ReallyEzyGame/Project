#include <stdio.h>

// the Merge function of the Merge sort
template <typename T>
void merge(T arr[], const size_t left, const size_t mid, const size_t right)
{
    // let l run through the first half, m run through the second half
    size_t l = left, m = mid + 1, idx = 0;

    T array[right - left + 1];
    // Merge the two array until one of them runs out
    while (l <= mid && m <= right)
        array[idx++] = (arr[l] < arr[m]) ? arr[l++] : arr[m++];

    // Put all the remaining to the array

    while (l <= mid)
        array[idx++] = arr[l++];
    while (m <= right)
        array[idx++] = arr[m++];

    // Put the result back to the orginal array
    for (size_t x = 0; x < idx; ++x)
        arr[left + x] = array[x];
}
// this function can sort any data type that has operator '<=' in the acsending order
template <typename T>
void acsendingSort(T arr[], const size_t begin, const size_t end)
{
    // we use the merge sort for gainning O(nlog(n)) complexiy while assuming the data size is relatively small( such as int, double, char,...)
    if (begin < end)
    {
        // Divide part
        size_t mid = begin + (end - begin) / 2;

        acsendingSort<T>(arr, begin, mid);
        acsendingSort<T>(arr, mid + 1, end);

        // Merge & Conquere
        merge<T>(arr, begin, mid, end);
    }
}

int main()
{
    // Sorting on Integer Array
    printf("- Sort integer array\n");
    int arr_i[5] = {10,5,9,6,100};

    printf("Before Sorting: ");
        for (int i = 0; i < 5; ++i)
        printf("%d\t", arr_i[i]);
    printf("\n");

    acsendingSort(arr_i, 0, 4);
    printf("Sorting Result: ");
    for (int i = 0; i < 5; ++i)
        printf("%d\t", arr_i[i]);


    printf("\n\n");


    // Sorting on Float Array
    printf("- Sort float array\n");
    float arr_f[5] = {11.5f,5.95f,10.6f,6.01f,20.3f};

    printf("Before Sorting: ");
        for (int i = 0; i < 5; ++i)
        printf("%.2f\t", arr_f[i]);
    printf("\n");

    acsendingSort(arr_f, 0, 4);
    
    printf("Sorting Result: ");
    for (int i = 0; i < 5; ++i)
        printf("%.2f\t", arr_f[i]);

    printf("\n\n");



    // Sorting on Char array
    // the order is base on the ASCII table rather than the Alphabet order
    printf("- Sort char array\n");
    char arr_c[5] = {'a','A','C','b','B'};

    printf("Before Sorting: ");
        for (int i = 0; i < 5; ++i)
        printf("%c\t", arr_c[i]);
    printf("\n");

    acsendingSort(arr_c, 0, 4);

    printf("Sorting Result: ");
    for (int i = 0; i < 5; ++i)
        printf("%c\t", arr_c[i]);

}