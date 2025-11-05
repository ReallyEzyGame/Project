#include <iostream>
#include <cstring>
#include <exception>

class CString
{
private:
    char *_mang;

public:
    CString();
    CString(const char *);
    ~CString();

    char &operator[](const int &);
    friend std::ostream &operator<<(std::ostream &, const CString &);
};

CString::CString()
{
    _mang = nullptr;
}
CString::CString(const char *str)
{
    int len = strlen(str);
    _mang = new char[len + 1];

    strcpy_s(_mang, len + 1, str);
}
CString::~CString()
{
    if (_mang)
        delete _mang;
}

char &CString::operator[](const int &i)
{
    int len = strlen(_mang);
    if (i < 0 || i >= len)
    {
        throw std::exception("out of range");
    }
    return _mang[i];
}
std::ostream &operator<<(std::ostream &os, const CString &cs)
{
    os << cs._mang;
    return os;
}

int main()
{
    const int iN = 2;
    CString cs1("cs1_content");

    std::cout << cs1 << std::endl;
    std::cout << "cs1[" << iN << "] = " << cs1[iN] << std::endl;
    cs1[iN] = 'N';
    std::cout << cs1 << std::endl;

    system("pause");
    return 0;
}