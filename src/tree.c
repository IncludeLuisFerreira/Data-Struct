#include "../include/tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Tree *init_Tree() {
    Tree *tree = (Tree*) malloc(sizeof(Tree));
    
    if (tree == NULL) {
        fprintf(stderr, "Error in 'init_Tree' ==> malloc error!\n");
        exit(EXIT_FAILURE);
    }

    tree->root = NULL;
    tree->size = -1;
    
    return tree;
}

TNode *create_TNode(int value) {
    TNode *node = (TNode*) malloc(sizeof(TNode));

    if (node == NULL) {
        fprintf(stderr, "Error in 'create_TNode' ==> malloc error!\n");
        exit(EXIT_FAILURE);
    }

    node->left = NULL;
    node->right = NULL;
    node->value = value;

    return node;
}

TNode *insertTreeNode(TNode *root, int value) {
    if (root == NULL) {
        root = create_TNode(value);
    }
    else {
        if (value > root->value)
            root->right = insertTreeNode(root->right, value);
        else
            root->left = insertTreeNode(root->left, value);
    }
    return root;
}

void destroyTree(Tree **tree, TNode *root) {
    if (root == NULL) {
        return;
    }
    destroyTree(tree,root->left);
    destroyTree(tree,root->right);

    if ((*tree)->root == root) {
        free(*tree);
        *tree = NULL;
    }
    free(root);
}

int height(TNode *root) {
   if (root == NULL) {
        return 0;
    }
   else {
        int left = height(root->left);
        int right = height(root->right);

        return 1 + (left > right) ? left : right;
    }
}

int countTNode(TNode *root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return 1 + countTNode(root->right) + countTNode(root->left);
    }
}

TNode *deleteTNode(TNode *root, int value) {
    if (root == NULL) return NULL;
    
    if (root->value == value) {
        if (root->right == NULL && root->left == NULL) {
            free(root);
            return NULL;
        }
        else {
            if (root->left && root->right) {
                TNode *aux = root->left;
                
                while (aux->right != NULL) {
                    aux = aux->right;
                }

                root->value = aux->value;
                aux->value = value;
                root->left = deleteTNode(root->left, value);
                return root;
            }
            else {
                TNode *aux = NULL;
                
                if (root->left != NULL) {
                    aux = root->left;
                }
                else {
                    aux = root->right;
                }
                free(root);
                return aux;
            }
        }
    }
    else {
        if (value < root->value) {
            root->left = deleteTNode(root->left, value);
        }
        else {
            root->right = deleteTNode(root->right, value);
        }
    }
}   

int checkBalance(TNode *root, bool *bolean) {
    if (root == NULL || !*bolean) {
        return 0;
    }


    int left = checkBalance(root->left, bolean);
    int right = checkBalance(root->right, bolean);
    
    if (abs(left - right) > 1) {
        *bolean = false;   
    }

    return 1 + ((left > right) ? left : right);
}


bool isBalanced(TNode *root) {
    bool balanced = true;
    checkBalance(root, &balanced);

    return balanced;
}

bool isLeave(TNode *node) {
    return node->left == NULL && node->right == NULL;
}

int countLeaves(TNode *root) {
    if (root == NULL) {
        return 0;
    }
    else if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    else {
        return countLeaves(root->left) + countLeaves(root->right);
    }
}

void mirrorTree(TNode *root);

bool areTreeEqual(TNode *root1, TNode *root2);

TNode *findMin(TNode *root);

TNode *findMax(TNode *root);




void printTree(TNode *root) {
    if (root == NULL) {
        
    }
    else {
        printTree(root->left);
        printf(" %d ", root->value);
        printTree(root->right);
    }
}
