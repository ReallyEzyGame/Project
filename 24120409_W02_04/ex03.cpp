#include <iostream>
#include <string.h>


float abs(const float a) {
    return a > 0 ? a : - a;
}

class HocSinh{
    static HocSinh HSTBCaoNhat;
    static int ID;
private:
    char* ten;
    int MSSV;
    float toan, ly, hoa;      // Diem cua cac mon

    float TinhTrungBinhMon();
public:
    
    HocSinh();
    HocSinh(const HocSinh&) = delete;       // Cac HocSinh khong duoc khai bao copy nhau
    HocSinh(const char*, const float, const float, const float);
    ~HocSinh();

    bool DatHoTen(const char*);
    void GanDiem(const float, const float, const float);


    void In(std::ostream &os);
    static HocSinh& HSDiemTBCaoNhat();
};

int HocSinh::ID = 23119999;
HocSinh HocSinh::HSTBCaoNhat = {" ",0,0,0};
HocSinh::HocSinh() {
    ten = nullptr;
    toan = ly = hoa = 0.f;
    MSSV = ++ID;
}
HocSinh::HocSinh(const char* t_, const float to_, const float ly_, const float ho_) {
    if (t_ == nullptr) {
        std::cout  << "Khai bao khong hop le\n";

        return;
    }
    else {
        int len = strlen(t_);
        ten = new char[len + 1];
        for (int i = 0; i < len; ++i)
            ten[i] = t_[i];
        ten[len] = '\0';
    }

    toan = abs(to_);
    ly = abs(ly_);
    hoa = abs(ho_);
    MSSV = ++ID;

    if (HSTBCaoNhat.TinhTrungBinhMon() < this->TinhTrungBinhMon()) {
        HSTBCaoNhat.ten = this->ten;
        HSTBCaoNhat.MSSV = this->MSSV;
        HSTBCaoNhat.toan = this->toan;
        HSTBCaoNhat.ly = this->ly;
        HSTBCaoNhat.hoa = this->hoa;
    }
}
HocSinh::~HocSinh() {
    if (ten)
        delete[] ten;
}


bool HocSinh::DatHoTen(const char* t_) {
    if (t_  == nullptr) {
        std::cout << "Loi: Ten Khong Xac Dinh\n";
        return false;
    }
    else {
        //  Xoa ten da co
        if (ten != nullptr)
            delete[] ten;

        int len = strlen(t_);
        ten = new char[len + 1];

        for (int i = 0; i < len; ++i)
            ten[i] = t_[i];
        ten[len] = '\0';
    }
    return true;
}
void HocSinh::GanDiem(const float to_, const float ly_, const float ho_) {
    toan = abs(to_);
    ly = abs(ly_);
    hoa = abs(ho_);

    if (HSTBCaoNhat.TinhTrungBinhMon() < this->TinhTrungBinhMon()) {
        HSTBCaoNhat.ten = this->ten;
        HSTBCaoNhat.MSSV = this->MSSV;
        HSTBCaoNhat.toan = this->toan;
        HSTBCaoNhat.ly = this->ly;
        HSTBCaoNhat.hoa = this->hoa;
    }
}


void HocSinh::In(std::ostream& os) {
    if (!ten) {
        os << "HS: Rong";
    }
    else {
        os << "HS: " << ten;
    }
    os << ", MSSV: " << MSSV << ", DTB: " << TinhTrungBinhMon();
}
float HocSinh::TinhTrungBinhMon() {
    return (toan + ly + hoa )/ 3.0;
}
HocSinh& HocSinh::HSDiemTBCaoNhat() {
    return HSTBCaoNhat;
}


int main() {
    HocSinh hs1, hs2("Tran Thi B", 5, 8, 4.5), 
    hs3("Hoang Thi C", -9.5, 8.5, 4.5),
    hs4("Le Van D", 7.5, 9, -10);

    hs1.DatHoTen("Nguyen Van A");
    hs1.GanDiem(7.5, 9, -10);

    hs1.In(std::cout);
    std::cout << std:: endl;
    hs2.In(std::cout);
    std::cout << std:: endl;
    hs3.In(std::cout);
    std::cout << std:: endl;

    std::cout <<  "Hoc Sinh co diem trung binh cao nhat: "; 
    HocSinh::HSDiemTBCaoNhat().In(std::cout);
    std::cout << std::endl;

    system("pause");
    return 0;
}