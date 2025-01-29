#include "linked_list.h"

int main() {
    LinkedList *list = Linked_list_Create();

    Linked_list_insert(list, 0, 9);
    Linked_list_insert(list, 0, 32);
    Linked_list_insert(list, 2, 1);
    Linked_list_insert(list, 2 , 10);
    print_Linked_list(list);
    Linked_list_invert_v2(&list);
    print_Linked_list(list);
    LinkedList *teste = Linked_list_copy(list);
    print_Linked_list(teste);
    teste = Linked_list_cat(teste, list);
    print_Linked_list(teste);
    sort_list(teste);
    print_Linked_list(teste);
    print_Node(Linked_list_search(teste, 10));
    
    LinkedList *p = Linked_list_Create();
    Linked_list_sorted_insert(p, 10);
    Linked_list_sorted_insert(p, 2);
    Linked_list_sorted_insert(p, 1);
    Linked_list_sorted_insert(p, 4);
    Linked_list_sorted_insert(p, 1);
    Linked_list_sorted_insert(p, 4);
    Linked_list_sorted_insert(p, 43);
    Linked_list_sorted_insert(p, 12);
    print_Linked_list(p);
    
    return 0;
}