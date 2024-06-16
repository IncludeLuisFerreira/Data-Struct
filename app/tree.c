#include "../include/tree.h"
#include <stdio.h>

int main() {
    Tree *test = init_Tree();
    test->root = insertTreeNode(test->root, 10);
    test->root = insertTreeNode(test->root, 1);
    test->root = insertTreeNode(test->root, 2);
    test->root = insertTreeNode(test->root, 43);
    test->root = insertTreeNode(test->root, 100);
    printTree(test->root);
    printf("Leave: %d", countLeaves(test->root));
    destroyTree(&test, test->root);

    return 0;
}