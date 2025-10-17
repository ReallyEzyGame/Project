#include <cstring>
#include <stdio.h>

#define DEFAULT_ID_LENGTH 7
#define DEFAULT_NAME_LENGTH 4

int abs(const int val)
{
    return val < 0 ? -val : val;
}

// class manage date
// it can handle leap year case, update the input to the correct date format
// for example: 32/12/2025 --- update() ---> 01/01/2025
class NgayThang
{
private:
    int day, month, year;
    // this function is still in develop
    void update();

public:
    NgayThang();
    NgayThang(const int, const int, const int);
    NgayThang(const NgayThang &);
    ~NgayThang() = default;

    // check if the current is a leap year or not
    bool leapYear() const;
    // get the number of day in current month
    int getNumberDayInMonth() const;
    NgayThang getDate() const;
    void Xuat() const;
};

NgayThang::NgayThang() : day(1), month(1), year(1) {}
NgayThang::NgayThang(const int d, const int m, const int y) : day(d), month(m), year(y) { update(); }
NgayThang::NgayThang(const NgayThang &other) : day(other.day), month(other.month), year(other.year) {}

bool NgayThang::leapYear() const { return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); }
int NgayThang::getNumberDayInMonth() const
{
    if (month == 2)
    {
        if (leapYear())
            return 29;
        return 28;
    }
    else
    {
        if (month % 2 == 0)
        {
            // even months before August have 30 days
            if (month < 8)
                return 30;
            // even months after August have 31 days
            else
                return 31;
        }
        else
        {
            // odd months before August have 31 days
            if (month < 8)
                return 31;
            // odd months after August have 30 days
            else
                return 30;
        }
    }
}
NgayThang NgayThang::getDate() const { return NgayThang(day, month, year); }

void NgayThang::Xuat() const
{
    printf("%02d/%02d/%02d", day, month, year);
}
void NgayThang::update()
{
    day = abs(day);
    month = abs(month);
    year = abs(year);

    while (true)
    {
        if (day > getNumberDayInMonth())
        {
            day -= getNumberDayInMonth();
            month += 1;

            continue;
        }
        if (month > 12)
        {
            month -= 12;
            year += 1;

            continue;
        }

        break;
    }
}

// Class Sinh Vien manages MSSV, HoTen, Date of Birth( DOB), point ( both theory & practice)
class SinhVien
{
private:
    char *MSSV, *HoTen;
    NgayThang NgaySinh;
    float DLT, DTH;

public:
    // Default Constructor
    SinhVien();
    // Construct by ID
    SinhVien(const char *);
    // Construct by ID, nam
    SinhVien(const char *, const char *);
    // Construct by ID, Name, point, DOB
    SinhVien(const char *, const char *, const float, const float);
    SinhVien(const char *, const char *, const float, const float, const int, const int, const int);
    SinhVien(const char *, const char *, const float, const float, const NgayThang);
    // Copy Constructor
    SinhVien(const SinhVien &);
    ~SinhVien();

    void Xuat();
};

SinhVien::SinhVien() : NgaySinh(), DLT(10), DTH(10)
{
    MSSV = new char[DEFAULT_ID_LENGTH + 1];
    HoTen = new char[DEFAULT_NAME_LENGTH + 1];

    for (int i = 0; i < DEFAULT_ID_LENGTH; ++i)
        MSSV[i] = 'x';
    for (int i = 0; i < DEFAULT_NAME_LENGTH; ++i)
        HoTen[i] = 'X';

    MSSV[DEFAULT_ID_LENGTH] = '\0';
    HoTen[DEFAULT_NAME_LENGTH] = '\0';
}
SinhVien::SinhVien(const char *ID) : NgaySinh(), DLT(10), DTH(10)
{
    int len = strlen(ID);

    MSSV = new char[len + 1];
    HoTen = new char[DEFAULT_NAME_LENGTH + 1];

    for (int i = 0; i < len; ++i)
        MSSV[i] = ID[i];
    for (int i = 0; i < DEFAULT_NAME_LENGTH; ++i)
        HoTen[i] = 'X';

    MSSV[len] = '\0';
    HoTen[DEFAULT_NAME_LENGTH] = '\0';
}
SinhVien::SinhVien(const char *ID, const char *name) : NgaySinh(), DLT(10), DTH(10)
{
    int len1 = strlen(ID);
    int len2 = strlen(name);

    MSSV = new char[len1 + 1];
    HoTen = new char[len2 + 1];

    for (int i = 0; i < len1; ++i)
        MSSV[i] = ID[i];
    for (int i = 0; i < len2; ++i)
        HoTen[i] = name[i];
    
    // avoid printf() read the garabge data
    MSSV[len1] = '\0';
    HoTen[len2] = '\0';
}
SinhVien::SinhVien(const char *ID, const char *name, const float LT, const float TH) : NgaySinh()
{
    int len1 = strlen(ID);
    int len2 = strlen(name);

    MSSV = new char[len1 + 1];
    HoTen = new char[len2 + 1];

    for (int i = 0; i < len1; ++i)
        MSSV[i] = ID[i];
    for (int i = 0; i < len2; ++i)
        HoTen[i] = name[i];
    // avoid printf() read the garabge data
    MSSV[len1] = '\0';
    HoTen[len2] = '\0';

    // Clamp
    DLT = LT >= 0 ? LT : 0;
    DTH = TH >= 0 ? TH : 0;
}
SinhVien::SinhVien(const char *ID, const char *name, const float LT, const float TH, const int d, const int m, const int y) : NgaySinh(d, m, y)
{
    int len1 = strlen(ID);
    int len2 = strlen(name);

    MSSV = new char[len1 + 1];
    HoTen = new char[len2 + 1];

    for (int i = 0; i < len1; ++i)
        MSSV[i] = ID[i];
    for (int i = 0; i < len2; ++i)
        HoTen[i] = name[i];

    // avoid printf() read the garabge data
    MSSV[len1] = '\0';
    HoTen[len2] = '\0';

    // Clamp
    DLT = LT >= 0 ? LT : 0;
    DTH = TH >= 0 ? TH : 0;
}
SinhVien::SinhVien(const char *ID, const char *name, const float LT, const float TH, const NgayThang DOB) : NgaySinh(DOB)
{
    int len1 = strlen(ID);
    int len2 = strlen(name);

    MSSV = new char[len1 + 1];
    HoTen = new char[len2 + 1];

    for (int i = 0; i < len1; ++i)
        MSSV[i] = ID[i];
    for (int i = 0; i < len2; ++i)
        HoTen[i] = name[i];

    // avoid printf() read the garabge data
    MSSV[len1] = '\0';
    HoTen[len2] = '\0';
    // Clamp
    DLT = LT >= 0 ? LT : 0;
    DTH = TH >= 0 ? TH : 0;
}
SinhVien::SinhVien(const SinhVien &other) : NgaySinh(other.NgaySinh)
{
    int len1 = strlen(other.MSSV);
    int len2 = strlen(other.HoTen);

    MSSV = new char[len1 + 1];
    HoTen = new char[len2 + 1];

    for (int i = 0; i < len1; ++i)
        MSSV[i] = other.MSSV[i];
    for (int i = 0; i < len2; ++i)
        HoTen[i] = other.HoTen[i];

    // avoid printf() read the garabge data
    MSSV[len1] = '\0';
    HoTen[len2] = '\0';
    // Clamp
    DLT = other.DLT >= 0 ? other.DLT : 0;
    DTH = other.DTH >= 0 ? other.DTH : 0;
}
SinhVien::~SinhVien()
{
    if (MSSV)
        delete MSSV;
    if (HoTen)
        delete HoTen;
}

void SinhVien::Xuat()
{
    printf("MSSV: %s, HoTen: %s, NgaySinh: ", MSSV, HoTen);
    NgaySinh.Xuat();
    printf(", DLT: %.2f, DTH %.2f.", DLT, DTH);
}

int main()
{
    NgayThang n(30, 2, 1996);

    SinhVien sv1, sv2("1363001"), sv3("1363002", "Nguyen Van A", 7, 8.5), sv4("1363003", "Tran Thi B", 8, 9.5, 12, 3, 1996), sv5("1363004", "Ngo Van C", 5, 6, n), sv6(sv5);

    sv1.Xuat();
    printf("\n");
    sv2.Xuat();
    printf("\n");
    sv3.Xuat();
    printf("\n");
    sv4.Xuat();
    printf("\n");
    sv5.Xuat();
    printf("\n");
    sv6.Xuat();
}