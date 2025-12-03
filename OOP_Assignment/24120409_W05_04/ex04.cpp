#include <iostream>
#include <string.h>
#include <exception>

template <class T>
class SLList
{
private:
  struct Node
  {
    T _data;
    Node *_pNext;
  };

  Node *_pHead, *_pTail;
  int _size;

  Node *create_node(const T);
  void Clear();

public:
  class iterator;

  SLList();
  SLList(const SLList<T> &);
  ~SLList();

  void insert_head(const T);
  void push_back(const T);
  void remove_head();
  void pop_back();

  iterator begin() const;
  iterator end() const;
  int size() const;

  SLList &operator=(const SLList &);
};

class MyString
{
private:
  SLList<char> str;

public:
  MyString();
  MyString(const char *);
  MyString(const MyString &);
  ~MyString();

  // if False, only take 1 delim char out where the  other delim character behind will turn into space char ' '
  // if True, remove all the  delim and seperate each string  between them
  SLList<MyString> Split(SLList<char> delim, const bool left_space = false);
  void push_back(const char);
  void pop_back();

  MyString &operator=(const MyString);
  MyString operator+(const MyString);

  friend std::ostream &operator<<(std::ostream &os, const MyString str);
};


// Implement SLList class
template <class T>
class SLList<T>::iterator
{
public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using reference = T&;
  using pointer = T*;

private:
  Node *current_node;

  iterator(Node *node) : current_node(node) {}
  friend class SLList<T>;

public:
  iterator() : current_node(nullptr) {}

  reference operator*() const
  {
    if (!current_node)
    {
      throw std::out_of_range("Dereferncing end() or null iterator");
    }
    return current_node->_data;
  }
  pointer operator->() const
  {
    if (!current_node)
    {
      throw std::out_of_range("Accessing member via end() or null iterator");
    }
    return &(current_node->_data);
  }
  iterator operator++()
  {
    if (!current_node)
    {
      throw std::out_of_range("Incrementing end() or null iterator");
    }
    current_node = current_node->_pNext;
    return *this;
  }
  iterator operator++(int)
  {
    if (!current_node)
    {
      throw std::out_of_range("Incrementing end() or null iterator");
    }

    iterator tmp = current_node;
    current_node = current_node->_pNext;

    return tmp;
  }
  bool operator==(const iterator &other) const
  {
    return current_node == other.current_node;
  }
  bool operator!=(const iterator &other) const
  {
    return !(current_node == other.current_node);
  }
};

template <class T>
SLList<T>::SLList()
{
  _pHead = nullptr;
  _pTail = nullptr;
  _size = 0;
}
template <class T>
SLList<T>::SLList(const SLList &other)
{
  _pHead = create_node(other._pHead->_data);

  Node *tmp = other._pHead->_pNext;
  Node *front = _pHead, *add;

  while (tmp)
  {
    add = create_node(tmp->_data);

    front->_pNext = add;
    front = add;

    tmp = tmp->_pNext;
  }
  _pTail = add;
  _size = other._size;
}
template<class T>
SLList<T>::~SLList() {
  Clear();
}



template <class T>
typename SLList<T>::Node *SLList<T>::create_node(const T val)
{
  Node *add = new Node;
  add->_data = val;
  add->_pNext = nullptr;

  return add;
}

template <class T>
void SLList<T>::Clear()
{
  Node *tmp = _pHead, *del;
  while (tmp)
  {
    del = tmp;
    tmp = tmp->_pNext;

    delete del;
  }

  _pHead = _pTail = nullptr;
  _size = 0;
}
template <class T>
void SLList<T>::insert_head(const T val)
{
  Node *add = create_node(val);
  if (_size == 0)
  {
    _pHead = _pTail = add;
  }
  else
  {
    add->_pNext = _pHead;
    _pHead = add;
  }
  _size++;
}
template <class T>
void SLList<T>::push_back(const T val)
{
  Node *add = create_node(val);
  if (_size == 0)
  {
    _pHead = _pTail = add;
  }
  else
  {
    _pTail->_pNext = add;
    _pTail = add;
  }
  _size++;
}
template <class T>
void SLList<T>::remove_head()
{
  Node *del = _pHead;

  if (_size == 0)
  {
    return;
  }
  if (_size == 1)
  {
    _pHead = _pTail = nullptr;
  }
  else
  {
    _pHead = _pHead->_pNext;
  }

  --_size;
  delete del;
}
template <class T>
void SLList<T>::pop_back()
{
  Node *del = _pHead;

  if (_size == 0)
  {
    return;
  }
  if (_size == 1)
  {
    _pHead = _pTail = nullptr;
  }
  else
  {
    Node *tmp = _pHead;
    while (tmp->_pNext->_pNext)
    {
      tmp = tmp->_pNext;
    }
    tmp->_pNext = nullptr;
    _pTail = tmp;
  }

  --size;
  delete del;
}

template <class T>
typename SLList<T>::iterator SLList<T>::begin() const
{
  return iterator(_pHead);
}
template <class T>
typename SLList<T>::iterator SLList<T>::end() const
{
  return iterator(nullptr);
}
template <class T>
int SLList<T>::size() const
{
  return _size;
}

template <class T>
SLList<T> &SLList<T>::operator=(const SLList<T> &list)
{
  Clear();

  for (T val : list)
  {
    push_back(val);
  }

  _size = list._size;
  return *this;
}



// IMPLEMENT MYSTRING CLASS
MyString::MyString() {}
MyString::MyString(const char *str)
{
  int len = strlen(str);

  for (int i = 0; i < len; ++i)
  {
    this->str.push_back(str[i]);
  }
}
MyString::MyString(const MyString &other)
{
  str = other.str;
}
MyString::~MyString() {}

SLList<MyString> MyString::Split(SLList<char> delim, const bool erase_space)
{
  bool is_first_delim = false;    // pass the delim char or record it as space ' '
  MyString tmp; // contains chars for each seprate time
  SLList<MyString> seperate;

  for (char ch : str)
  {
    bool flag = false;
    // check if the char belongs to delim set
    for (char bound : delim)
    {
      if (ch == bound)
      {
        flag = true;
      }
    }

    if (!flag) {
      tmp.str.push_back(ch);
    }
    else {
      if (tmp.str.size() > 0) 
      {
        seperate.push_back(tmp);
        tmp = MyString();
        is_first_delim  = true;
      }
      else if (is_first_delim && !erase_space){
        seperate.push_back(MyString(" "));
        is_first_delim = false;
      }
    }
  }

  return seperate;
}

MyString &MyString::operator=(const MyString other)
{
  str = other.str;
  return *this;
}
MyString MyString::operator+(const MyString other)
{
  MyString consecutive;
  for (char ch : str)
  {
    consecutive.str.push_back(ch);
  }
  for (char ch : other.str)
  {
    consecutive.str.push_back(ch);
  }

  return consecutive;
}

std::ostream &operator<<(std::ostream &os, const MyString str)
{
  for (char ch : str.str)
  {
    os << ch;
  }
  return os;
}

MyString operator+(const char *str, const MyString &ms) {
  return MyString(str) + ms;
}


int main()
{
  MyString ms1("abcdsf");
  MyString ms2 = "_____" + ms1;
  MyString ms3 = ms2 + ms1;

  std::cout << "ms1= " << ms1 << std::endl;
  std::cout << "ms2= " << ms2 << std::endl;
  std::cout << "ms3= " << ms3 << std::endl;

  MyString ms = "a,b,c;d.r;.,h;e,w__u,t.f;j_..";
  SLList<char> arrChar;
  arrChar.push_back(',');
  arrChar.push_back('.');
  arrChar.push_back(';');

  SLList<MyString> vMs = ms.Split(arrChar, false);

  std::cout << "Split: " << std::endl;
  for (SLList<MyString>::iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
  {
    std::cout << *itMS << " ";
  }

  std::cout << std::endl
            << "size= " << vMs.size() << std::endl
            << std::endl;

  vMs = ms.Split(arrChar, true);
  std::cout << "Split with erase empty:" << std::endl;
  for (SLList<MyString>::iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
  {
    std::cout << *itMS << " ";
  }
  std::cout << std::endl
            << "size= " << vMs.size() << std::endl
            << std::endl;

  system("pause");
  return 0;
}