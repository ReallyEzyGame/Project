#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>

#define _PI_ 3.14159

// Chuyển ký tự chuỗi thành kiểu float dương
float to_float(const char *str)
{
  int n = strlen(str);
  int integer = 0;
  float decimal = 0;

  // Lấy phần nguyên
  int i = 0;
  for (; i < n && str[i] != '.'; ++i)
  {
    integer = integer * 10 + (str[i] - '0');
  }
  // Lấy phần thập phân
  for (int j = n - 1; j > i && str[j] != '.'; --j)
  {
    decimal = decimal / 10 + (str[j] - '0');
  }
  decimal /= 10;
  return integer + decimal;
}
// operator >> của các đối tượng hình học chỉ có thể nhận format tương tự như trong file yêu cầu
// #Format:    hinhoc: dodai1, dodai2, dodai3,...
class HinhHocPhang
{
protected:
  std::vector<float> canh;

public:
  HinhHocPhang() {};
  HinhHocPhang(const HinhHocPhang &hinh)
  {
    *this = hinh;
  }
  ~HinhHocPhang() {}

  float operator[](const int idx) const
  {
    return canh[idx];
  }

  std::istream &input(std::istream &is)
  {
    const int len = 1024;
    int n = canh.size();

    char *line = new char[len];
    char *context;

    is.getline(line, len, '\n');
    // lấy độ dài
    for (int i = 0; i < n; ++i)
    {
      char *tmp = i == 0 ? line : nullptr;
      float value = to_float(strtok_s(tmp, " ,", &context));
      
      value = abs(value);
      canh[i] = value;
    }

    delete[] line;
    return is;
  }
  std::ostream &output(std::ostream &os) const
  {
    int n = canh.size();
    for (int i = 0; i < n - 1; ++i)
    {
      os << canh[i] << ", ";
    }
    os << canh[n-1];

    return os;
  }
  friend std::istream &operator>>(std::istream &is, HinhHocPhang &hinh)
  {
    return hinh.input(is);
  }
  friend std::ostream &operator<<(std::ostream &os,const HinhHocPhang hinh)
  {
    return hinh.output(os);
  }
};

class HinhTamGiac : public HinhHocPhang
{
public:
  HinhTamGiac()
  {
    canh = std::vector<float>(3, 0);
  }
  HinhTamGiac(const float c)
  {
    canh = std::vector<float>(3, std::abs(c));
  }
  HinhTamGiac(const float c1, const float c2, const float c3)
  {
    canh = std::vector<float>({std::abs(c1), std::abs(c2), std::abs(c3)});
  }
  HinhTamGiac(const HinhTamGiac &hinh_khac)
  {
    canh = std::vector<float>({hinh_khac.canh[0], hinh_khac.canh[1], hinh_khac.canh[2]});
  }
  ~HinhTamGiac() {}

  float chu_vi() const
  {
    return canh[0] + canh[1] + canh[2];
  }
  float dien_tich() const
  {
    float p = chu_vi() / 2.0;
    return sqrt(p * (p - canh[0]) * (p - canh[1]) * (p - canh[2]));
  }
};
class HinhThangVuong : public HinhHocPhang
{
public:
  HinhThangVuong()
  {
    canh = std::vector<float>(3, 0);
  }
  HinhThangVuong(const float c)
  {
    canh = std::vector<float>(3, abs(c));
  }
  HinhThangVuong(const float day_lon, const float day_be, const float cao)
  {
    canh = std::vector({abs(day_lon), abs(day_be), abs(cao)});
  }
  ~HinhThangVuong() {}

  float chu_vi() const
  {
    return canh[0] + canh[1] + canh[2] + sqrt(pow(canh[0] - canh[1], 2) + pow(canh[2], 2));
  }
  float dien_tich() const
  {
    return 1.0 * canh[2] * (canh[0] + canh[1]) / 2;
  }
};
class HinhChuNhat : public HinhHocPhang
{
public:
  HinhChuNhat() : HinhHocPhang()
  {
    canh = std::vector<float>(2, 0);
  }
  HinhChuNhat(const float c) : HinhHocPhang()
  {
    canh = std::vector<float>(2, std::abs(c));
  }
  HinhChuNhat(const float c1, const float c2)
  {
    canh = std::vector<float>({std::abs(c1), std::abs(c2)});
  }
  HinhChuNhat(const HinhChuNhat &hinh_khac)
  {
    canh = std::vector<float>({hinh_khac.canh[0], hinh_khac.canh[1]});
  }
  ~HinhChuNhat() {}

  float chu_vi() const
  {
    return 2 * (canh[0] + canh[1]);
  }
  float dien_tich() const
  {
    return canh[0] * canh[1];
  }
};
class HinhTron : public HinhHocPhang
{
public:
  HinhTron() : HinhHocPhang()
  {
    canh = std::vector<float>(1, 0);
  }
  HinhTron(const float c) : HinhHocPhang()
  {
    canh = std::vector<float>(1, std::abs(c));
  }
  HinhTron(const HinhTron &hinh_khac)
  {
    canh = std::vector<float>({hinh_khac.canh[0]});
  }
  ~HinhTron() {}

  float chu_vi() const
  {
    return 2 * _PI_ * canh[0];
  }
  float dien_tich() const
  {
    return _PI_ * canh[0] * canh[0];
  }
};

class QuanLyHinhHocPhang
{
private:
  std::vector<HinhTamGiac> _tam_giac;
  std::vector<HinhThangVuong> _thang_vuong;
  std::vector<HinhChuNhat> _chu_nhat;
  std::vector<HinhTron> _hinh_tron;

public:
  QuanLyHinhHocPhang() {};
  QuanLyHinhHocPhang(const QuanLyHinhHocPhang &khac)
  {
    *this = khac;
  }
  ~QuanLyHinhHocPhang() {}

  void them_tg(const HinhTamGiac tg)
  {
    _tam_giac.push_back(tg);
  }
  void them_htv(const HinhThangVuong htv)
  {
    _thang_vuong.push_back(htv);
  }
  void them_hcn(const HinhChuNhat hcn)
  {
    _chu_nhat.push_back(hcn);
  }
  void them_hinh_tron(const HinhTron ht)
  {
    _hinh_tron.push_back(ht);
  }

  int so_tam_giac() const {
    return _tam_giac.size();
  }
  int so_thang_vuong() const {
    return _thang_vuong.size();
  }
  int so_chu_nhat() const {
    return _chu_nhat.size();
  }
  int so_hinh_tron() const {
    return _hinh_tron.size();
  }
  int so_hinh() const {
    return so_tam_giac() + so_thang_vuong() + so_chu_nhat() + so_hinh_tron();
  }

  float tong_chu_vi_tg() const {
    float p = 0;

    for (HinhTamGiac tg : _tam_giac) {
      p += tg.chu_vi();
    }

    return p;
  }
  float tong_chu_vi_hcn() const {
    float p = 0;

    for (HinhChuNhat hcn : _chu_nhat) {
      p += hcn.chu_vi();
    }

    return p;
  }
  float tong_chu_vi_hthv() const {
    float p = 0;

    for (HinhThangVuong hthv: _thang_vuong) {
      p += hthv.chu_vi();
    }

    return p;
  }
  float tong_chu_vi_ht() const {
    float p = 0;

    for (HinhTamGiac ht : _tam_giac) {
      p += ht.chu_vi();
    }

    return p;
  }
  float tong_chu_vi() const {
    return tong_chu_vi_tg() + tong_chu_vi_hcn() + tong_chu_vi_hthv() + tong_chu_vi_hcn();
  }

  float tong_dien_tich_tg() const {
    float s = 0;
    for (HinhTamGiac tg : _tam_giac) {
      s += tg.dien_tich();
    }

    return s;
  }
  float tong_dien_tich_hthv() const {
    float s = 0;
    for (HinhThangVuong hthv : _thang_vuong) {
      s += hthv.dien_tich();
    }

    return s;
  }
  float tong_dien_tich_hcn() const {
    float s = 0;

    for (HinhChuNhat hcn : _chu_nhat) {
      s += hcn.dien_tich();
    }

    return s;
  }
  float tong_dien_tich_ht() const {
    float s = 0;

    for (HinhTron ht : _hinh_tron) {
      s += ht.dien_tich();
    }

    return s;
  }
  float tong_dien_tich() const {
    return tong_dien_tich_tg() + tong_dien_tich_hthv() + tong_dien_tich_hcn() + tong_dien_tich_ht();
  }
  
  std::istream &input(std::istream &is)
  {
    char trash;
    while (!is.eof())
    {
      std::string geo_type;
      char ch;
      // Xác định tên hình
      while (is.get(ch))
      {
        if (ch == ':')
        {
          break;
        }
        geo_type.push_back(ch);
      }

      if (geo_type == "htg")
      {
        HinhTamGiac hinh;
        is >> hinh;
        them_tg(hinh);
      }
      else if (geo_type == "hthv")
      {
        HinhThangVuong hinh;
        is >> hinh;
        them_htv(hinh);
      }
      else if (geo_type == "hcn")
      {
        HinhChuNhat hinh;
        is >> hinh;
        them_hcn(hinh);
      }
      else if (geo_type == "htr")
      {
        HinhTron hinh;
        is >> hinh;
        them_hinh_tron(hinh);
      }
    }

    return is;
  }
  std::ostream &output(std::ostream &os) const
  {
    // In ra do dai canh cua hinh tam giac
    int n = _tam_giac.size();
    for (int i = 0; i < n; ++i)
    {
      os << "htg: ";
      os << _tam_giac[i];
      os << ", cv: " << _tam_giac[i].chu_vi();
      os << ", dt: " << _tam_giac[i].dien_tich();
      os << std::endl;
    }
    // In ra do dai canh cua hinh thang vuong
    n = _thang_vuong.size();
    for (int i = 0; i < n; ++i)
    {
      os << "hthv: ";
      os << _thang_vuong[i];
      os << ", cv: " << _thang_vuong[i].chu_vi();
      os << ", dt: " << _thang_vuong[i].dien_tich();
      os << std::endl;
    }
    // In ra do dai canh cua hinh chu nhat
    n = _chu_nhat.size();
    for (int i = 0; i < n; ++i)
    {
      os << "hcn: ";
      os << _chu_nhat[i];
      os << ", cv: " << _chu_nhat[i].chu_vi();
      os << ", dt: " << _chu_nhat[i].dien_tich();
      os << std::endl;
    }
    // In ra do dai canh cua hinh tron
    n = _hinh_tron.size();
    for (int i = 0; i < n; ++i)
    {
      os << "ht: ";
      os << _hinh_tron[i];
      os << ", cv: " << _hinh_tron[i].chu_vi();
      os << ", dt: " << _hinh_tron[i].dien_tich();
      os << std::endl;
    }
    return os;
  }
  friend std::istream &operator>>(std::istream &is, QuanLyHinhHocPhang &ql)
  {
    return ql.input(is);
  }
  friend std::ostream &operator<<(std::ostream &os, const QuanLyHinhHocPhang ql)
  {
    return ql.output(os);
  }
};

std::string input_path = "hhp.txt";
std::string output_path = "output.txt";

int main()
{
  std::ifstream input(input_path);
  std::ofstream output(output_path);

  HinhChuNhat chu_nhat;
  QuanLyHinhHocPhang ql;

  std::cout << "Nhap do 2 do dai canh cua hinh chu nhat: ";
  std::cin >> chu_nhat;

  ql.them_hcn(chu_nhat);

  input >> ql;
  output << ql;

  std::cout << chu_nhat << std::endl;
  std::cout << "Danh sach hinh hoc:\n" << ql << std::endl;
  std::cout << std::endl;
  std::cout << "Tong So Hinh: " << ql.so_hinh() << std::endl;
  std::cout << "So Hinh Tron: " << ql.so_hinh_tron() << std::endl;
  std::cout << "So Hinh Thang Vuong: " << ql.so_thang_vuong() << std::endl;
  std::cout << "So Hinh Chu Nhat: " << ql.so_chu_nhat() << std::endl;
  std::cout << "So Hinh Tam Giac: " << ql.so_tam_giac() << std:: endl;
  std::cout << std::endl;
  std::cout << "Tong Chu Vi Hinh Tam Giac: " << ql.tong_chu_vi_tg() << std::endl;
  std::cout << "Tong Chu Vi Hinh Thang Vuong: " << ql.tong_chu_vi_hthv() << std::endl;
  std::cout << "Tong Chu Vi Hinh Chu Nhat: " << ql.tong_chu_vi_hcn() << std::endl;
  std::cout << "Tong Chu Vi Hinh Tron: " << ql.tong_chu_vi_ht() << std::endl;
  std::cout << "Tong Chu Vi: " << ql.tong_chu_vi() << std::endl;
  std::cout << std::endl;
  std::cout << "Tong Dien Tich Hinh Tam Giac: " << ql.tong_dien_tich_tg() << std::endl;
  std::cout << "Tong Dien Tich Hinh Thang Vuong: " << ql.tong_dien_tich_hthv() << std::endl;
  std::cout << "Tong Dien Tich Hinh Chu Nhat: " << ql.tong_dien_tich_hcn() << std::endl;
  std::cout << "Tong Dien Tich Hinh Tron: " << ql.tong_dien_tich_ht() << std::endl;
  std::cout << "Tong Dien Tich: " << ql.tong_dien_tich() << std::endl;

  input.close();
  output.close();
}