#include "../include/avltree.h"


int main (int argc, char **argv) {
    avltree *tree = initializeAvlTree();
    avlInsert(tree, 10);
    avlInsert(tree, 5);
    avlInsert(tree, 50);
    avlInsert(tree, 3);
    avlInsert(tree, 4);
    avlInsert(tree, 60);

    transversalPrintAvl(tree);

    return 0;
 }