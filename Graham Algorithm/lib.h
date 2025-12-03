#include <iostream>

#define STACK_SIZE 8192

struct Cordinate
{
  float x = 0.f, y = 0.f;
};

template <typename T>
class Node
{
private:
  T data;
  Node *nxt;

public:
  // Default Construct with default input data and nullptr in next node field
  Node();
  // construct a Node with the nxt Node field is input Node
  Node(const Node *);
  // Construct a Node from given value and next node  is nullptr
  Node(const T);
  // construct a Node with input value and Next Node field
  Node(const T, const Node *);
  // Copy from a Node
  Node(const Node &);
  ~Node() = default;

  void setNextnode(const Node *);
  void setValue(const T);

  T getData() const;
  Node *getNextNode();
};

template <typename T>
Node<T>::Node()
{
  this->data = T();
  this->nxt = nullptr;
}
template <typename T>
Node<T>::Node(const Node *nxt)
{
  this->data = T();
  this->nxt = nxt;
}
template <typename T>
Node<T>::Node(const T val)
{
  this->data = val;
  this->nxt = nullptr;
}
template <typename T>
Node<T>::Node(const T val, const Node *nxt)
{
  this->data = val;
  this->nxt = nxt;
}
template <typename T>
Node<T>::Node(const Node<T>& other)
{
  this->data = other.val;
  // Avoid ptr to the same node
  this->nxt = nullptr;
}

template <typename T>
void Node<T>::setNextnode(const Node *node)
{
  nxt = nullptr;
}
template <typename T>
void Node<T>::setValue(const T val)
{
  data = val;
}

template <typename T>
T Node<T>::getData() const
{
  return data;
}
template <typename T>
Node<T> *Node<T>::getNextNode()
{
  return nxt;
}




class Stack
{
private:
  Node<Cordinate> *top_node;
  int max_size;
  int size;

public:
  Stack();
  Stack(const Stack &);
  ~Stack();

  bool push(const Cordinate);
  bool pop();

  Cordinate top() const;
  int stackSize() const;
  bool isEmpty() const;
  bool isFull() const;
};

Stack::Stack()
{
  this->top_node = nullptr;
  this->max_size = STACK_SIZE;
  this->size = 0;
}
Stack::Stack(const Stack &other)
{
  this->size = other.size;
  this->max_size = other.max_size;

  Node<Cordinate>* cur = nullptr, *nxt;
  Node<Cordinate>* tmp = other.top_node;  

  cur = new Node<Cordinate>(tmp);
  tmp = tmp->getNextNode();

  this->top_node = cur;

  while (tmp)
  {
    nxt = new Node<Cordinate>(tmp);
    cur->setNextnode(nxt);

    tmp = tmp->getNextNode();
  }
}
Stack::~Stack()
{
  Node<Cordinate>* tmp = this->top_node;
  Node<Cordinate>* del;
  while (tmp) {
    del = tmp;
    tmp = tmp->getNextNode();

    delete del;
  }
}


bool Stack::push(const Cordinate cordi) {
  if (!this->isFull()) {
    Node<Cordinate>* nxt = new Node(cordi, top_node);

    this->top_node = nxt;
    this->size++;
    return true;
  }
  else {
    return false;
  }
}
bool Stack::pop() {
  if (!this->isEmpty()) {
    Node<Cordinate>* del;
    this->top_node = this->top_node->getNextNode();

    size--;
    delete del;
    return true;
  }
  else {
    return false;
  }
}


Cordinate Stack::top() const {
  return top_node->getData();
}
int Stack::stackSize() const {
  return size;
}
bool Stack::isEmpty()  const {
  return size == 0;
}
bool Stack::isFull() const {
  return size == max_size;
}


