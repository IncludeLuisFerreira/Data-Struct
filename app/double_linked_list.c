#include "../include/double_linked_list.h"

int main() {
    DLinkedlist *teste = init_DLinkedlist();


    sorted_insert_DLinkedlist(teste, 21);
    sorted_insert_DLinkedlist(teste, 12);
    sorted_insert_DLinkedlist(teste, 9);
    sorted_insert_DLinkedlist(teste, 5);
    sorted_insert_DLinkedlist(teste, 0);
    sorted_insert_DLinkedlist(teste, 1);
    sorted_insert_DLinkedlist(teste , 200);
    print_DLinkedlist(teste);
    inverted_print_DLinkedlist(teste);


    return 0;
}