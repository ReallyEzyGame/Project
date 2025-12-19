#include "header.h"


void recursive(Node* prev, Node* curr) {
    if (curr == nullptr) {
        return;
    }

    recursive(curr, curr->_nxt);
    curr->_nxt = prev;
}
// Reverse the list
LinkedList *reverse(LinkedList *list)
{
    recursive(nullptr, list->_head);
    std::swap(list->_head, list->_tail);

    return list;
}


int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt", std::ios::app);

    LinkedList* list = create_list(input);

    std::cout << "Before Reverse:\n";
    print_list(std::cout, list);
    std::cout << std::endl;

    reverse(list);
    std::cout << "After reverse:\n";
    print_list(std::cout, list);

    print_list(output, list);
    output << std::endl;

    destroy_list(list);
    input.close();
    output.close();

    delete list;
}