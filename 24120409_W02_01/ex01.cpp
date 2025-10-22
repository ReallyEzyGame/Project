#include <iostream>

class SoPhuc
{
private:
    static int ssl;
    int thuc, ao;
    int sl;

public:
    SoPhuc();
    SoPhuc(const int &th, const int &ao);
    SoPhuc(const SoPhuc &sp);
    ~SoPhuc();

    SoPhuc Cong(const SoPhuc &);
    int SoLuongSP();
    static int SSoLuongSP();
};

int SoPhuc::ssl = 1;

SoPhuc::SoPhuc()
{
    thuc = ao = 0;
    sl++;
    ssl++;
}
SoPhuc::SoPhuc(const int &th, const int &a)
{
    thuc = th;
    ao = a;
    sl++;
    ssl++;
}
SoPhuc::SoPhuc(const SoPhuc &sp)
{
    thuc = sp.thuc;
    ao = sp.ao;
    sl++;
    ssl++;
}
SoPhuc::~SoPhuc()
{
    sl--;
    ssl--;
}

SoPhuc SoPhuc::Cong(const SoPhuc &sp)
{
    SoPhuc kq(*this);
    kq.thuc += sp.thuc;
    kq.ao += sp.ao;

    return kq;
}
int SoPhuc::SoLuongSP()
{
    return sl;
}
int SoPhuc::SSoLuongSP()
{
    return ssl;
}

int main()
{
    SoPhuc sp1, sp2(5, 10), sp3(sp1), sp4 = sp2.Cong(sp1);

    std::cout << SoPhuc::SSoLuongSP() << std::endl;
    {
        SoPhuc sp5, sp6 = sp2.Cong(sp1);
    }
    std::cout << sp4.SoLuongSP() << std::endl;
    std::cout << SoPhuc::SSoLuongSP() << std::endl;

    system("pause");
}