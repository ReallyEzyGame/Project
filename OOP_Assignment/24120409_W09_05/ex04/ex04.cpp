#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ChiTietMay {
private:
    string _ten;
public:
    ChiTietMay(const string ten) {
        _ten = ten;
    }
    virtual ~ChiTietMay() {}

    virtual int TrongLuong() const = 0;
    virtual int GiaThanh() const = 0;
    void Xuat(ostream& os, int do_sau = 0) const {
        for (int i = 0; i < do_sau; ++i) {
            os << "   ";
        }

        os << "[" << _ten << "] " << "<" << TrongLuong() << "> " << "(" << GiaThanh() << ")";
    }

    friend ostream& operator<<(ostream& os, const ChiTietMay& chi_tiet) {
        chi_tiet.Xuat(os);
        return os;
    }
};

class ChiTietDon : public ChiTietMay {
private:
    int _trong_luong;
    int _gia_thanh;
public:
    ChiTietDon(const string ten, const int tr, const int gi) : ChiTietMay(ten) {
        _trong_luong = std::abs(tr);
        _gia_thanh = std::abs(gi);
    }
    ~ChiTietDon() {}

    int TrongLuong() const final {
        return _trong_luong;
    }
    int GiaThanh() const final {
        return _gia_thanh;
    }
};

class ChiTietPhuc : public ChiTietMay {
private:
    vector<ChiTietMay*> _chi_tiet_con;
    float _trong_luong_them;
    float _gia_tang_them;
public:
    ChiTietPhuc(const string ten) : ChiTietMay(ten) {
        _trong_luong_them = 0.1f;
        _gia_tang_them = 0.2f;
    }
    ~ChiTietPhuc() {
        for (int i = 0; i < _chi_tiet_con.size(); ++i) {
            delete _chi_tiet_con[i];
        }
    }


    int TrongLuong() const final {
        int tong = 0;

        for (int i = 0; i < _chi_tiet_con.size(); ++i) {
            tong += _chi_tiet_con[i]->TrongLuong();
        }

        return (1.0 + _trong_luong_them) * tong;
    }
    int GiaThanh() const final {
        int tong = 0;

        for (int i = 0; i < _chi_tiet_con.size(); ++i) {
            tong += _chi_tiet_con[i]->GiaThanh();
        }

        return (1.0 + _gia_tang_them) * tong;
    }

    void ThemChiTiet(ChiTietMay* chi_tiet) {
        _chi_tiet_con.push_back(chi_tiet);
    }
};


class CoMay {
private:
    vector<ChiTietMay*> _chi_tiet;
public:
    CoMay() {}
    ~CoMay() {}

    int GiaThanh() const {
        int tong = 0;

        for (int i = 0; i < _chi_tiet.size(); ++i) {
            tong += _chi_tiet[i]->GiaThanh();
        }

        return tong;
    }
    int TrongLuong() const{
        int tong = 0;

        for (int i = 0; i < _chi_tiet.size(); ++i) {
            tong += _chi_tiet[i]->TrongLuong();
        }

        return tong;
    }

    void ThemChiTietMay(ChiTietMay* chi_tiet) {
        _chi_tiet.push_back(chi_tiet);
    }


    void Xuat(ostream& os) const {
        os << "[Co May]" << endl;
        for (int i = 0; i < _chi_tiet.size(); ++i) {
            _chi_tiet[i]->Xuat(os);
            os << endl;
        }
    }

    friend ostream& operator<< (ostream& os, const CoMay& may) {
        may.Xuat(os);
        return os;
    }
};


int main() {
    // tạo cỗ máy mới
    CoMay* pcm = new CoMay();
    // thêm chi tiết đơn
    pcm->ThemChiTietMay(new ChiTietDon("CTD001", 120, 350000));
    // thêm chi tiết phức
    ChiTietMay* pctm = new ChiTietPhuc("CTP001");
    ((ChiTietPhuc*)pctm)->ThemChiTiet(new ChiTietDon("CTD002", 50, 1280000));
    ((ChiTietPhuc*)pctm)->ThemChiTiet(new ChiTietDon("CTD003", 20, 10000));

    ChiTietMay* pctm1 = new ChiTietPhuc("CTP002");
    ((ChiTietPhuc*)pctm1)->ThemChiTiet(new ChiTietDon("CTD004", 80, 170000));

    ((ChiTietPhuc*)pctm)->ThemChiTiet(pctm1);
    
    pcm->ThemChiTietMay(pctm);
    pcm->ThemChiTietMay(new ChiTietDon("CTD005", 210, 2350000));
    pcm->ThemChiTietMay(new ChiTietDon("CTD006", 40, 50000));

    // Xuất thông tin cỗ máy
    // xuất danh sách các chi tiết con
    cout << "Thong tin co may: " << endl << *pcm << endl;

    // Xuất trọng lượng cỗ máy
    cout << "Trong luong: " << pcm->TrongLuong() << endl;
    // Xuất giá thành cỗ máy
    cout << "Gia thanh: " << (int)pcm->GiaThanh() << endl;

    cout << endl << endl;
    system("pause");
    return 0;
}