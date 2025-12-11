#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Hinh
{
protected:
  std::vector<float> canh;

public:
  Hinh(const int n) : canh(n) {}
  Hinh(const vector<float> values) : canh(values) {}
  Hinh(const Hinh &other) : canh(other.canh) {}
  ~Hinh() {}

  istream &input(istream &is)
  {
    float value;

    for (int i = 0; i < canh.size(); ++i)
    {
      is >> value;
      value = std::abs(value);

      canh[i] = value;
    }

    return is;
  }
  virtual ostream &output(ostream &os) const = 0;

  friend ostream& operator<< (ostream& os, const Hinh& hinh) {
    return hinh.output(os);
  }
};

class Hinh2D : public Hinh
{
public:
  Hinh2D(const int n) : Hinh(n) {}
  Hinh2D(const vector<float> values) : Hinh(values) {}
  Hinh2D(const Hinh2D &other) : Hinh(other) {}
  ~Hinh2D() {}

  virtual ostream &output(ostream &os) const override = 0;

  virtual float chu_vi() const = 0;
  virtual float dien_tich() const = 0;
};

class HinhTron : public Hinh2D
{
public:
  HinhTron() : Hinh2D(1) {}
  HinhTron(const float r) : Hinh2D(vector<float>(1, r)) {}
  HinhTron(const HinhTron &other) : Hinh2D(other) {}
  ~HinhTron() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh tron> [" << chu_vi() << ", " << dien_tich() << "]";
    return os;
  }

  float chu_vi() const final
  {
    return 2 * M_PI * canh[0];
  }
  float dien_tich() const final
  {
    return M_PI * canh[0] * canh[0];
  }

  friend ostream& operator<< (ostream& os, const HinhTron& hinh) {
    return hinh.output(os);
  }
};
class HinhTamGiacDeu : public Hinh2D
{
public:
  HinhTamGiacDeu() : Hinh2D(1) {}
  HinhTamGiacDeu(const float c) : Hinh2D(vector<float>(1, c)) {}
  HinhTamGiacDeu(const vector<float> values) : Hinh2D(1)
  {
    canh[0] = std::abs(values[0]);
  }
  HinhTamGiacDeu(const HinhTamGiacDeu &other) : Hinh2D(other) {}
  ~HinhTamGiacDeu() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh tam giac deu> [" << chu_vi() << ", " << dien_tich() << "]";
    return os;
  }

  float chu_vi() const final
  {
    return 3 * canh[0];
  }
  float dien_tich() const final
  {
    return sqrt(3) / 2.0 * pow(canh[0], 2);
  }

  friend ostream& operator<< (ostream& os, const HinhTamGiacDeu& hinh) {
    return hinh.output(os);
  }
};
class HinhChuNhat : public Hinh2D
{
public:
  HinhChuNhat() : Hinh2D(2) {}
  HinhChuNhat(const float val1, const float val2) : Hinh2D(vector<float>({val1, val2})) {}
  HinhChuNhat(const vector<float> values) : Hinh2D(2)
  {
    canh[0] = std::abs(values[0]);
    canh[1] = std::abs(values[1]);
  }
  ~HinhChuNhat() {}

  virtual ostream &output(ostream &os) const override
  {
    os << "<hinh chu nhat> [" << chu_vi() << ", " << dien_tich() << "]";
    return os;
  }

  virtual float chu_vi() const override
  {
    return 2 * (canh[0] + canh[1]);
  }
  virtual float dien_tich() const override
  {
    return canh[0] * canh[1];
  }

  friend ostream& operator<< (ostream& os, const HinhChuNhat& hinh) {
    return hinh.output(os);
  }
};
class HinhVuong : public HinhChuNhat
{
public:
  HinhVuong() : HinhChuNhat() {}
  HinhVuong(const float c) : HinhChuNhat(vector<float>({c, c})) {}
  HinhVuong(const vector<float> values) : HinhChuNhat()
  {
    canh[0] = std::abs(values[0]);
    canh[1] = std::abs(values[1]);
  }
  HinhVuong(const HinhVuong &other) : HinhChuNhat(other) {}
  ~HinhVuong() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh vuong> [" << chu_vi() << ", " << dien_tich() << "]";
    return os;
  }

  float chu_vi() const final
  {
    return HinhChuNhat::chu_vi();
  }
  float dien_tich() const final
  {
    return HinhChuNhat::dien_tich();
  }

  friend ostream& operator<< (ostream& os, const HinhVuong& hinh) {
    return hinh.output(os);
  }
};

class Hinh3D : public Hinh
{
public:
  Hinh3D(const int n) : Hinh(n) {}
  Hinh3D(const vector<float> values) : Hinh(values) {}
  Hinh3D(const Hinh3D &other) : Hinh(other) {}
  ~Hinh3D() {}

  virtual ostream &output(ostream &os) const override = 0;

  virtual float dien_tich_xq() const = 0;
  virtual float the_tich() const = 0;
};

class HinhCau : public Hinh3D
{
public:
  HinhCau() : Hinh3D(1) {}
  HinhCau(const float r) : Hinh3D(vector<float>({r})) {}
  HinhCau(const HinhCau &other) : Hinh3D(other) {}
  ~HinhCau() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh cau> [" << dien_tich_xq() << ", " << the_tich() << "]";
    return os;
  }

  float dien_tich_xq() const final
  {
    return 4.0 / 3 * M_PI * pow(canh[0], 3);
  }
  float the_tich() const final
  {
    return 4 * M_PI * pow(canh[0], 2);
  }

  friend ostream& operator<< (ostream& os, const HinhCau& hinh) {
    return hinh.output(os);
  }
};
class HinhLapPhuong : public Hinh3D
{
public:
  HinhLapPhuong() : Hinh3D(1) {}
  HinhLapPhuong(const float c) : Hinh3D(vector<float>({c})) {}
  HinhLapPhuong(const HinhCau &other) : Hinh3D(other) {}
  ~HinhLapPhuong() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh lap phuong> [" << dien_tich_xq() << ", " << the_tich() << "]";
    return os;
  }

  float dien_tich_xq() const final
  {
    return 4 * pow(canh[0], 2);
  }
  float the_tich() const final
  {
    return pow(canh[0], 3);
  }

  friend ostream& operator<< (ostream& os, const HinhLapPhuong& hinh) {
    return hinh.output(os);
  }
};
class HinhHop : public Hinh3D
{
public:
  HinhHop() : Hinh3D(3) {}
  HinhHop(const float d, const float r, const float c) : Hinh3D(vector<float>({d, r, c})) {}
  HinhHop(const HinhCau &other) : Hinh3D(other) {}
  ~HinhHop() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh hop> [" << dien_tich_xq() << ", " << the_tich() << "]";
    return os;
  }

  float dien_tich_xq() const final
  {
    float hcn1 = canh[0] * canh[1];
    float hcn2 = canh[1] * canh[2];

    return 2 * (hcn1 + hcn2);
  }
  float the_tich() const final
  {
    return canh[0] * canh[1] * canh[2];
  }

  friend ostream& operator<< (ostream& os, const HinhHop& hinh) {
    return hinh.output(os);
  }
};
class HinhTru : public Hinh3D
{
public:
  HinhTru() : Hinh3D(2) {}
  HinhTru(const float c, const float r) : Hinh3D(vector<float>({c, r})) {}
  HinhTru(const HinhCau &other) : Hinh3D(other) {}
  ~HinhTru() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh tru> [" << dien_tich_xq() << ", " << the_tich() << "]";
    return os;
  }

  float dien_tich_xq() const final
  {
    float hcn = canh[0] * 2 * M_PI * canh[1];
    return hcn;
  }
  float the_tich() const final
  {
    return canh[0] * M_PI * pow(canh[1], 2);
  }

  friend ostream& operator<< (ostream& os, const HinhTru hinh) {
    return hinh.output(os);
  }
};
class HinhNon : public Hinh3D
{
public:
  HinhNon() : Hinh3D(2) {}
  HinhNon(const float h, const float r) : Hinh3D(vector<float>({h, r})) {}
  HinhNon(const HinhCau &other) : Hinh3D(other) {}
  ~HinhNon() {}

  ostream &output(ostream &os) const final
  {
    os << "<hinh non> [" << dien_tich_xq() << ", " << the_tich() << "]";
    return os;
  }

  float dien_tich_xq() const final
  {
    return M_PI * canh[1] * sqrt(pow(canh[0], 2) + pow(canh[1], 2));
  }
  float the_tich() const final
  {
    return M_PI * canh[0] * pow(canh[1], 2);
  }

  friend ostream& operator<< (ostream& os, const HinhNon& hinh) {
    return hinh.output(os);
  }
};



int main()
{
  vector<Hinh *> dsHinh;
  
  dsHinh.push_back(new HinhTron(3.5));
  dsHinh.push_back(new HinhTamGiacDeu(8.5));
  dsHinh.push_back(new HinhChuNhat(3.7, 1.9));
  dsHinh.push_back(new HinhVuong(4.1));
  dsHinh.push_back(new HinhCau(13.5));
  dsHinh.push_back(new HinhLapPhuong(2.9));
  dsHinh.push_back(new HinhHop(1.2, 3.7, 6.3));
  dsHinh.push_back(new HinhTru(6.1, 4.9));
  dsHinh.push_back(new HinhNon(8.7, 3.2));

  for (int i = 0; i < dsHinh.size(); ++i)
  {
    cout << *dsHinh[i] << std::endl;
  }

  cout << endl
       << endl;
  system("pause");
  return 0;
}