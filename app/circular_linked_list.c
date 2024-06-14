#include "../include/circular_linked_list.h"

int main() {
    CList *teste = init_CList();

    addFirst_CList(teste, 1);
    addLast_CList(teste, 3);
    print_CList(teste);
    inverted_print_CList(teste);

    return 0;
}