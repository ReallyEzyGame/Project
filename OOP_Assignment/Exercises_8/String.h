#include "Array.h"
#include <string.h>

class String
{
private:
  Array<char> _str;

public:
  String() {};
  String(const char *str) : _str(str, strlen(str)) {}
  String(const int time, const char ch) : _str(time, ch) {}
  //String(const std::initializer_list<char>& list) : _str(list) {}
  String(const String &other)
  {
    _str = other._str;
  }
  ~String() {}

  void push_back(const char ch)
  {
    _str.push_back(ch);
  }
  void pop_back()
  {
    _str.pop_back();
  }

  int size() const
  {
    return _str.size();
  }
  int length() const
  {
    return _str.size();
  }
  int capacity() const
  {
    return _str.capacity();
  }
  bool empty() const
  {
    return _str.empty();
  }

  char operator[](const int idx) const
  {
    return _str[idx];
  }
  char &operator[](const int idx)
  {
    return _str[idx];
  }

  String &operator=(const String other)
  {
    _str = other._str;
    return *this;
  }
  String operator+(const String other)
  {
    int len1 = size();
    int len2 = other.size();
    String consec(len1 + len2, ' ');    // Consecutive String

    for (int i = 0; i < len1; ++i)
    {
      consec[i] = this->operator[](i);
    }
    for (int i = 0; i < len2; ++i)
    {
      consec[i + len1] = other[i];
    }

    return consec;
  }
  bool operator==(const String other) const {
    int max = std::max(size(), other.size());
    int min = std::min(size(), other.size());

    if (max != min) {
      return false;
    }
    else {
      for (int i = 0; i < max; ++i) {
        if (this->operator[](i) != other[i]) {
          return false;
        }
      }

      return true;
    }
  }
  bool operator!= (const String other) const {
    return !(*this == other);
  }
  bool operator< (const String other) const {

  }
  bool operator>(const String other) const {
  }
  bool operator<=(const String other) const {
    
  }
  bool operator>= (const String other) const {

  }
  Array<char>::Iterator begin() const {
    return &_str[0];
  }
  Array<char>::Iterator end() const {
    return (&_str[0] + size());
  }


  friend std::ostream& operator <<(std::ostream& os, const String& str) {
    for (char it : str) {
      os << it;
    }
    return os;
  }
  friend std::istream& operator >>(std::istream& is, String& str) {
    char ch;
    while (is.get(ch)) {
      if (ch == '\0' || ch == '\n') {
        break;
      }
      str.push_back(ch);
    }
    return is;
  }
};