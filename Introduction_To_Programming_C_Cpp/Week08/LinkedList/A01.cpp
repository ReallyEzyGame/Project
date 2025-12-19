#include "header.h"

// remove all 'x' value in the linkedlist
void remove_all_x(LinkedList *list, const int x)
{
    while (list->_head && list->_head->_data == x)
    {
        remove_head(list);
    }
    while (list->_tail && list->_tail->_data == x)
    {
        remove_tail(list);
    }

    Node *tmp = list->_head;
    Node *del = nullptr;

    while (tmp->_nxt)
    {
        if (tmp->_nxt->_data == x)
        {
            del = tmp->_nxt;
            tmp->_nxt = del->_nxt;

            delete del;
        }
        else
        {
            tmp = tmp->_nxt;
        }
    }
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList *list = create_list(input);
    int x;
    std::cout << "Input remove value: ";
    std::cin >> x;

    std::cout << "Before remove: ";
    print_list(std::cout, list);
    std::cout << std::endl;

    remove_all_x(list, x);
    std::cout << "After remove " << x << ": ";
    print_list(std::cout, list);

    print_list(output, list);
    output << std::endl;

    destroy_list(list);
    input.close();
    output.close();

    delete list;
}