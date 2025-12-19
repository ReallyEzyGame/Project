#include <stdio.h>
#include <fstream>
#include <iostream>

struct Node
{
    int _data;
    Node *_nxt;
};

struct LinkedList
{
    Node *_head = nullptr, *_tail = nullptr;
};

Node *create_node(const int value);
void add_head(LinkedList *list, const int x);
void add_head(LinkedList *list, Node *node);
void add_tail(LinkedList *list, Node *node);
void add_tail(LinkedList *list, const int x);
void remove_head(LinkedList *list);
void remove_tail(LinkedList *list);

LinkedList* create_list(std::istream &is);
std::ostream &print_list(std::ostream &os, LinkedList *list);
void destroy_list(LinkedList *&list);