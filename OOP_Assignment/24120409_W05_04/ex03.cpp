#include <iostream>
#include <exception>
#include <algorithm>
#include <string.h>

template <class T>
class SLList
{
private:
  struct Node
  {
    T _info;
    Node *_pNext;
  };

  Node *_pHead, *_pTail;
  int _n;

  static Node *CreateNode(const T &value)
  {
    Node *node = new Node{value, nullptr};
    return node;
  }

public:
  class Iterator;
  SLList();
  ~SLList();

  void AddHead(const T &);
  void AddTail(const T &);
  void RemoveHead();
  void RemoveTail();
  void Clear();

  // // Insert to the back of a Node
  // void insert(const Node* node, const T val);
  // void insert(const Iterator node, const T val);
  // Tail Insert
  void push_back(const T val);
  int size() const;

  // Iterator Access
  Iterator begin()
  {
    return Iterator(_pHead);
  }
  Iterator end()
  {
    return Iterator(nullptr);
  }

  T operator[](const int idx) const;
  T &operator[](const int idx);
  SLList<T> &operator=(const SLList<T> &list);
  // template <class T>
  // friend std::ostream &operator<<(std::ostream &os, const SLList<T> &ll)
  // {
  //   SLList<T>::Node *node = ll._pHead;
  //   while (node != nullptr)
  //   {
  //     os << node->_info << ", ";
  //     node = node->_pNext;
  //   }
  //   return os;
  // }
};

template <class T>
SLList<T>::SLList()
{
  _pHead = _pTail = nullptr;
  _n = 0;
}
template <class T>
SLList<T>::~SLList()
{
  SLList<T>::Node *node = _pHead;
  while (node)
  {
    SLList<T>::Node *del = node;
    node = node->_pNext;
    delete del;
  }
}

template <class T>
void SLList<T>::Clear()
{
  Node *node = _pHead;
  while (node)
  {
    Node *del = node;
    node = node->_pNext;

    delete del;
  }

  _n = 0;
  _pHead = _pTail = nullptr;
}

template <class T>
void SLList<T>::AddHead(const T &value)
{
  Node *node = CreateNode(value);
  if (node == nullptr)
  {
    return;
  }
  if (_pHead == nullptr)
  {
    _pHead = _pTail = node;
  }
  else
  {
    node->_pNext = _pHead;
    _pHead = node;
  }
  _n++;
}
template <class T>
void SLList<T>::AddTail(const T &value)
{
  Node *node = CreateNode(value);
  if (node == nullptr)
  {
    return;
  }
  else if (_pTail == nullptr)
  {
    _pHead = _pTail = node;
  }
  else
  {
    _pTail->_pNext = node;
    _pTail = node;
  }
  _n++;
}
template <class T>
void SLList<T>::RemoveHead()
{
  Node *node = _pHead;
  if (_n == 0)
  {
    return;
  }

  if (_n == 1)
  {
    _pHead = _pTail = nullptr;
  }
  else
  {
    _pHead = _pHead->_pNext;
  }

  delete node;
  _n--;
}
template <class T>
void SLList<T>::RemoveTail()
{
  Node *node = _pHead;
  if (_n == 0)
  {
    return;
  }

  if (_n == 1)
  {
    _pHead = _pTail = nullptr;

    _n--;
    delete node;
  }
  else
  {
    while (node->_pNext->_pNext)
    {
      node = node->_pNext;
    }

    _pTail = node;
    _pTail->_pNext = nullptr;
    node = node->_pNext;

    _n--;
    delete node;
  }
}

template <class T>
int SLList<T>::size() const
{
  return _n;
}

template <class T>
void SLList<T>::push_back(const T val)
{
  AddTail(val);
}

template <class T>
SLList<T> &SLList<T>::operator=(const SLList<T> &list)
{

  Clear();

  Node *tmp = list._pHead;
  while (tmp)
  {
    AddTail(tmp->_info);
    tmp = tmp->_pNext;
  }
  return *this;
}
template <class T>
T &SLList<T>::operator[](const int idx)
{
  if (idx < 0 || _n <= idx)
  {
    throw std::out_of_range("Out of Range");
  }

  Node *tmp = _pHead;
  int i = 0;
  while (i < idx)
  {
    tmp = tmp->_pNext;
    i++;
  }

  return tmp->_info;
}
template <class T>
T SLList<T>::operator[](const int idx) const
{
  if (idx < 0 || _n <= idx)
  {
    throw std::out_of_range("Out of Range");
  }

  Node *tmp = _pHead;
  int i = 0;
  while (i < idx)
  {
    tmp = tmp->_pNext;
    i++;
  }

  return tmp->_info;
}

template <class T>
class SLList<T>::Iterator
{
public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

private:
  Node *current_node;
  Iterator(Node *node) : current_node(node) {}
  friend class SLList<T>;

public:
  Iterator() : current_node(nullptr) {}

  reference operator*() const
  {
    if (!current_node)
    {
      throw std::out_of_range("Dereferencing end() or null iterator");
    }

    return current_node->_info;
  }
  pointer operator->() const
  {
    if (!current_node)
    {
      throw std::out_of_range("Accessing member via end() orr null iterator");
    }
    return &(current_node->_info);
  }

  Iterator &operator++()
  {
    if (current_node)
    {
      current_node = current_node->_pNext;
    }
    else
    {
      throw std::out_of_range("Incrementing end() or null iterator");
    }
    return *this;
  }
  Iterator &operator++(int)
  {
    if (!current_node)
    {
      throw std::out_of_range("Incrementing end() or null iterator");
    }

    Iterator tmp = *this;
    current_node = current_node->_pNext;
    return tmp;
  }
  bool operator==(const Iterator other) const
  {
    return current_node == other.current_node;
  }
  bool operator!=(const Iterator other) const
  {
    return !(*this == other);
  }
};

class SoNguyenLon
{
private:
  SLList<unsigned char> lCS;
  void Pow10(const int &n);

public:
  SoNguyenLon(void);
  SoNguyenLon(const int &cs, const int &scs);
  SoNguyenLon(const unsigned long long &n);
  SoNguyenLon(const SoNguyenLon &snl);
  SoNguyenLon(const char *str);
  ~SoNguyenLon(void);

  int SoCS();

  SoNguyenLon operator+(SoNguyenLon snl);
  SoNguyenLon operator-(SoNguyenLon snl);
  SoNguyenLon operator*(SoNguyenLon snl);

  bool operator>(const SoNguyenLon &snl);
  const SoNguyenLon &operator=(const SoNguyenLon &snl);
  SoNguyenLon &operator+=(SoNguyenLon snl);

  friend SoNguyenLon operator+(const unsigned int &n, const SoNguyenLon &snl);
  friend SoNguyenLon operator-(const unsigned int &n, const SoNguyenLon &snl);
  friend std::ostream &operator<<(std::ostream &os, const SoNguyenLon &snl);
};

SoNguyenLon::SoNguyenLon(void)
{
  lCS.push_back(0);
}
SoNguyenLon::SoNguyenLon(const int &cs, const int &scs)
{
  int csR = cs;
  // Clamp
  if (csR < 1)
  {
    csR = 1;
  }
  if (csR > 9)
  {
    csR = 9;
  }

  int soCS = abs(scs);
  if (soCS > 9)
  {
    soCS = 9;
  }

  for (int i = 0; i < soCS; ++i)
  {
    lCS.push_back(csR);
  }
}
SoNguyenLon::SoNguyenLon(const unsigned long long &n)
{
  unsigned long long temp = n;
  while (temp > 0)
  {
    lCS.AddTail(temp % 10);
    temp /= 10;
  }
}
SoNguyenLon::SoNguyenLon(const SoNguyenLon &snl)
{
  lCS = snl.lCS;
}
SoNguyenLon::SoNguyenLon(const char *str)
{
  int len = strlen(str);
  for (int i = 0; i < len; ++i)
  {
    lCS.AddHead(str[i] - '0');
  }
}
SoNguyenLon::~SoNguyenLon() {}

int SoNguyenLon::SoCS()
{
  return lCS.size();
}
void SoNguyenLon::Pow10(const int &n)
{
  for (int i = 0; i < n; ++i)
  {
    lCS.AddHead(0);
  }
}
bool SoNguyenLon::operator>(const SoNguyenLon &snl)
{
  if (lCS.size() > snl.lCS.size())
  {
    return true;
  }
  if (lCS.size() < snl.lCS.size())
  {
    return false;
  }

  for (int i = lCS.size() - 1; i >= 0; --i)
  {
    if (lCS[i] == snl.lCS[i])
    {
      continue;
    }

    if (lCS[i] > snl.lCS[i])
    {
      return true;
    }
    return false;
  }

  return false;
}

const SoNguyenLon &SoNguyenLon::operator=(const SoNguyenLon &snl)
{
  lCS = snl.lCS;
  return *this;
}
SoNguyenLon &SoNguyenLon::operator+=(SoNguyenLon snl)
{
  (*this) = (*this) + snl;
  return *this;
}
SoNguyenLon SoNguyenLon::operator+(SoNguyenLon snl)
{
  SoNguyenLon snlKQ;
  snlKQ.lCS.Clear();

  SoNguyenLon *snlSCSMax = (SoCS() > snl.SoCS()) ? this : &snl;
  SoNguyenLon *snlSCSMin = (SoCS() < snl.SoCS()) ? this : &snl;
  int carry = 0, tmp;
  for (int i = 0; i < snlSCSMin->SoCS(); ++i)
  {
    tmp = lCS[i] + snl.lCS[i] + carry;

    snlKQ.lCS.push_back(tmp % 10);
    carry = tmp / 10;
  }
  for (int i = snlSCSMin->SoCS(); i < snlSCSMax->SoCS(); ++i)
  {
    tmp = snlSCSMax->lCS[i] + carry;
    snlKQ.lCS.push_back(tmp % 10);
    carry = tmp / 10;
  }
  if (carry > 0)
  {
    snlKQ.lCS.push_back(1);
  }
  return snlKQ;
}
SoNguyenLon SoNguyenLon::operator-(SoNguyenLon snl)
{
  SoNguyenLon snlKQ;
  if (snl > *this)
  {
    return snlKQ;
  }
  else
  {
    snlKQ.lCS.Clear();
  }

  SoNguyenLon *snlSCSMax = this;
  SoNguyenLon *snlSCSMin = &snl;
  int carry = 0, tmp;

  for (int i = 0; i < snlSCSMin->SoCS(); ++i)
  {
    tmp = snlSCSMax->lCS[i] - (snlSCSMin->lCS[i] + carry);

    snlKQ.lCS.push_back(tmp >= 0 ? tmp : 10 + tmp);
    carry = tmp < 0 ? 1 : 0;
  }
  for (int i = snlSCSMin->SoCS(); i < snlSCSMax->SoCS(); ++i)
  {
    tmp = snlSCSMax->lCS[i] - carry;

    snlKQ.lCS.push_back(tmp >= 0 ? tmp : 10 + tmp);
    carry = tmp < 0 ? 1 : 0;
  }

  while (snlKQ.lCS.size() > 1 && snlKQ.lCS[snlKQ.lCS.size() - 1] ==  0) {
    snlKQ.lCS.RemoveTail();
  }


  return snlKQ;
}
SoNguyenLon SoNguyenLon::operator*(SoNguyenLon snl)
{
  SoNguyenLon snlKQ, *psnlTemp;
  SoNguyenLon *snlSCSMax = (SoCS() > snl.SoCS()) ? this : &snl;
  SoNguyenLon *snlSCSMin = (SoCS() < snl.SoCS()) ? this : &snl;
  int carry = 0, temp;

  for (int i = 0; i < snlSCSMin->SoCS(); ++i)
  {
    psnlTemp = new SoNguyenLon;
    psnlTemp->lCS.Clear();
    carry = 0;

    for (int j = 0; j < snlSCSMax->SoCS(); ++j)
    {
      temp = snlSCSMin->lCS[i] * snlSCSMax->lCS[j] + carry;

      psnlTemp->lCS.push_back(temp % 10);
      carry = temp / 10;
    }

    if (carry > 0)
    {
      psnlTemp->lCS.push_back(carry);
    }

    psnlTemp->Pow10(i);
    snlKQ += *psnlTemp;
    delete psnlTemp;
  }
  return snlKQ;
}
SoNguyenLon operator+(const unsigned int &n, const SoNguyenLon &snl)
{
  return SoNguyenLon(n) + snl;
}
SoNguyenLon operator-(const unsigned int &n, const SoNguyenLon &snl)
{
  return SoNguyenLon(n) - snl;
}
SoNguyenLon operator*(const unsigned int &n, const SoNguyenLon &snl)
{
  return SoNguyenLon(n) * snl;
}


std::ostream &operator<<(std::ostream &os, const SoNguyenLon &snl)
{
  for (int i = snl.lCS.size() - 1; i >= 0; --i)
  {
    os << (int)snl.lCS[i];
  }

  return os;
}

int main()
{
  const int iTest = 78912;
  SoNguyenLon snl1(123);
  SoNguyenLon snl2(40000);

  std::cout << snl1 << " + " << snl2 << " = ";
  std::cout << (snl1 + snl2) << std::endl;

  std::cout << snl1 << " * " << snl2 << " = ";
  std::cout << (snl1 * snl2) << std::endl;

  std::cout << snl1 << " - " << snl2 << " = ";
  std::cout << (snl1 - snl2) << std::endl;

  std::cout << snl2 << " - " << snl1 << " = ";
  std::cout << (snl2 - snl1) << std::endl;

  std::cout << iTest << " - " << snl2 << " = ";
  std::cout << (iTest - snl2) << std::endl;

  system("pause");
  return 0;
}