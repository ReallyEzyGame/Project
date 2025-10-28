#include <stdio.h>

class MangSoNguyen
{
private:
    int *data;
    int size; // capacity shows the number of candidate in the array while size is the truly size that is allocate in the memory

public:
    MangSoNguyen();
    MangSoNguyen(const int);
    MangSoNguyen(const int *, const int);
    MangSoNguyen(const MangSoNguyen &);
    ~MangSoNguyen();

    void Xuat() const;
};

MangSoNguyen::MangSoNguyen() : data(nullptr), size(0) {}
MangSoNguyen::MangSoNguyen(const int s)
{
    if (s <= 0)
    {
        size = 0;
        data = nullptr;
    }
    else
    {
        size = s;
        data = new int[size + 1];
        for (int i = 0; i < size; ++i)
            data[i] = 0;
    }
}
MangSoNguyen::MangSoNguyen(const int *arr, const int n)
{
    if (n <= 0 || arr == nullptr)
    {
        size = 0;
        data = nullptr;
    }
    else
    {
        size = n;
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = arr[i];
    }
}
MangSoNguyen::MangSoNguyen(const MangSoNguyen &other)
{
    // Avoid pointer points to  itself
    if (this == &other) {
        size = 0;
        data = nullptr;
    }
    size = other.size;
    data = new int[size];

    for (int i = 0; i < size; ++i)
        data[i] = other.data[i];
}
MangSoNguyen::~MangSoNguyen()
{
    if (data)
        delete data;
}

void MangSoNguyen::Xuat() const {
    if (!data) {
        printf("Empty");
    }
    else {
        for (int i = 0 ; i < size; ++i)
            printf("%d ", data[i]);
    }
}


int main() {
    MangSoNguyen msn1, msn2(5);

    int arr_i[10];
    for (int i = 0; i < 10; ++i)
        arr_i[i] = i * i;

    MangSoNguyen msn3(arr_i, 10), msn4(msn3);


    msn1.Xuat();
    printf("\n");
    msn2.Xuat();
    printf("\n");
    msn3.Xuat();
    printf("\n");
    msn4.Xuat();
    printf("\n");
}