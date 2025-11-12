#include <iostream>
#include <exception>
#include <algorithm>

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

    // Iterator Access
    Iterator begin()
    {
        return Iterator(_pHead);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    template <class T>
    friend std::ostream &operator<<(std::ostream &os, const SLList<T> &ll)
    {
        SLList<T>::Node *node = ll._pHead;
        while (node != nullptr)
        {
            os << node->_info << ", ";
            node = node->_pNext;
        }
        return os;
    }
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
    }

    delete node;
    _n--;
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
            throw std::out_of_range("Dereferncing end() or null iterator");
        }
        return current_node->_info;
    }
    pointer operator->() const
    {
        if (!current_node)
        {
            throw std::out_of_range("Accessing member via end() or null iterator");
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
        Iterator temp = *this;
        current_node = current_node->_pNext;
        return temp;
    }
    bool operator==(const Iterator &other) const
    {
        return current_node == other.current_node;
    }
    bool operator!=(const Iterator &other) const
    {
        return !(*this == other);
    }
};

void fnAction(int val)
{
    std::cout << val << ", ";
}
void fnAction2(int &val)
{
    val *= 2;
}
bool fnPredict(int val)
{
    const int threshold = 3;
    return val > threshold;
}
int main()
{
    SLList<int> l;
    l.AddTail(1);
    l.AddTail(1);
    l.AddTail(0);
    l.AddTail(4);
    l.AddTail(2);
    l.AddTail(5);

    for (SLList<int>::Iterator it = l.begin(); it != l.end(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    std::for_each(l.begin(), l.end(), fnAction2);
    std::for_each(l.begin(), l.end(), fnAction);
    std::cout << std::endl;

    std::replace_if(l.begin(), l.end(), fnPredict, 100);
    std::cout << l << std::endl;

    std::fill(l.begin(), l.end(), 123);
    std::cout << l << std::endl;
    l.Clear();

    system("pause");
    return 0;
}