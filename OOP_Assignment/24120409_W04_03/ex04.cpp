#include <iostream>

template <typename T>
class Node
{
private:
    Node *next;
    T data;

public:
    Node();
    Node(const Node *&);
};
template <typename T>
class LinkedList
{
private:
public:
};