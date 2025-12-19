#include <iostream>
#include <string>

#define _PI_ 3.14159

class HinhHocPhang {
public:
  HinhHocPhang() {}
  
  virtual float tinhDienTich() const {
    return 0;
  }
};

class HinhChuNhat : public HinhHocPhang {
private:  
  float chieuDai, chieuRong;
public:
  HinhChuNhat() : chieuDai(0), chieuRong(0) {};
  HinhChuNhat(const float cd, const float cr) {
    chieuDai = cd == 0 ? 1 : std::abs(cd);
    chieuRong = cr == 0 ? 1 : std::abs(cr);
  }

  float tinhDienTich() const final {
    return chieuDai * chieuRong;
  }
};
class HinhTron : public HinhHocPhang {
private:
  float banKinh;
public:
  HinhTron() : banKinh(0) {}
  HinhTron(const float r) {
    banKinh = r == 0 ? 1 : std::abs(r);
  }
  
  float tinhDienTich() const final {
    return _PI_ * banKinh * banKinh;
  }
};



int main() {
  HinhHocPhang* hhp = new HinhHocPhang();
  HinhChuNhat* hcn = new HinhChuNhat(34, 56.8);
  HinhTron* ht = new HinhTron(73.9);

  std::cout << hhp->tinhDienTich() << "\t" <<  hcn->tinhDienTich() << "\t" << ht->tinhDienTich();
  std::cout << std::endl;

  hhp = hcn;
  std::cout << hhp->tinhDienTich() << std::endl;

  std::cout << std::endl << std::endl;

  delete hhp;
  delete hcn;
  delete ht;
  system("pause");
  return 0;
}