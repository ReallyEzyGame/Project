#include <fstream>
#include "String.h"

#define _SECRETARTY_ 0
#define _EGINEER_ 1

int to_integer(const String str)
{
  int n = str.size();
  int sum = 0;

  for (int i = 0; i < n; ++i)
  {
    sum = 10 * sum + (str[i] - '0');
  }

  return sum;
}
void trim(String& str) {
  while (!str.empty() && str[str.size() - 1] == ' ') {
    str.pop_back();
  }
}


class CongTy;



class NhanVien
{
protected:
  static unsigned long long _current_id;

protected:
  String _name;
  String _address;

  unsigned long long _id;

public:
  NhanVien()
  {
    _id = _current_id++;
  }
  NhanVien(const String name, const String address)
  {
    _name = name;
    _address = address;
    _id = _current_id++;
  }
  NhanVien(const NhanVien &other)
  {
    _name = other._name;
    _address = other._address;
    _id = other._id;
  }
  ~NhanVien() {}

  unsigned long long id() const
  {
    return _id;
  }
  String name() const
  {
    return _name;
  }
  String address() const
  {
    return _address;
  }

  void input_from_keyboard() {
    const int N = 1024;
    char *data = new char[N];

    std::cout << "Name: ";
    std::cin.getline(data, N, '\n');
    _name = data;

    std::cout << "Address: ";
    std::cin.getline(data, N, '\n');
    _address = data;

    delete[] data;
  }
  std::istream& input(std::istream& is) {
    Array<String> infor(2);
    int N = 1024;
    char line[N];

    // name
    is.getline(line, N, '(');
    infor[0] = line;
    trim(infor[0]);        // pop the space out ' '    
    // address
    is.getline(line, N, ')');
    infor[1] = line;
    trim(infor[1]);       // pop the space out ' '


    this->_name =  infor[0];
    this->_address = infor[1];

    return is;
  }
  std::ostream &output(std::ostream &os) const
  {
    os << id();
    os << " " << name();
    os << " (" << address() << ")";

    return os;
  }
  friend std::ostream &operator<<(std::ostream &os, const NhanVien &nv)
  {
    return nv.output(os);
  }
};
unsigned long long NhanVien::_current_id = 100000;


class NhanVienThuKy : public NhanVien
{
private:
  String _language_certificate;
  int _number_report;

public:
  NhanVienThuKy() : NhanVien() {}
  NhanVienThuKy(const String name, const String address, const String certificate, int reports = 0) : NhanVien(name, address)
  {
    _language_certificate = certificate;
    _number_report = reports;
  }
  ~NhanVienThuKy() {}

  bool is_excellent() const
  {
    return _number_report >= 12;
  }
  
  void input_from_keyboard() {
    int N = 1024;
    char *data = new char[N];

    NhanVien::input_from_keyboard();

    std::cout << "Language Certificate: ";
    std::cin.getline(data, N, '\n');
    _language_certificate = data;

    std::cout << "Number of report: ";
    std::cin >> _number_report;
    
    delete[] data;
  }
  std::istream &input(std::istream &is)
  {
    String infor;
    const int N = 1024;
    char line[N];

    NhanVien::input(is);

    is.ignore(N, '[');           // ignore trash data
    // certificate
    is.getline(line, N, ']');
    infor = line;
    trim(infor);
    _language_certificate = infor;

    is.ignore(N, '<');
    // number report
    is >> _number_report;

    is.ignore(N, '\n');

    return is;
  }
  std::ostream &output(std::ostream &os) const
  {
    os << "nvtk: ";
    NhanVien::output(os);
    os << " [" << _language_certificate << ']';
    os << " <" << _number_report << '>';

    return os;
  }
  friend std::istream &operator>>(std::istream &is, NhanVienThuKy &nv)
  {
    return nv.input(is);
  }
  friend std::ostream &operator<<(std::ostream &os, const NhanVienThuKy &nv)
  {
    return nv.output(os);
  }
};
class NhanVienKyThuat : public NhanVien
{
private:
  String _department_certificate;
  int _number_idea;

public:
  NhanVienKyThuat() : NhanVien() {}
  NhanVienKyThuat(const String name, const String address, const String certificate, int ideas = 0) : NhanVien(name, address)
  {
    _department_certificate = certificate;
    _number_idea = ideas;
  }
  ~NhanVienKyThuat() {}

  bool is_excellent() const
  {
    return _number_idea >= 6;
  }
  
  void input_from_keyboard() {
    int N = 1024;
    char *data = new char[N];

    NhanVien::input_from_keyboard();

    std::cout << "Department: ";
    std::cin.getline(data, N, '\n');
    _department_certificate = data;

    std::cout << "Number of Idea: ";
    std::cin >> _number_idea;

    delete[] data;
  }
  std::istream &input(std::istream &is)
  {
    String infor;
    const int N = 1024;
    char line[N];

    NhanVien::input(is);

    is.ignore(N, '[');       // ignore trash data
    // certificate
    is.getline(line, N, ']');
    infor = line;
    trim(infor);
    _department_certificate = infor;

    is.ignore(N, '<');       // ignore trash data
    // number
    is >> _number_idea;

    is.ignore(N, '\n');

    return is;
  }
  std::ostream &output(std::ostream &os) const
  {
    os << "nvkt: ";
    NhanVien::output(os);
    os << " [" << _department_certificate << ']';
    os << " <" << _number_idea << '>';

    return os;
  }
  friend std::istream &operator>>(std::istream &is, NhanVienKyThuat &nv)
  {
    return nv.input(is);
  }
  friend std::ostream &operator<<(std::ostream &os, const NhanVienKyThuat &nv)
  {
    return nv.output(os);
  }
};

class CongTy
{
private:
  String _name;
  String _address;
  Array<NhanVienThuKy> _secretaries;
  Array<NhanVienKyThuat> _engineers;

public:
  CongTy(const String name) : _name(name), _address(), _secretaries(), _engineers() {}
  CongTy(const String name, const String address) : _name(name), _address(address), _engineers(), _secretaries() {}
  // We do not allow companies to copy each other
  CongTy(const CongTy &other) = delete;
  ~CongTy() {}

  // // we do not allow outside using this function since it can create a nullptr or memory error
  void add_engineer(const NhanVienKyThuat nv)
  {
    _engineers.push_back(nv);
  }
  void add_secretary(const NhanVienThuKy nv)
  {
    _secretaries.push_back(nv);
  }
  int size_engineer() const
  {
    return _engineers.size();
  }
  int size_secretary() const
  {
    return _secretaries.size();
  }
  // Display excellent employees to the Terminal
  void display_excellent_employee()
  {
    int n = _engineers.size();
    for (int i = 0; i < n; ++i)
    {
      if (_engineers[i].is_excellent())
      {
        std::cout << _engineers[i] << std::endl;
      }
    }

    n = _secretaries.size();
    for (int i = 0; i < n; ++i)
    {
      if (_secretaries[i].is_excellent())
      {
        std::cout << _secretaries[i] << std::endl;
      }
    }
  }

  friend std::istream &operator>>(std::istream &is, CongTy &company)
  {
    const int N = 1024;
    char line[N];

    while (true)
    {
      String occupation;
      char ch;
      // get occupation data
      is.getline(line, N, ':');
      occupation = line;
      trim(occupation);

      if (is.eof()) {
        break;
      }
      is.get(ch);         // pass ':'
      // ignore space ' '`
      if (is.peek() == ' ') {
        is.get(ch);
      }

      if (occupation == "nvtk")
      {
        NhanVienThuKy nv;
        is >> nv;
        company.add_secretary(nv);
      }
      else if (occupation == "nvkt")
      {
        NhanVienKyThuat nv;
        is >> nv;
        company.add_engineer(nv);
      }
      else {
        is.getline(line, N, '\n');
      }
    }

    return is;
  }
  // Display employee list to the output file
  friend std::ostream &operator<<(std::ostream &os, const CongTy &company)
  {
    int n = company._engineers.size();
    for (int i = 0; i < n; ++i)
    {
      os << company._engineers[i] << std::endl;
    }
    n = company._secretaries.size();
    for (int i = 0; i < n; ++i)
    {
      os << company._secretaries[i] << std::endl;
    }

    return os;
  }
};


const char *input_path = "input.txt";
const char *output_path = "output.txt";


int main()
{
  std::ifstream input_file(input_path);
  std::ofstream output_file(output_path);
  NhanVienKyThuat nvkt;

  std::cout << "Ten thong tin nhan vien ky thuat 1:\n";
  nvkt.input_from_keyboard();

  CongTy company("Cong ty 1 thanh vien");
  input_file >> company;

  std::cout << "List of excellent_employee:\n";
  company.display_excellent_employee();

  std::cout << "Add NhanVien to the Company:\n";
  std::cout << nvkt;

  company.add_engineer(nvkt);

  output_file << company;

  input_file.close();
  output_file.close();
}