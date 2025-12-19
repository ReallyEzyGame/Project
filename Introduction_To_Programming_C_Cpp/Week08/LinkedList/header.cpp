#include "header.h"

Node *create_node(const int value)
{
    Node *add = new Node;
    add->_data = value;
    add->_nxt = nullptr;

    return add;
}
void add_head(LinkedList *list, const int x)
{
    Node *add = create_node(x);

    if (list->_head == nullptr)
    {
        list->_head = add;
        list->_tail = add;
    }
    else
    {
        add->_nxt = list->_head;
        list->_head = add;
    }
}
void add_head(LinkedList *list, Node *node)
{
    if (list->_head == nullptr)
    {
        list->_head = node;
        list->_tail = node;
    }
    else
    {
        node->_nxt = list->_head;
        list->_head = node;
    }
}
void add_tail(LinkedList *list, Node *node)
{
    if (list->_head == nullptr)
    {
        list->_head = node;
        list->_tail = node;
    }
    else
    {
        list->_tail->_nxt = node;
        list->_tail = node;
    }
}
void add_tail(LinkedList *list, const int x)
{
    Node *add = create_node(x);

    if (list->_head == nullptr)
    {
        list->_head = add;
        list->_tail = add;
    }
    else
    {
        list->_tail->_nxt = add;
        list->_tail = add;
    }
}
void remove_head(LinkedList *list)
{
    if (list->_head == nullptr)
    {
        return;
    }

    Node *del = list->_head;

    if (list->_head == list->_tail)
    {
        list->_head = nullptr;
        list->_tail = nullptr;
    }
    else
    {
        list->_head = list->_head->_nxt;
    }

    delete del;
}
void remove_tail(LinkedList *list)
{
    if (list->_head == nullptr)
    {
        return;
    }

    Node *tmp = list->_head;
    Node *del;

    while (tmp->_nxt->_nxt)
    {
        tmp = tmp->_nxt;
    }

    if (list->_head == list->_tail)
    {
        list->_head = nullptr;
        list->_tail = nullptr;
    }
    else
    {
        del = tmp->_nxt;
        tmp->_nxt = nullptr;
        list->_tail = tmp;
    }

    delete del;
}

std::ostream &print_list(std::ostream &os, LinkedList *list)
{
    Node *tmp = list->_head;

    while (tmp)
    {
        os << tmp->_data << " ";
        tmp = tmp->_nxt;
    }
    os << 0;

    return os;
}
LinkedList* create_list(std::istream &is)
{
    LinkedList* list = new LinkedList();
    while (!is.eof() && !(is.peek() == '\n'))
    {
        int val;
        is >> val;
        add_tail(list, val);
    }

    return list;
}
void destroy_list(LinkedList *&list)
{
    Node *tmp = list->_head;

    while (tmp)
    {
        Node *del = tmp;
        tmp = tmp->_nxt;

        delete del;
    }

    list = nullptr;
}