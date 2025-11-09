#include <iostream>
#include <cstring>

class CString
{
private:
    char *_mang;

public:
    CString();
    CString(const char *);
    CString(const CString &);
    ~CString();

    char &operator[](const int &);
    CString &operator=(const CString &);
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
CString::CString(const CString &cstr) : CString(cstr._mang)
{
    std::cout << "The Constructor was called\n";
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
        throw std::exception("Out of Range");
    }
    return _mang[i];
}
CString &CString::operator=(const CString &cs)
{
    std::cout << "The operator= was called\n";
    if (_mang != nullptr)
    {
        delete[] _mang;
    }
    int len = strlen(cs._mang) + 1;
    _mang = new char[len];
    strcpy_s(_mang, len, cs._mang);

    return *this;
}
std::ostream &operator<<(std::ostream &os, const CString &cs)
{
    os << cs._mang;
    return os;
}

int main(void)
{
    const int iN = 2;
    CString cs1("cs1_content");
    CString cs2(cs1);
    
    
    std::cout << "cs2(cs1)" << std::endl;
    cs2[iN] = '2';

    std::cout << "cs3 = cs1" << std::endl;
    CString cs3 = cs1;
    cs3[iN] = '3';

    std::cout << cs1 << std::endl
              << cs2 << std::endl
              << cs3 << std::endl;

    std::cout << "cs3 = cs2" << std::endl;
    cs3 = cs2;

    std::cout << cs3 << std::endl;
    system("pause");

    return 0;
}