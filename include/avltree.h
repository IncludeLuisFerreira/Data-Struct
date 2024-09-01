#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int value;
    struct node *right, *left;
}Node;

typedef struct avltree {
    Node *root;
    size_t countNode;
    size_t height;
}avltree;

avltree *initializeAvlTree();

Node *createNode(int value);
Node *removeAvlTree(Node *root, int value);
Node *avlBalanceNode(Node *node);
Node *rotationLL(Node *node);
Node *rotationLR(Node *node);
Node *rotationRL(Node *node);
Node *rotationRR(Node *node);
Node *avlFind(Node *root, int value);

void avlBalance(avltree *tree);
void avlInsert(avltree *tree, int value);
void transversalPrintAvl(avltree *tree);

int avlNodeHeight(Node *node);
int avlBalanceFactor(Node *node);




#endif