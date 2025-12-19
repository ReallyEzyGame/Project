#include "header.h"

// 2 list -> 1 list
LinkedList *merge_in_order(LinkedList *list1, LinkedList *list2)
{
    LinkedList *list = new LinkedList;
    Node *tmp1 = list1->_head;
    Node *tmp2 = list2->_head;

    int idx = 0;
    while (tmp1 && tmp2)
    {
        if (idx % 2 == 0)
        {
            add_tail(list, tmp1);

            Node *save = tmp1;
            tmp1 = tmp1->_nxt;
            save->_nxt = nullptr;
        }
        else
        {
            add_tail(list, tmp2);

            Node *save = tmp2;
            tmp2 = tmp2->_nxt;
            save->_nxt = nullptr;
        }

        idx++;
    }

    list1->_head = list1->_tail = nullptr;
    list2->_head = list2->_tail = nullptr;

    return list;
}

int main()
{
    std::ifstream input1("input.txt");
    std::ifstream input2("input_sorted.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list1 = create_list(input1);
    LinkedList* list2 = create_list(input2);\

    std::cout << "Before Merging:\n";
    print_list(std::cout, list1);
    std::cout << std::endl;
    print_list(std::cout, list2);
    std::cout << std::endl;


    LinkedList* list = merge_in_order(list1, list2);
    std::cout << "After Mergeing:\n";
    print_list(std::cout, list);

    print_list(output, list);
    output << std::endl;

    destroy_list(list);
    input1.close();
    input2.close();
    output.close();

    delete list;
    delete list1;
    delete list2;
}