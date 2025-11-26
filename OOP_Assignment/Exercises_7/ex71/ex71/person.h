#ifndef _PERSON_H_
#define _PERSON_H_

#include "array.h"

struct Date
{
  int day, month, year;
};

class Person
{
private:
  static unsigned long long _current_id;

private:
  String _name;
  Date _dob; // Date of Birth
  unsigned long long _ccid;

protected:
  // Only permit for to copy in specific situation such as create an Employee instance
  Person(const Person &person)
  {
    _ccid = person._current_id++;
    _name = person._name;
    _dob = person._dob;
  }

  unsigned long long ccid() const
  {
    return _ccid;
  }

public:
  Person() = delete;
  Person(const String name, const Date date)
  {
    _ccid = _current_id++;
    _name = name;
    _dob = date;
  }
  ~Person() {};

  String name() const
  {
    return _name;
  }
  Date dob() const
  {
    return _dob;
  }

  // We do not Allow user to copy other Person information
  Person &operator=(const Person &) = delete;
};
inline unsigned long long Person::_current_id = 10000000;

#endif