#include "../include/circular_linked_list.h"

int main() {
    CList *teste = init_CList();
    CList *copy = clone_CList(teste);

    addFirst_CList(teste, 1);
    addFirst_CList(teste, 2);
    addLast_CList(teste, 3);
    insert_CList(teste, 0, 0);
    insert_CList(teste, 10, 1);
    print_CList(teste);
    inverted_print_CList(teste);

    copy = clone_CList(teste);
    print_CList(copy);

    clean_CList(&copy);
    print_CList(copy);
    
    return 0;
}