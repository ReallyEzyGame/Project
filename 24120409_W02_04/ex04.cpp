#include <iostream>
#include <cstring>
#include <math.h>

int abs(const int val)
{
    return val >= 0 ? val : -val;
}
int max(const int val1, const int val2)
{
    return val1 > val2 ? val1 : val2;
}
// lop so nguy lon bieu dien cac so nguyen co kich thuoc ma cac kieu du lieu co san khong  the luu tru duoc
// luu y: thu tu cac chu so trong truong SoLon khong duoc luu theo chieu thuan( logic trong toan hoc) ma duoc luu nguoc lai nham de thuc hien cac phep toan cung nhu so sanh
class SoNguyenLon
{
private:
    static SoNguyenLon SNLmax;
    void CapNhat(); // Cap nhat lai so lon nhat sau moi lan doi
private:
    char *SoLon;

public:
    SoNguyenLon();
    SoNguyenLon(const int);
    // Tao ra 1 chuoi gia tri 'val' co do dai 'n'
    SoNguyenLon(int val, const int n);
    //
    SoNguyenLon(const char *);
    SoNguyenLon(const SoNguyenLon &);

    ~SoNguyenLon();

    void In(std::ostream &os);

    SoNguyenLon Cong(const SoNguyenLon &);
    SoNguyenLon Tru(const SoNguyenLon &);
    // tra ve -1 neu so thu nhat nho hon so thu 2, 0 neu hai so bang nhau va 1 neu so thu hai nho hon so thu nhat
    static int SoSanh(const SoNguyenLon &, const SoNguyenLon &);
    static SoNguyenLon SNLMax();
    static SoNguyenLon HieuVoiHangSo(const int, const SoNguyenLon);
};

SoNguyenLon SoNguyenLon::SNLmax(0, 1);

SoNguyenLon::SoNguyenLon()
{
    SoLon = new char[2];
    SoLon[0] = '0';
    SoLon[1] = '\0';

    CapNhat();
}
SoNguyenLon::SoNguyenLon(int val)
{
    if (val == 0)
    {
        SoLon = new char[2];
        SoLon[0] = '0';
        SoLon[1] = '\0';
    }
    else
    {
        int idx = 0, len = log10(val) + 1;
        SoLon = new char[len + 1];

        while (idx < len)
        {
            SoLon[idx++] = val % 10 + '0';
            val /= 10;
        }
        SoLon[len] = '\0';
    }

    CapNhat();
}
SoNguyenLon::SoNguyenLon(int val, const int n)
{
    if (val <= 0 || n <= 0)
    {
        SoLon = new char[2];
        SoLon[0] = '0';
        SoLon[1] = '\0';
    }
    else
    {
        int j = 0, tmp = val;         // j la chi so cua mang so lon, tmp la gia tri luu tam
        int val_len = log10(val) + 1; // chieu dai cua 'val'
        SoLon = new char[val_len * n + 1];

        // chuyen 'val' vao mang n lan
        for (int i = 0; i < n; ++i)
        {
            int idx = 0;
            val = tmp;

            // chuyen 'val' vao mang
            while (idx < val_len)
            {
                SoLon[j] = val % 10 + '0';
                val /= 10;
                idx++;
                j++;
            }
        }
        SoLon[val_len * n] = '\0';
    }

    CapNhat();
}
SoNguyenLon::SoNguyenLon(const char *str)
{
    if (str == nullptr)
    {
        SoLon = new char[2];
        SoLon[0] = '0';
        SoLon[1] = '\0';
    }
    else
    {
        int len = strlen(str);
        SoLon = new char[len + 1];

        for (int i = len - 1; i >= 0; --i)
            SoLon[i] = str[len - i - 1];
        SoLon[len] = '\0';
    }

    CapNhat();
}
SoNguyenLon::SoNguyenLon(const SoNguyenLon &other)
{
    // tranh truong hop khoi tao bang cach copy chinh no
    if (this == &other)
    {
        SoLon = new char[2];
        SoLon[0] = '0';
        SoLon[1] = '\0';
    }
    else
    {
        int len = strlen(other.SoLon);
        SoLon = new char[len + 1];

        for (int i = 0; i < len; ++i)
            SoLon[i] = other.SoLon[i];
        SoLon[len] = '\0';
    }

    CapNhat();
}
SoNguyenLon::~SoNguyenLon()
{
    delete[] SoLon;
}

void SoNguyenLon::In(std::ostream &os)
{
    int len = strlen(SoLon);
    // tran ky hieu '\0' terminate
    for (int i = len - 1; i >= 0; i--)
    {
        os << SoLon[i];
    }
}
void SoNguyenLon::CapNhat()
{
    if (SoSanh(*this, SNLmax) == 1)
    {
        delete[] SNLmax.SoLon;
        int len =  strlen(SoLon);
        SNLmax.SoLon = new char[len + 1];
        for (int i = 0; i <  len; ++i)
            SNLmax.SoLon[i] = SoLon[i];

        SNLmax.SoLon[len] = '\0';

    }
}
SoNguyenLon SoNguyenLon::Cong(const SoNguyenLon &other)
{
    bool carry = false;
    int i = 0;
    int m = strlen(SoLon), n = strlen(other.SoLon);
    // tao gia tri moi chua max(m,n) gom 2 ky tu '\0' o phia duoi
    SoNguyenLon sum(0, max(m, n) + 1);
    // Chung ta chi duyet den truoc ky tu '\0'
    while (i < m && i < n)
    {
        int tmp = (SoLon[i] - '0') + (other.SoLon[i] - '0') + carry;
        carry = false;

        if (tmp >= 10)
        {
            carry = true;
            tmp = tmp % 10;
        }
        sum.SoLon[i] = tmp + '0';
        i++;
    }

    // tra phan con du neu con vao ket qua
    while (i < m)
    {
        int tmp = (SoLon[i] - '0') + carry;
        carry = false;

        if (tmp >= 10)
        {
            carry = true;
            tmp = tmp % 10;
        }
        sum.SoLon[i] = tmp + '0';
        i++;
    }
    while (i < n)
    {
        int tmp = (other.SoLon[i] - '0') + carry;
        carry = false;

        if (tmp >= 10)
        {
            carry = true;
            tmp = tmp % 10;
        }
        sum.SoLon[i] = tmp + '0';
        i++;
    }

    // van con gia tri => chen vao vi tri du phong
    if (carry)
    {
        sum.SoLon[max(m, n)] = '1';
    }
    else
    {
        sum.SoLon[max(m, n)] = '\0';
    }

    CapNhat();
    return sum;
}
SoNguyenLon SoNguyenLon::Tru(const SoNguyenLon &other)
{
    bool carry = false;
    // m > n
    int m = strlen(SoLon), n = strlen(other.SoLon);
    int i = 0, compare = SoSanh(*this, other);

    char *greater = this->SoLon;
    char *smaller = other.SoLon;
    // tao gia tri moi co do dai max(n,m)
    SoNguyenLon sum(1, max(m, n));

    if (compare == -1)
    {
        greater = other.SoLon;
        smaller = this->SoLon;

        std::swap(m, n);
    }
    // Chung ta chi duyet den truoc ky tu '\0'
    while (i < m && i < n)
    {
        int tmp = greater[i] - smaller[i] - carry;
        carry = false;

        if (tmp < 0)
        {
            carry = true;
            tmp = 10 + tmp;
        }
        sum.SoLon[i] = tmp + '0';
        i++;
    }

    // tra phan con du neu con vao ket qua
    // chuyen phan con lai cua so bi tru
    while (i < m)
    {
        int tmp = SoLon[i] - '0' - carry;
        carry = false;

        if (tmp < 0)
        {
            carry = true;
            tmp = 10 + tmp;
        }
        sum.SoLon[i] = tmp + '0';
        i++;
    }

    return sum;
}
int SoNguyenLon::SoSanh(const SoNguyenLon &num1, const SoNguyenLon &num2)
{
    // bo qua ky tu '\0'
    int m = strlen(num1.SoLon) - 1, n = strlen(num2.SoLon) - 1;
    while (num1.SoLon[m] == '\0')
        m--;
    while (num2.SoLon[n] == '\0')
        n--;

    if (m < n)
        return -1;
    else if (m > n)
        return 1;

    for (int i = m - 1; i >= 0; --i)
    {
        if (num1.SoLon[i] < num2.SoLon[i])
            return -1;
        if (num1.SoLon[i] > num2.SoLon[i])
            return 1;
    }
    return 0;
}
SoNguyenLon SoNguyenLon::SNLMax()
{
    return SNLmax;
}
SoNguyenLon SoNguyenLon::HieuVoiHangSo(const int number, const SoNguyenLon other)
{
    return SoNguyenLon(number).Tru(other);
}

int main()
{
    SoNguyenLon snl1,
        snl2("1234567"),
        snl3(3, 14), snl4(9, 20),
        snl5 = snl3.Tru(snl2),
        snl6 = SoNguyenLon::HieuVoiHangSo(45678910, snl2),
        snl7 = snl4.Tru(snl3).Cong(123456789);

    snl1.In(std::cout);
    std::cout << std::endl;
    snl2.In(std::cout);
    std::cout << std::endl;
    snl3.In(std::cout);
    std::cout << std::endl;
    snl4.In(std::cout);
    std::cout << std::endl;
    snl5.In(std::cout);
    std::cout << std::endl;
    snl6.In(std::cout);
    std::cout << std::endl;
    snl7.In(std::cout);
    std::cout << std::endl;

    std::cout << "So Nguyen Lon Max: " << std::endl;
    SoNguyenLon::SNLMax().In(std::cout);
    std::cout << std::endl;
    system("pause");
}