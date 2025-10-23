#include <iostream>

class Ngay
{
private:
    int ng_, th_, n_;
    static int arr_ngay_cua_thang[][13];
    static bool laNamNhuan(const int &);

public:
    Ngay();
    Ngay(const int &);
    ~Ngay();

    void Xuat(std::ostream &os);
};

Ngay::Ngay()
{
    ng_ = th_ = n_ = 1;
}
Ngay::Ngay(const int &n)
{
    ng_ = n > 0 ? n : -n;
    th_ = n_ = 1;
    if (ng_ == 0)
    {
        ng_ = 1;
    }
    else
    {
        int idx = laNamNhuan(n_);
        while (ng_ > arr_ngay_cua_thang[idx][th_])
        {
            ng_ -= arr_ngay_cua_thang[idx][th_];
            ++th_;

            if (th_ > 12)
            {
                th_ = 1;
                n_++;
                idx = laNamNhuan(n_);
            }
        }
    }
}
Ngay::~Ngay() = default;

bool Ngay::laNamNhuan(const int &year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
void Ngay::Xuat(std::ostream &os)
{
    os << ng_ << "-" << th_ << "-" << n_;
}

int Ngay::arr_ngay_cua_thang[][13] = {{-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {-1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int main()
{
    Ngay n1, n2(1000), n3(2000), n4(3000), n5(5000);

    n1.Xuat(std::cout);
    std::cout << std::endl;
    n2.Xuat(std::cout);
    std::cout << std::endl;
    n3.Xuat(std::cout);
    std::cout << std::endl;
    n4.Xuat(std::cout);
    std::cout << std::endl;
    n5.Xuat(std::cout);
    std::cout << std::endl;

    system("pause");
}