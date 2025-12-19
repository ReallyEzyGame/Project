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
  virtual ~HinhHocPhang() {}

  float operator[](const int idx) const
  {
    return canh[idx];
  }
  float &operator[](const int idx)
  {
    return canh[idx];
  }
  virtual std::string ten() const = 0;
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
  virtual std::ostream &output(std::ostream &os) const
  {
    int n = canh.size();
    for (int i = 0; i < n - 1; ++i)
    {
      os << canh[i] << ", ";
    }
    os << canh[n - 1];

    return os;
  }

  virtual float chu_vi() const = 0;
  virtual float dien_tich() const = 0;
  friend std::istream &operator>>(std::istream &is, HinhHocPhang &hinh)
  {
    return hinh.input(is);
  }
  friend std::ostream &operator<<(std::ostream &os, const HinhHocPhang& hinh)
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

  std::string ten() const final
  {
    return "Tam Giac";
  }
  float chu_vi() const final
  {
    return canh[0] + canh[1] + canh[2];
  }
  float dien_tich() const final
  {
    float p = chu_vi() / 2.0;
    return sqrt(p * (p - canh[0]) * (p - canh[1]) * (p - canh[2]));
  }

  std::ostream& output(std::ostream& os) const {
    os << "htg: ";
    HinhHocPhang::output(os);
    os << ", cv: " << chu_vi() << ", dt: " << dien_tich();

    return os;
  }
  friend std::ostream& operator<< (std::ostream& os, const HinhTamGiac& hinh) {
    return hinh.output(os);
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

  std::string ten() const final
  {
    return "Thang Vuong";
  }
  float chu_vi() const final
  {
    return canh[0] + canh[1] + canh[2] + sqrt(pow(canh[0] - canh[1], 2) + pow(canh[2], 2));
  }
  float dien_tich() const final
  {
    return 1.0 * canh[2] * (canh[0] + canh[1]) / 2;
  }


  std::ostream& output(std::ostream& os) const {
    os << "hthv: ";
    HinhHocPhang::output(os);
    os << ", cv: " << chu_vi() << ", dt: " << dien_tich();

    return os;
  }
  friend std::ostream& operator<< (std::ostream& os, const HinhThangVuong& hinh) {
    return hinh.output(os);
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

  std::string ten() const final
  {
    return "Chu Nhat";
  }
  float chu_vi() const final
  {
    return 2 * (canh[0] + canh[1]);
  }
  float dien_tich() const final
  {
    return canh[0] * canh[1];
  }


  std::ostream& output(std::ostream& os) const {
    os << "hcn: ";
    HinhHocPhang::output(os);
    os << ", cv: " << chu_vi() << ", dt: " << dien_tich();

    return os;
  }
  friend std::ostream& operator<< (std::ostream& os, const HinhChuNhat& hinh) {
    return hinh.output(os);
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

  std::string ten() const final
  {
    return "Tron";
  }
  float chu_vi() const final
  {
    return 2 * _PI_ * canh[0];
  }
  float dien_tich() const final
  {
    return _PI_ * canh[0] * canh[0];
  }


    std::ostream& output(std::ostream& os) const {
    os << "htr: ";
    HinhHocPhang::output(os);
    os << ", cv: " << chu_vi() << ", dt: " << dien_tich();

    return os;
  }
  friend std::ostream& operator<< (std::ostream& os, const HinhTron& hinh) {
    return hinh.output(os);
  }
};



class QuanLyHinhHocPhang
{
private:
  std::vector<HinhHocPhang *> hinh;

public:
  QuanLyHinhHocPhang() {};
  QuanLyHinhHocPhang(const QuanLyHinhHocPhang &khac)
  {
    *this = khac;
  }
  ~QuanLyHinhHocPhang() {}

  int so_hinh() const
  {
    return hinh.size();
  }
  int so_hinh(const std::string ten_hinh) const
  {
    int cnt = 0;

    for (int i = 0; i < hinh.size(); ++i)
    {
      if (hinh[i]->ten() == ten_hinh)
      {
        cnt++;
      }
    }

    return cnt;
  }

  void them(HinhHocPhang *hh)
  {
    hinh.push_back(std::move(hh));
  }
  // tính tổng chu vi theo loại hình cụ thể
  float tong_chu_vi_theo_hinh(const std::string ten_hinh) const
  {
    float sum = 0;

    for (int i = 0; i < hinh.size(); i++)
    {
      if (hinh[i]->ten() == ten_hinh)
        sum += hinh[i]->chu_vi();
    }

    return sum;
  }
  // Tổng diện tích của tất cả các hình
  float tong_chu_vi() const
  {
    float sum = 0;

    for (int i = 0; i < hinh.size(); i++)
    {
      sum += hinh[i]->chu_vi();
    }

    return sum;
  }
  // Tính tổng diện tích theo loại hình cụ thể
  float tong_dien_tich_theo_hinh(const std::string ten_hinh)
  {
    float sum = 0;

    for (int i = 0; i < hinh.size(); i++)
    {
      if (hinh[i]->ten() == ten_hinh)
        sum += hinh[i]->dien_tich();
    }

    return sum;
  }
  // tính tổng diện tích tất cả các hình
  float tong_dien_tich() const
  {
    float sum = 0;

    for (int i = 0; i < hinh.size(); i++)
    {
      sum += hinh[i]->dien_tich();
    }

    return sum;
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

      HinhHocPhang *hhp;
      if (geo_type == "htg")
      {
        hhp = new HinhTamGiac();
      }
      else if (geo_type == "hthv")
      {
        hhp = new HinhThangVuong();
      }
      else if (geo_type == "hcn")
      {
        hhp = new HinhChuNhat();
      }
      else if (geo_type == "htr")
      {
        hhp = new HinhTron();
      }

      is >> *hhp;
      them(hhp);
    }

    return is;
  }
  std::ostream &output(std::ostream &os) const
  {
    // In ra thông tin của các hình học
    for (int i = 0; i < hinh.size(); ++i)
    {
      os << *hinh[i] << std::endl;
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

  HinhChuNhat *chu_nhat = new HinhChuNhat();
  QuanLyHinhHocPhang ql;

  std::cout << "Nhap do 2 do dai canh cua hinh chu nhat: ";
  std::cin >> *chu_nhat;

  ql.them(chu_nhat);

  input >> ql;
  output << ql;

  std::cout << *chu_nhat << std::endl;
  std::cout << "Danh sach hinh hoc:\n"
            << ql << std::endl;
  std::cout << std::endl;
  std::cout << "Tong So Hinh: " << ql.so_hinh() << std::endl;
  std::cout << "So Hinh Tron: " << ql.so_hinh("Tron") << std::endl;
  std::cout << "So Hinh Thang Vuong: " << ql.so_hinh("Thang Vuong") << std::endl;
  std::cout << "So Hinh Chu Nhat: " << ql.so_hinh("Chu Nhat") << std::endl;
  std::cout << "So Hinh Tam Giac: " << ql.so_hinh("Tam Giac") << std::endl;
  std::cout << std::endl;
  std::cout << "Tong Chu Vi Hinh Tam Giac: " << ql.tong_chu_vi_theo_hinh("Tam Giac") << std::endl;
  std::cout << "Tong Chu Vi Hinh Thang Vuong: " << ql.tong_chu_vi_theo_hinh("Thang Vuong") << std::endl;
  std::cout << "Tong Chu Vi Hinh Chu Nhat: " << ql.tong_chu_vi_theo_hinh("Chu Nhat") << std::endl;
  std::cout << "Tong Chu Vi Hinh Tron: " << ql.tong_chu_vi_theo_hinh("Tron") << std::endl;
  std::cout << "Tong Chu Vi: " << ql.tong_chu_vi() << std::endl;
  std::cout << std::endl;
  std::cout << "Tong Dien Tich Hinh Tam Giac: " << ql.tong_dien_tich_theo_hinh("Tam Giac") << std::endl;
  std::cout << "Tong Dien Tich Hinh Thang Vuong: " << ql.tong_dien_tich_theo_hinh("Thang Vuong") << std::endl;
  std::cout << "Tong Dien Tich Hinh Chu Nhat: " << ql.tong_dien_tich_theo_hinh("Chu Nhat") << std::endl;
  std::cout << "Tong Dien Tich Hinh Tron: " << ql.tong_dien_tich_theo_hinh("Tron") << std::endl;
  std::cout << "Tong Dien Tich: " << ql.tong_dien_tich() << std::endl;

  input.close();
  output.close();
}