#include <string>
#include <iostream>

using namespace std;


class NhanVien {
private:
  string hoTen, diaChi;
public:
  NhanVien() {}
  NhanVien(const string ht, const string dc) : hoTen(ht), diaChi(dc) {}
  ~NhanVien() {}


  friend ostream& operator<<(ostream& os, const NhanVien& nv) {
    os << nv.hoTen << " (" << nv.diaChi << ")";

    return os;
   }
};

class NhanVienKyThuat : public NhanVien {
private:
  string chungChiNganh;
public:
  NhanVienKyThuat() : NhanVien() {}
  NhanVienKyThuat(const string ht, const string dc, const string cc) : NhanVien(ht, dc), chungChiNganh(dc) {}
  ~NhanVienKyThuat() {}

  friend ostream& operator<< (ostream& os, const NhanVienKyThuat& nv) {
    os << (NhanVien) nv;
    os << " [" << nv.chungChiNganh << "]";
    return os;
  }
};



int main() {
  NhanVienKyThuat nvkt("Nguyen Van A", "Nguyen Van Cu, Q.5", "CNTT");

  cout << nvkt << endl << endl;

  system("pause");
  return 0;
}