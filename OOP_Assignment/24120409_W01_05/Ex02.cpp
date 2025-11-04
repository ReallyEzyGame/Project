#include <cstring>
#include <stdio.h>


bool isDigit(const char ch) {
    return '0' <= ch && ch <= '9';
}
int abs(const int val) {
    return val < 0 ? - val : val;
}
int atoi(char* str) {
    if (str == nullptr || strlen(str) == 0)
        return 0;

    bool negative = false;
    int size = strlen(str);
    int result = 0, idx = 0;

    if (str[idx] == '-') {
        negative = true;
        idx++;
    }
    for (; idx < size; ++idx)
    {
        if (!isDigit(str[idx]))
        {
            printf("Error: Unexpected Token '%c'\n", str[idx]);
            return -1;
        }

        result = result * 10 + (str[idx] - '0');
    }


    if (negative)
        result = -result;
    return result;
}




// We use the main language is VietNamese from here
// gia su don gian rang moi thang chi co 30 ngay, 1 nam co 365 ngay( khong co nam nhuan)
class Ngay {
private:
    int ngay, thang, nam;
    void chuanHoa();
public:
    Ngay();
    Ngay(const int&);
    Ngay(const int, const int, const int);
    Ngay(const char*);
    Ngay(const Ngay&);
    ~Ngay() = default;

    void Xuat() const;
};

Ngay::Ngay() : ngay(1), thang(1), nam(1) {}
Ngay::Ngay(const int& so_ngay) : ngay(so_ngay), thang(1), nam(1) { chuanHoa();}
Ngay::Ngay(const int ng, const int th, const int na) : ngay(ng), thang(th), nam(na) {chuanHoa();}
Ngay::Ngay(const Ngay& other) : ngay(other.ngay), thang(other.thang), nam(other.nam) {}
Ngay::Ngay(const char* date_str) {
    size_t len = strlen(date_str);
    char* tempArr = new char[len + 1];
    char* tmp, *curStr;
    const char* delimeters = "-/";

    strcpy_s(tempArr, len + 1, date_str);

    // Chuyen chuoi ky tu chua lich sang ngay, thang nam
    curStr = strtok_s(tempArr, delimeters, &tmp);
    ngay = atoi(curStr);
    if (curStr) {
        curStr = strtok_s(nullptr, delimeters, &tmp);
        thang = atoi(curStr);
    }
    if (curStr) {
        curStr = strtok_s(nullptr, delimeters, &tmp);
        nam = atoi(curStr);
    }
    
    delete tempArr;
    chuanHoa();
}


void Ngay::chuanHoa() {
    ngay = abs(ngay);
    thang = abs(thang);
    nam = abs(nam);


    int thangDu = (ngay - 1) / 30;
    ngay = (ngay - 1) % 30 + 1;
    thang += thangDu;

    int namDu = (thang - 1) / 12;
    thang = (thang - 1) % 12 + 1;
    nam += namDu;
}


void Ngay::Xuat() const {
    printf("%d/%d/%d\n", ngay, thang, nam);
}

int main() {
    Ngay n1, n2(2,10,2024), n3(-100,16,1990), n4(1403), n5("12-12-2012");

    n1.Xuat();
    n2.Xuat();
    n3.Xuat();
    n4.Xuat();
    n5.Xuat();

    return 0;
}