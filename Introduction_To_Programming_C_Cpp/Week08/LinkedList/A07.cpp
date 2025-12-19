#include "header.h"

// 1 list -> 2 list
void seperate_list(LinkedList *&list1, LinkedList *&list2)
{
    LinkedList* tmp_list = new LinkedList();
    Node *tmp = list1->_head;

    int idx = 0;
    while (tmp)
    {
        Node *save = tmp;

        if (idx % 2 == 0)
        {
            add_tail(tmp_list, save);
        }
        else
        {
            add_tail(list2, save);
        }
        tmp = tmp->_nxt;
        save->_nxt = nullptr;
        idx++;
    }
    list1 = tmp_list;
    delete tmp_list;
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list = create_list(input);

    std::cout << "Before seperation:\n";
    print_list(std::cout, list);
    std::cout << std::endl;

    LinkedList *list2 = new LinkedList();
    seperate_list(list, list2);
    std::cout << "After seperation:\n";
    print_list(std::cout, list);
    std::cout << std::endl;
    print_list(std::cout, list2);

    print_list(output, list);
    output << std::endl;
    print_list(output, list2);
    output << std::endl;

    destroy_list(list);
    destroy_list(list2);
    input.close();
    output.close();

    delete list;
    delete list2;
}