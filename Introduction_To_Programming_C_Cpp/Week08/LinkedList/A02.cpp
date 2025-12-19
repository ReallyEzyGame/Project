#include "header.h"

// remove duplicate
void remove_duplicate(LinkedList *list)
{
    Node *tmp = list->_head;

    while (tmp)
    {
        Node *iterate = tmp;

        while (iterate->_nxt)
        {
            if (iterate->_nxt->_data == tmp->_data)
            {
                Node *del = iterate->_nxt;
                iterate->_nxt = del->_nxt;

                delete del;
            }
            else
            {
                iterate = iterate->_nxt;
            }
        }

        tmp = tmp->_nxt;
    }
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list = create_list(input);

    std::cout << "Before Removing duplicate:\n";
    print_list(std::cout, list);
    std::cout << std::endl;

    remove_duplicate(list);
    std::cout << "After Removing duplicate:\n";
    print_list(std::cout, list);

    print_list(output, list);
    output << std::endl;

    destroy_list(list);
    input.close();
    output.close();

    delete list;
}