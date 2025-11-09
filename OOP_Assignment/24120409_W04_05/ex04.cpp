#include <iostream>
#include <random>
#include <exception>
#include <cstring>


template <typename T>
class Node
{
private:
    Node *next;
    T data;

public:
    Node();
    Node(const T);
    // We only copy the data value of other Node and will not copy the next Node to avoid 2 Node pointing to 1 Node
    Node(const Node *&);
    ~Node() = default;

    void SetData(const T);
    void SetNextNode(Node<T> *);

    T &GetData();
    Node<T> *GetNextNode();
};


template <typename T>
Node<T>::Node()
{
    data = T();
    next = nullptr;
}
template <typename T>
Node<T>::Node(const T val)
{
    data = val;
    next = nullptr;
}
template <typename T>
Node<T>::Node(const Node *&other)
{
    data = other->data;
    next = nullptr;
}

template <typename T>
T &Node<T>::GetData()
{
    return data;
}
template <typename T>
Node<T> *Node<T>::GetNextNode()
{
    return next;
}

template <typename T>
void Node<T>::SetData(const T val)
{
    data = val;
}
template <typename T>
void Node<T>::SetNextNode(Node<T> *other)
{
    next = other;
}





class CString
{
private:
    char *_mang;

public:
    CString();
    CString(const char *);
    CString(const CString &);
    ~CString();

    CString &operator++();
    CString operator++(int);

    char &operator[](const int &);
    CString &operator=(const CString &);
    friend std::ostream &operator<<(std::ostream &, const CString &);
};

CString::CString()
{
    _mang = nullptr;
}
CString::CString(const char *str)
{
    int len = strlen(str);
    _mang = new char[len + 1];

    strcpy_s(_mang, len + 1, str);
}
CString::CString(const CString &cstr) : CString(cstr._mang) {}
CString::~CString()
{
    if (_mang)
        delete _mang;
}
CString &CString::operator++()
{
    if (_mang != nullptr)
    {
        int len = strlen(_mang);
        _mang[len - 1]++;
    }
    return *this;
}
CString CString::operator++(int)
{
    CString tmp = *this;
    if (_mang != nullptr)
    {
        int len = strlen(_mang);
        _mang[len - 1]++;
    }
    return tmp;
}
char &CString::operator[](const int &i)
{
    int len = strlen(_mang);
    if (i < 0 || i >= len)
    {
        throw std::exception("Out of Range");
    }
    return _mang[i];
}
CString &CString::operator=(const CString &cs)
{
    if (_mang != nullptr)
    {
        delete[] _mang;
    }
    int len = strlen(cs._mang) + 1;
    _mang = new char[len];
    strcpy_s(_mang, len, cs._mang);

    return *this;
}
std::ostream &operator<<(std::ostream &os, const CString &cs)
{
    os << cs._mang;
    return os;
}



template <typename T>
class LinkedList
{
private:
  Node<T> *head, *tail;
  int size;
  static Node<T> *CreateNode(const T);

public:
  LinkedList();
  LinkedList(const T);
  LinkedList(const LinkedList<T> &);
  ~LinkedList();

  void AddHead(const T);
  void AddTail(const T);
  void RemoveHead();
  void RemoveTail();

  int getSize() const;

  T &operator[](const int);
  LinkedList<T>& operator=(LinkedList<T>);
};


template <typename T>
LinkedList<T>::LinkedList()
{
  head = tail = nullptr;
  size = 0;
}
template <typename T>
LinkedList<T>::LinkedList(const T val)
{
  head = new Node<T>(val);
  tail = head;
  size = 1;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
  head = tail = new Node<T>(list.head->GetData());
  Node<T> *tmp = list.head->GetNextNode(), *last;

  while (tmp)
  {
    last = tail;
    tail = new Node<T>(tmp->GetData());

    last->SetNextNode(tail);
    tmp = tmp->GetNextNode();
  }
  size = list.size;
}
template <typename T>
LinkedList<T>::~LinkedList()
{
  Node<T> *tmp = head;
  Node<T> *del;

  while (tmp)
  {
    del = tmp;
    tmp = tmp->GetNextNode();

    delete del;
  }
}


template <typename T>
Node<T> *LinkedList<T>::CreateNode(const T val)
{
  Node<T> *add = new Node<T>(val);
  return add;
}
template <typename T>
void LinkedList<T>::AddHead(const T val)
{
  Node<T> *add = CreateNode(val);

  if (size != 0)
  {
    add->SetNextNode(head);
  }
  else
  {
    tail = add;
  }

  head = add;
  size++;
}
template <typename T>
void LinkedList<T>::AddTail(const T val)
{
  Node<T> *add = CreateNode(val);

  if (size != 0)
  {
    tail->SetNextNode(add);
  }
  else
  {
    head = add;
  }

  tail = add;
  size++;
}
template <typename T>
int LinkedList<T>::getSize() const
{
  return size;
}


template <typename T>
void LinkedList<T>::RemoveHead()
{
  if (size == 0)
  {
    return;
  }

  if (head == tail)
  {
    delete head;
    head = tail = nullptr;
  }
  else
  {
    Node<T> *del = head;
    head = head->GetNextNode();

    delete del;
  }
  size--;
}
template <typename T>
void LinkedList<T>::RemoveTail()
{
  if (size == 0)
  {
    return;
  }

  if (head == tail)
  {
    delete tail;
    head = tail = nullptr;
  }
  else
  {
    Node<T> *del = head, *new_tail = head;
    while (del->GetNextNode())
    {
      new_tail = del;
      del = del->GetNextNode();
    }
    tail = new_tail;
    tail->SetNextNode(nullptr);

    delete del;
  }
  size--;
}


template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> other) {
  Node<T>* tmp = other.head;
  // Xoá bỏ danh sách cũ
  while (size > 0) {
    this->RemoveHead();
  }

  // copy lại, tạo thành danh sách mới
  while (tmp) {
    this->AddTail(tmp->GetData());
    tmp = tmp->GetNextNode();
  }

  return *this;
}
template <typename T>
T &LinkedList<T>::operator[](const int idx)
{
  if (idx < 0)
  {
    throw std::exception("Out of List Range");
  }
  if (idx >= size)
  {
    throw std::exception("Out of List Range");
  }

  Node<T> *tmp = head;
  int i = 0;
  while (tmp)
  {
    if (idx == i)
    {
      break;
    }
    tmp = tmp->GetNextNode();
    i++;
  }

  return tmp->GetData();
}

template <typename T>
std::ostream &operator<<(std::ostream &os, LinkedList<T> &ll)
{
    int N = ll.getSize();
    for (int i = 0; i < N; ++i)
    {
        os << ll[i] << ", ";
    }
    return os;
}

int main()
{
    srand((unsigned int)(time(NULL)));

    const int maxV = 1000, iTest = 2;
    int n = 5 + rand() % 10;

    LinkedList<int> ll;
    for (int i = 0; i < n; ++i)
    {
        if (rand() % 2 == 0)
        {
            ll.AddHead(rand() % maxV);
        }
        else
        {
            ll.AddTail(rand() % maxV + maxV);
        }
    }

    std::cout << ll << std::endl;

    ll[iTest] = -123;
    ll[iTest + 2] = 9876;

    ll.RemoveHead();
    ll.RemoveTail();
    std::cout << "After Removing: " << std::endl;
    std::cout << ll << std::endl;



    LinkedList<CString> llCS;
    llCS.AddTail(CString("cstring-1"));
    llCS.AddTail(CString("cstring-2"));
    llCS.AddTail(CString("cstring-3"));

    std::cout << "List CString: " << llCS << std::endl;
    llCS[iTest] = CString("new CString");
    std::cout << "List CString Changed: " << std::endl << llCS << std::endl;

    system("pause");
    return 0;
}