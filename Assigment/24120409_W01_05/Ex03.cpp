#include <stdio.h>



class ThoiGian {
private:
    int gio, phut, giay;
    // cap  nhat lai thoi gian va dam bao thoi gian van nam trong don vi quy dinh
    // VD: 360(s) --> 6(m)
    void capNhat();
public:
    ThoiGian();
    ThoiGian(const int);
    ThoiGian(const int, const int);
    ThoiGian(const int,const int, const int);
    ThoiGian(const ThoiGian&);

    //  Xuat ra tren thiet bi chuan( man hinh)
    void Xuat() const;
};

ThoiGian::ThoiGian() : giay(0), phut(0), gio(0) {}
ThoiGian::ThoiGian(const int sec) : phut(0), gio(0) { giay = sec > 0 ? sec : 0; capNhat();}
ThoiGian::ThoiGian(const int min, const int sec) : gio(0) {
    giay = sec > 0 ? sec : 0;
    phut = min > 0 ? min : 0;

    capNhat();
}
ThoiGian::ThoiGian(const int hou, const int min, const int sec) { 
    giay = sec > 0 ? sec : 0;
    phut = min > 0 ? min : 0;
    gio  = hou > 0 ? hou : 0;

    capNhat();
}
ThoiGian::ThoiGian(const ThoiGian& other) : giay(other.giay), phut(other.phut), gio(other.gio) {}


void ThoiGian::Xuat() const {
    printf("%02d:%02d:%02d\n", gio, phut, giay);
}


void ThoiGian::capNhat() {
    int phutDu = giay / 60;
    giay = giay % 60;
    phut += phutDu;

    int gioDu = phut / 60;
    phut = phut % 60;
    gio += gioDu;
}



int main() {
    ThoiGian t1, t2(1212), t3(125, 45), t4(12, 239, -78);

    t1.Xuat();
    t2.Xuat();
    t3.Xuat();
    t4.Xuat();

    return 0;
}