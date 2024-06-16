#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct tree_node TNode;
typedef struct tree Tree;

struct tree_node {
    int value;
    struct tree_node *left, *right;
};

struct tree {
    TNode *root;
    size_t size;
};


Tree *init_Tree();
TNode *create_TNode(int value);
TNode *insertTreeNode(TNode *root, int value);
void destroyTree(Tree **tree, TNode *root);
int height(TNode *root);
int countTNode(TNode *root);
TNode *deleteTNode(TNode *root, int value);
bool isBalanced(TNode *root);
int checkBalance(TNode *root, bool *bolean);
bool isLeave(TNode *);
int countLeaves(TNode *root);
void mirrorTree(TNode *root);
bool areTreeEqual(TNode *root1, TNode *root2);
TNode *findMin(TNode *root);
TNode *findMax(TNode *root);
void printTree(TNode *root);


#endif