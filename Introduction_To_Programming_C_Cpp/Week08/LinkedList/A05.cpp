#include "header.h"

// Sorted list
void insert_to_sorted_list(LinkedList *list, const int x)
{
    if (list->_head == nullptr)
    {
        add_head(list, x);
    }

    if (x < list->_head->_data)
    {
        add_head(list, x);
    }
    else if (x > list->_tail->_data)
    {
        add_tail(list, x);
    }
    else
    {
        Node *add = create_node(x);
        Node *tmp = list->_head;

        while (tmp->_nxt && tmp->_nxt->_data < x)
        {
            tmp = tmp->_nxt;
        }

        add->_nxt = tmp->_nxt;
        tmp->_nxt = add;
    }
}

int main()
{
    std::ifstream input("input_sorted.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list = create_list(input);
    int value;

    std::cout << "Before insert:\n";
    print_list(std::cout, list);
    std::cout << std::endl;

    std::cout << "Input a positive value value to insert: ";
    std::cin >> value;

    insert_to_sorted_list(list, value);
    std::cout << "After insert " << value << ":\n";
    print_list(std::cout, list);

    print_list(output, list);
    output << std::endl;

    destroy_list(list);
    input.close();
    output.close();

    delete list;
}