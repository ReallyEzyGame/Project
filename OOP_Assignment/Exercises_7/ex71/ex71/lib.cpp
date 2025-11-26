#include "lib.h"

Company::Employee::Employee(const Person &person) : Person(person)
{
  _id = _current_id++;
  _salary = 5000000;
  _bonus = 0.075;
}
Company::Employee::~Employee() {};

int Company::Employee::id() const
{
  return _id;
}
int Company::Employee::bonus() const
{
  return _bonus;
}
int Company::Employee::baseSalary() const
{
  return _salary;
}
void Company::Employee::updateBonus(const float value)
{
  _bonus = std::abs(value);
}
void Company::Employee::updateBaseSalary(const int value)
{
  _salary = std::abs(value);
}

Company::Engineer::Engineer(const Person &person) : Employee(person)
{
  _over_time = 0;
}
Company::Engineer::Engineer(const Employee &empl) : Employee(empl)
{
  _over_time = 0;
}
Company::Engineer::Engineer(const Person &person, const int time) : Employee(person)
{
  _over_time = std::abs(time);
}
Company::Engineer::Engineer(const Employee &empl, const int time) : Employee(empl)
{
  _over_time = std::abs(time);
}
Company::Engineer::~Engineer() {};

int Company::Engineer::overTime() const
{
  return _over_time;
}
void Company::Engineer::updateOverTime(const int time)
{
  _over_time = std::abs(time);
}

int Company::Engineer::salary() const
{
  return _salary + (_over_time * bonus());
}
String Company::Engineer::job() const
{
  return "Engineer";
}
String Company::Engineer::describe() const
{
  return "SoftWare Engineering of Tao-Work One Man Company";
}



Company::Manager::Manager(const Person &person) : Employee(person) {}
Company::Manager::Manager(const Employee &empl) : Employee(empl) {}
Company::Manager::~Manager(){};

int Company::Manager::teamSize() const
{
  return employees.size();
}
void Company::Manager::addEmpl(const int id)
{
  // Must have a condition check whether the employee is a staff of the company
  employees.push_back(id);
}
void Company::Manager::ereaseEmply(const int id)
{
  int n = employees.size();

  for (int i = 0; i < n; ++i)
  {
    if (employees[i] == id)
    {
      std::swap(employees[i], employees[n - 1]);
      employees.pop_back();
      break;
    }
  }
}

int Company::Manager::salary() const
{
  return _salary + (employees.size() * bonus());
}
String Company::Manager::job() const
{
  return "Manager";
}
String Company::Manager::describe() const
{
  return "Manger of Tao-Work One Man Company";
}



Company::Company(const String name)
{
  _id = _current_id++;
  _name = name;
}
Company::Company(const String name, const Array<Employee *> list)
{
  _id = _current_id++;
  _name = name;

  // Lack of Copy Employee list
}
Company::Company(const Company &other)
{
  _id = _current_id++;
  _name = other._name;

  // Lack of Copy Employee list
}
Company::~Company()
{
  int n = _employees.size();
  // Discard Employee information
  for (int i = 0; i < n; ++i)
  {
    delete _employees[i];
  }
}

int Company::size() const
{
  return _employees.size();
}
int Company::totalSalary() const
{
  int n = _employees.size();
  int total = 0;

  for (int i = 0; i < n; ++i)
  {
    total += _employees[i]->salary();
  }

  return total;
}
const Company::Employee *Company::findEmpl(const int id) const
{
  int n = _employees.size();
  for (int i = 0; i < n; ++i)
  {
    if (_employees[i]->id() == id)
    {
      return _employees[i];
    }
  }
  // Return Non-exist employee ( sacre-crown) for better handle
  return nullptr;
}

// 1 : Manager, 2 : Engineer
void Company::addEmpl(const Person &person, int job_id)
{
  Employee *empl;
  switch (job_id)
  {
  case 1:
    empl = new Manager(person);
    break;
  case 2:
    empl = new Engineer(person);
    break;
  default:
    throw std::out_of_range("Bad Job ID");
    return;
  }

  _employees.push_back(empl);
}
void Company::eraseEmpl(const int id)
{
  int n = _employees.size();
  for (int i = 0; i < n; ++i)
  {
    if (_employees[i]->id() == id)
    {
      std::swap(_employees[i], _employees[n - 1]);

      delete _employees[n - 1];
      _employees.pop_back();

      break;
    }
  }
}

std::ostream &operator<<(std::ostream &os, const Company &company)
{
  for (int i = 0; i < company.size(); ++i)
  {
    os << company._employees[i]->id() << std::endl;
    os << company._employees[i]->name() << std::endl;
    os << company._employees[i]->dob().day << '/' << company._employees[i]->dob().month << '/' << company._employees[i]->dob().year << std::endl;
    os << company._employees[i]->job() << std::endl;
    std::cout << "------------------" << std::endl;
  }
  return os;
}
