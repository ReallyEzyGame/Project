#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define _SECRETARTY_ 0
#define _EGINEER_ 1

int to_integer(const string str)
{
  int n = str.size();
  int sum = 0;

  for (int i = 0; i < n; ++i)
  {
    sum = 10 * sum + (str[i] - '0');
  }

  return sum;
}
void trim(string &str)
{
  while (!str.empty() && str[str.size() - 1] == ' ')
  {
    str.pop_back();
  }
}

class CongTy;

class NhanVien
{
protected:
  static unsigned long long _current_id;

protected:
  string _name;
  string _address;

  unsigned long long _id;

public:
  NhanVien()
  {
    _id = _current_id++;
  }
  NhanVien(const string name, const string address)
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
  virtual ~NhanVien() {}

  unsigned long long id() const
  {
    return _id;
  }
  string name() const
  {
    return _name;
  }
  string address() const
  {
    return _address;
  }

  virtual void input_from_keyboard()
  {
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
  virtual std::istream &input(std::istream &is)
  {
    vector<string> infor(2);
    const int N = 1024;
    char line[N];

    // name
    is.getline(line, N, '(');
    infor[0] = line;
    trim(infor[0]); // pop the space out ' '
    // address
    is.getline(line, N, ')');
    infor[1] = line;
    trim(infor[1]); // pop the space out ' '

    this->_name = infor[0];
    this->_address = infor[1];

    return is;
  }
  virtual std::ostream &output(std::ostream &os) const
  {
    os << id();
    os << " " << name();
    os << " (" << address() << ")";

    return os;
  }

  virtual bool is_excellent() const = 0;

  friend std::ostream &operator<<(std::ostream &os, const NhanVien &nv)
  {
    return nv.output(os);
  }
};
unsigned long long NhanVien::_current_id = 100000;

class NhanVienThuKy : public NhanVien
{
private:
  string _language_certificate;
  int _number_report;

public:
  NhanVienThuKy() : NhanVien() {}
  NhanVienThuKy(const string name, const string address, const string certificate, int reports = 0) : NhanVien(name, address)
  {
    _language_certificate = certificate;
    _number_report = reports;
  }
  ~NhanVienThuKy() {}

  bool is_excellent() const final
  {
    return _number_report >= 12;
  }

  void input_from_keyboard() final
  {
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
  std::istream &input(std::istream &is) final
  {
    string infor;
    const int N = 1024;
    char line[N];

    NhanVien::input(is);

    is.ignore(N, '['); // ignore trash data
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
  std::ostream &output(std::ostream &os) const final
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
  string _department_certificate;
  int _number_idea;

public:
  NhanVienKyThuat() : NhanVien() {}
  NhanVienKyThuat(const string name, const string address, const string certificate, int ideas = 0) : NhanVien(name, address)
  {
    _department_certificate = certificate;
    _number_idea = ideas;
  }
  ~NhanVienKyThuat() {}

  bool is_excellent() const final
  {
    return _number_idea >= 6;
  }

  void input_from_keyboard() final
  {
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
  std::istream &input(std::istream &is) final
  {
    string infor;
    const int N = 1024;
    char line[N];

    NhanVien::input(is);

    is.ignore(N, '['); // ignore trash data
    // certificate
    is.getline(line, N, ']');
    infor = line;
    trim(infor);
    _department_certificate = infor;

    is.ignore(N, '<'); // ignore trash data
    // number
    is >> _number_idea;

    is.ignore(N, '\n');

    return is;
  }
  std::ostream &output(std::ostream &os) const final
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
  string _name;
  string _address;
  vector<NhanVien *> _employees;

public:
  CongTy(const string name) : _name(name), _address()
  {
  }
  CongTy(const string name, const string address) : _name(name), _address(address) {}
  // We do not allow companies to copy each other
  CongTy(const CongTy &other) = delete;
  ~CongTy()
  {
    for (auto &empl : _employees)
    {
      delete empl;
    }
  }

  // let _employee gets ownership over pointer
  void add_empl(NhanVien *nv)
  {
    _employees.push_back(std::move(nv));
  }
  int size() const
  {
    return _employees.size();
  }
  // Display excellent employees to the Terminal
  void display_excellent_employee() const
  {
    int n = _employees.size();
    for (int i = 0; i < n; ++i)
    {
      cout << *_employees[i] << endl;
    }
  }

  friend std::istream &operator>>(std::istream &is, CongTy &company)
  {
    const int N = 1024;
    char line[N];

    while (true)
    {
      string occupation;
      char ch;
      // get occupation data
      is.getline(line, N, ':');
      occupation = line;
      trim(occupation);

      if (is.eof())
      {
        break;
      }
      is.get(ch); // pass ':'
      // ignore space ' '
      if (is.peek() == ' ')
      {
        is.get(ch);
      }

      if (occupation == "nvtk")
      {
        NhanVienThuKy *nv = new NhanVienThuKy();
        is >> *nv;
        company.add_empl(nv);
      }
      else if (occupation == "nvkt")
      {
        NhanVienKyThuat *nv = new NhanVienKyThuat();
        is >> *nv;
        company.add_empl(nv);
      }
      else
      {
        is.getline(line, N, '\n');
      }
    }

    return is;
  }
  // Display employee list to the output file
  friend std::ostream &operator<<(std::ostream &os, const CongTy &company)
  {
    int n = company.size();
    for (int i = 0; i < n; ++i)
    {
      os << *company._employees[i] << endl;
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

  company.add_empl(&nvkt);

  output_file << company;

  input_file.close();
  output_file.close();
}