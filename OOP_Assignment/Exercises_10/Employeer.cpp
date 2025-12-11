#include <iostream>
#include <vector>
#include <string>

using  namespace std;


// Fix the name of this to ip system
class Company {
private:
  std::vector<Catalog*> catalogs;
public:
  Company();
  Company(const Company& other);
  ~Company();

  void add_catalog(const Catalog* catalog);
  void remove_catalog(const int id);

  float getPaymentAmount() const;

  void catalog_infor(const int id) const;
  float get_catalog_payment_amount(const int id) const;
  Catalog* find_catalog(const int id);
};

class Catalog {
  static int  current_id;
private:
  int id;
  string name;
public:
  Catalog() = default;
  ~Catalog();

  void update_name(const  string str);
  int get_id() const;

  virtual float getPaymentAmount() const;
};

// if more  class is added in the future
class Service : public Catalog {

};

class Invoice : public Catalog {
private:
  int amount;
  float price;
public:
  Invoice();
  Invoice(const string str, const int am, const float pr);
  Invoice(const Invoice& other);
  ~Invoice();

  void update_price(const float pr);
  void update_amount(const int am);

  float getPaymentAmount() const final;
};


class Employee : public Catalog {
private:
  string address;
public:
  Employee(const string n, const string add);
  Employee(const Employee& other);
  ~Employee();


  void update_address(const string str);

  virtual float getPaymentAmount() const;
};

class SalariedEmployee : public Employee {
private:
  float weekly_salary;
public:
  SalariedEmployee();
  SalariedEmployee(const SalariedEmployee& other);
  ~SalariedEmployee();


  float getPaymentAmount() const final;
};

class HourlyEmployee : public Employee {
private:
  float hour;
  float base;
public:
  HourlyEmployee();
  HourlyEmployee(const float h, const float am);
  HourlyEmployee(const HourlyEmployee& other);
  ~HourlyEmployee();

  void update_hour(const float h);
  void update_amount(const float b);
  float getPaymentAmount() const final;
};

class CommissionEmployee : public Employee {
private:
  float commission_rate;
  float gross_saled;
public:
  CommissionEmployee();
  CommissionEmployee(const float com, const float saled);
  CommissionEmployee(const CommissionEmployee& other);
  ~CommissionEmployee();


  void update_commission_rate(const float com);
  void update_gross_saled(const float grs);
  float getPaymentAmount() const final;
};