#include <iostream>
#include <exception>
#include <cstring>
#include <math.h>

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



// the Number will be saved in the order as same as the order in mathematic notation
// Big Number only handles and contains non-negative number
class SoNguyenLon
{
private:
  LinkedList<char> dayso;

public:
  SoNguyenLon();
  SoNguyenLon(int);
  // construct a big number with x  n times
  SoNguyenLon(const int, const int);
  SoNguyenLon(SoNguyenLon &);
  ~SoNguyenLon() = default;


  int DoDai() const;


  char &operator[](const int);
  SoNguyenLon& operator=(SoNguyenLon);
  SoNguyenLon operator+(SoNguyenLon );
  SoNguyenLon operator+(int);
  // Chỉ làm việc vói phép trừ mà kết quả lớn hơn hoặc bằng 0
  SoNguyenLon operator-(SoNguyenLon);
  SoNguyenLon operator*(SoNguyenLon);
};


SoNguyenLon::SoNguyenLon() : dayso() {}
SoNguyenLon::SoNguyenLon(int val)
{
  int len = floor(log10(val)) + 1;
  int i = 1;
  while (i <= len)
  {
    dayso.AddHead(val % 10 + '0');
    
    val /= 10;
    i++;
  }
}
SoNguyenLon::SoNguyenLon(const int x, const int n) : dayso(LinkedList<char>())
{
  if (n >= 0 && x >= 1)
  {
    for (int i = 1; i <= n; ++i)
    {
      dayso.AddHead(x + '0');
    }
  }
}
SoNguyenLon::SoNguyenLon(SoNguyenLon& number)
{
  int N = number.DoDai();
  for (int i = 0; i < N; ++i)
  {
    dayso.AddTail(number[i]);
  }
}


int SoNguyenLon::DoDai() const
{
  return dayso.getSize();
}


char &SoNguyenLon::operator[](const int idx)
{
  if (idx < 0 || idx >= dayso.getSize())
  {
    throw(10);
  }

  return dayso[idx];
}
SoNguyenLon& SoNguyenLon::operator=(SoNguyenLon sk) {
  dayso = sk.dayso;
  return *this;
}
SoNguyenLon SoNguyenLon::operator+(SoNguyenLon sk)
{
  SoNguyenLon kq;
  int N1 = this->DoDai(), N2 = sk.DoDai();
  int i1 = N1 - 1, i2 = N2 - 1;
  bool nho = false;

  while (i1 >= 0 || i2 >= 0)
  {
    int gia_tri1 = i1 >= 0 ? (*this)[i1] - '0' : 0;
    int gia_tri2 = i2 >= 0 ? sk[i2] - '0' : 0;
    int gia_tri = gia_tri1 + gia_tri2 + nho;

    if (gia_tri >= 10)
    {
      nho = true;
      gia_tri -= 10;
    }
    else
    {
      nho = false;
    }

    kq.dayso.AddHead(gia_tri + '0');
    --i1;
    --i2;
  }
  if (nho)
    kq.dayso.AddHead('1');
  return kq;
}
std::ostream &operator<<(std::ostream &os, SoNguyenLon &snl);


SoNguyenLon SoNguyenLon::operator+(const int so)
{
  SoNguyenLon snl(so);
  return *this + snl;
}
SoNguyenLon SoNguyenLon::operator-(SoNguyenLon sk)
{
  SoNguyenLon kq;
  int N1 = this->DoDai(), N2 = sk.DoDai();
  int i1 = N1 - 1, i2 = N2 - 1;
  bool nho = false;

  while (i1 >= 0 || i2 >= 0)
  {
    int gia_tri1 = i1 >= 0 ? (*this)[i1] - '0' : 0;
    int gia_tri2 = i2 >= 0 ? sk[i2] - '0' : 0;
    int gia_tri = gia_tri1 - gia_tri2 - nho;

    if (gia_tri < 0)
    {
      nho = true;
      gia_tri += 10;
    }
    else
    {
      nho = false;
    }

    kq.dayso.AddHead(gia_tri + '0');
    --i1;
    --i2;
  }
  return kq;
}
SoNguyenLon SoNguyenLon::operator*(SoNguyenLon sk)
{
  SoNguyenLon kq;
  int N1 = this->DoDai(), i1 = N1 - 1;
  int nho = 0;

  while (i1 >= 0)
  {
    SoNguyenLon kq_tam;
    int gia_tri1 = (*this)[i1] - '0';

    int N2 = sk.DoDai(), i2 = N2 - 1;
    while (i2 >= 0)
    {
      int gia_tri2 = i2 >= 0 ? sk[i2] - '0' : 0;
      int gia_tri = gia_tri1 * gia_tri2 + nho;

      
      nho = gia_tri / 10;
      gia_tri -= nho * 10;

      kq_tam.dayso.AddHead(gia_tri + '0');
      --i2;
    }
    // Thêm vào giá trị nhớ nếu còn
    while (nho > 0) {
      kq_tam.dayso.AddHead(nho % 10 + '0');
      nho /= 10;
    }
    // them so 0 vao sau
    for (int i = 0; i < N1 - i1 - 1; ++i) {
      kq_tam.dayso.AddTail('0');
    }
    kq = kq + kq_tam;
    --i1;
  }

  if (nho)
    kq.dayso.AddHead(nho + '0');

  return kq;
}
SoNguyenLon operator+(int so, SoNguyenLon &snl)
{
  SoNguyenLon sokhac;
  return sokhac + snl;
}
SoNguyenLon operator-(int so, SoNguyenLon &snl)
{
  SoNguyenLon sk(so);
  return sk - snl;
}
SoNguyenLon operator*(int so, SoNguyenLon &snl)
{
  SoNguyenLon sk(so);
  return sk * snl;
}
std::ostream &operator<<(std::ostream &os, SoNguyenLon &snl)
{
  int N = snl.DoDai();
  if (N == 0)
  {
    os << '0';
  }
  else
  {
    for (int i = 0; i < N; ++i)
    {
      os << snl[i];
    }
  }
  return os;
}

int main()
{
  SoNguyenLon snl1,
      snl2(44667733),
      snl3(5, 9),
      snl4(7, 30);
  SoNguyenLon snl5 = snl3 - snl2;
  SoNguyenLon snl6 = 1098765432 - snl2;
  SoNguyenLon snl7 = snl4 - snl3 + 123456789;
  SoNguyenLon snl8 = snl2 * snl3;

  std::cout << snl1 << std::endl
            << snl2 << std::endl;
  std::cout << snl3 << std::endl
            << snl4 << std::endl;
  std::cout << snl5 << std::endl
            << snl6 << std::endl;
  std::cout << snl7 << std::endl
            << snl8 << std::endl;
}