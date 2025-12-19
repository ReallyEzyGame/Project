#include "header.h"

// insert enven number
void insert_even_number(LinkedList *list)
{
    int even = 2;
    add_head(list, even);
    Node *tmp = list->_head->_nxt;

    even += 2;
    while (tmp)
    {
        Node *add = create_node(even);
        add->_nxt = tmp->_nxt;
        tmp->_nxt = add;

        tmp = add->_nxt;
        even += 2;
    }
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list = create_list(input);

    std::cout << "Before insert even number:\n";
    print_list(std::cout, list);
    std::cout << std::endl;

    insert_even_number(list);
    std::cout << "After insert even number:\n";
    print_list(std::cout, list);

    print_list(output, list);
    output << std::endl;

    destroy_list(list);
    input.close();
    output.close();

    delete list;
}