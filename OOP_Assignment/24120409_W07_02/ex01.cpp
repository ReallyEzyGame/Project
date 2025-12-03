#include <fstream>
#include "String.h"

#define _SECRETARTY_ 0
#define _EGINEER_ 1

int to_integer(const String str) {
  int n = str.size();
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum = 10 * sum + (str[i] - '0');
  }
  return sum;
}


class CongTy;


class NhanVien {
  static unsigned long long _current_id;
private:
  String _name;
  String _address;
  unsigned long long _id;

public:
  NhanVien() = delete;
  

  NhanVien(const String name, const String address) {
    _name = name;
    _address = address;
    _id = _current_id++;
  }
  NhanVien(const NhanVien& other) {
    _name = other._name;
    _address = other._address;
    _id = other._id;
  }
  ~NhanVien() {}


  unsigned long long id() const {
    return _id;
  }
  String name() const {
    return _name;
  }
  String address() const {
    return _address;
  }

  virtual bool is_excellent() const = 0;
  virtual void display() const {
    std::cout << "ID: " << id() << std::endl;
    std::cout << "Name: " << name() << std::endl;
    std::cout <<  "Address: " << address() << std::endl;
  }


  friend std::ostream& operator<< (std::ostream& os, const NhanVien& nv) {
    os << "ID: " << nv.id() << std::endl;
    os << "Name: " << nv.name() << std::endl;
    os <<  "Address: " << nv.address() << std::endl;

    return os;
  }
};
unsigned long long NhanVien::_current_id = 100000;

class NhanVienThuKy : public NhanVien {
private:
  String _language_certificate;
  int _number_report;
public:
  NhanVienThuKy(const String name, const String address, const String certificate, int reports = 0) : NhanVien(name, address) {
    _language_certificate = certificate;
    _number_report  = reports;
  }
  ~NhanVienThuKy() {}

  bool is_excellent() const final {
    return _number_report >= 12;
  }
  void display() const final {
    NhanVien::display();
    std::cout << "Language Certificate: " << _language_certificate << std::endl;
    std::cout << "Number Report: " << _number_report << std::endl;
  }

  // friend std::ostream& operator<< (std::ostream& os, const NhanVienThuKy& nv) {
    
  // }
};
class NhanVienKyThuat : public NhanVien {
private:
  String _department_certificate;
  int _number_idea;
public:
  NhanVienKyThuat(const String name, const String address, const String certificate, int ideas = 0) : NhanVien(name, address) {
    _department_certificate = certificate;
    _number_idea  = ideas;
  }
  ~NhanVienKyThuat() {}

  bool is_excellent() const final {
    return _number_idea >= 6;
  }
  void display() const final {
    NhanVien::display();
    std::cout << "Department certificate: " << _department_certificate << std::endl;
    std::cout << "Number idex: " << _number_idea << std::endl;
  }

  // friend std::ostream& operator<< (std::ostream& os, const NhanVienKyThuat) {

  // }
};


class CongTy
{
private:
  String _name;
  String _address;
  Array<NhanVien *> _employees;
public:
  CongTy(const String name) : _name(name), _address(), _employees() {}
  CongTy(const String name, const String address) : _name(name), _address(address), _employees() {}
  // We do not allow companies to copy each other
  CongTy(const CongTy &other) = delete;
  ~CongTy() {
    int n = _employees.size();
    for (int i = 0; i < n; ++i) {
      delete _employees[i];
    }
  }

  // // we do not allow outside using this function since it can create a nullptr or memory error
  void add_employee(NhanVien* nv) {
    _employees.push_back(nv);
  }
  int size() const
  {
    return _employees.size();
  }

  Array<NhanVien*>::Iterator begin() const {
    return &_employees[0];
  }
  Array<NhanVien*>::Iterator end() const {
    return (&_employees[0] + size());
  }
  // Display excellent employees to the Terminal
  void display_excellent_employee() {
    int n =  size();
    for (int i = 0; i < n; ++i) {
      if (_employees[i]->is_excellent()) {
        std::cout << (*_employees[i]) << std::endl;
      }
    }
  }

  NhanVien*& operator[](const int idx) {
    if (0 <= idx && idx < size()) {
      return _employees[idx];
    }
    else {
      throw std::out_of_range("Out of Array range");
    }
  }
  friend std::istream& operator>> (std::istream& is, CongTy& company) {
    const int N = 1024;
    char* line = new char[N];
    char *context;
    char trash;

    while (is.getline(line, N, '\n')) {
      Array<String> infor(5);
      // employee 
      infor[0] = strtok_s(line, ":", &context);
      strtok_s(nullptr, " ", &context);
      // name
      infor[1] = strtok_s(nullptr, "(", &context);
      infor[1].pop_back();    // pop the space ' ' out
      // address
      infor[2] = strtok_s(nullptr, ")", &context);
      // certificate
      strtok_s(nullptr, "[", &context);
      infor[3] = strtok_s(nullptr, "]", &context);
      // number
      strtok_s(nullptr, " ", &context);
      infor[4] = strtok_s(nullptr, "]", &context);

      NhanVien* nv;
      if (infor[0] == "nvtk") {
        nv = new NhanVienThuKy(infor[1], infor[2], infor[3], to_integer(infor[4]));
      }
      if (infor[0] == "nvkt") {
        nv = new NhanVienKyThuat(infor[1], infor[2], infor[3], to_integer(infor[4]));
      }
      company.add_employee(nv);
    }

    return is;
  }
  // Display employee list to the output file
  friend std::ostream &operator<<(std::ostream &os, const CongTy company)
  {
    int n = company.size();
    for (int i = 0; i < n; ++i)
    {
      os << company._employees[i] << std::endl;
    }
    return os;
  }
};


const char* input = "input.txt";
const char* output = "output.txt";

int main()
{
  std::ifstream input_file(input);
  std::ofstream output_file(output);

  CongTy company("Cong ty 1 thanh vien tao-work");
  input_file >> company;

  company.display_excellent_employee();
  std::cout  << *company[0];
}