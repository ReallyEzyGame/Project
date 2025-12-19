#include "header.h"

// List of sum
LinkedList *list_of_sum(LinkedList *list)
{
    LinkedList *sum_list = new LinkedList();
    Node *tmp = list->_head;
    int sum = 0;

    while (tmp)
    {
        sum += tmp->_data;
        add_tail(sum_list, sum);

        tmp = tmp->_nxt;
    }

    return sum_list;
}

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list = create_list(input);

    std::cout << "Input list:\n";
    print_list(std::cout, list);
    std::cout << std::endl;

    LinkedList* sum_list = list_of_sum(list);

    std::cout << "list of sum:\n";
    print_list(std::cout, sum_list);

    print_list(output, sum_list);
    output << std::endl;

    destroy_list(sum_list);
    destroy_list(list);
    input.close();
    output.close();

    delete list;
}