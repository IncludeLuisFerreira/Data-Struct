#include "avltree.h"

/**************************************** Private Functions Utilitis ********************************************************** */

Node *insertAvlNode(Node *root, int value) {
    if (!root) {
        return createNode(value);
    }

    if (value > root->value)
        root->right = insertAvlNode(root->right, value);
    else
        root->left  =  insertAvlNode(root->left, value);
    
    return root;
}

Node *removeAvlTree(Node *root, int value) {
    if (!root) {
        return NULL;
    }

    if (value > root->value) 
        root->right = removeAvlTree(root->right, value);
    else if (value < root->value)
        root->left = removeAvlTree(root->left, value);
    else {
        // Leaf node
        if (!root->left && !root->right) {
            free(root);
            return NULL;
        }
        //This node has only one pointer
        else if (!root->left || !root->right) {
            if (!root->left) {
                Node *temp = root->right;
                free(root);
                return temp;
            }

            else {
                Node *temp = root->left;
                free(root);
                return temp;
            }
        }
        //This node has two child
        else {
            Node *temp = root->left;
            
            while (temp->right) {
                temp = temp->right;
            }
            
            root->value = temp->value;
            temp->value = value;
            root->left = removeAvlTree(root->left, value);
            return root;
        }
    }
}

void transversalPrintAvlUtil(Node *root, int depth) {
    int i;
    
    if (root->right) transversalPrintAvlUtil(root->right, depth + 2);

    for (i = 0; i < depth; i++) putchar(' ');
    printf(" %d \n", root->value);
    
    if (root->left) transversalPrintAvlUtil(root->left, depth + 2);
}
/******************************************************************************************************/
avltree *initializeAvlTree() {
    avltree *newavltree = (avltree*) malloc(sizeof(avltree));
    
    if (!newavltree) {
        
        return NULL;
    }

    newavltree->countNode = 0;
    newavltree->height = 0;
    newavltree->root = NULL;
    return newavltree;
}

Node *createNode(int value) {
    Node *newnode = (Node*) malloc(sizeof(Node));
    
    if (!newnode) {
        return NULL;
    }
    
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->value = value;
    return newnode;
}

Node *avlBalanceNode(Node *node) {
    Node *newroot;
    
    if (node->left )
        node->left = avlBalanceNode(node->left);
    if (node->right)
        node->right = avlBalanceNode(node->right);

    int balanceFactor = avlBalanceFactor(node);

    if (balanceFactor <= -2) {
        
        if (avlBalanceFactor(node->left) >= 1)
            newroot = rotationLR(node);
        else
            newroot = rotationLL(node);
    }
    else if (balanceFactor >= 2) {

        if (avlBalanceFactor(node->right) <= -1)
            newroot = rotationRL(node);
        else
            newroot = rotationRR(node);
    }
    else
        newroot = node;

    return newroot;
}

Node *rotationLL(Node *node) {
    Node *a = node;
    Node *b = a->left;
    
    a->left = b->right;
    b->right = a;

    return b;
}

Node *rotationLR(Node *node) {
    Node *a = node;
    Node *b = a->left;
    Node *c = b->right;

    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;

    return c;   
}

Node *rotationRL(Node *node) {
    Node *a = node;
    Node *b = a->right;
    Node *c = b->left;

    a->right = c->left;
    b->left = c->right;
    c->right = b;
    c->left = a;
    
    return c;
}

Node *rotationRR(Node *node) {
    Node *a = node;
    Node *b = a->right;

    a->right = b->left;
    b->left = a;

    return b;
}

Node *avlFind(Node *root, int value) {
    if (!root) {
        return NULL;
    }
    
    if (root->value == value)
        return root;
    else if (value > root->value)
        return avlFind(root->right, value);
    else
        return avlFind(root->left, value);
}


void avlBalance(avltree *tree) {
    Node *newroot = avlBalanceNode(tree->root);

    if (newroot != tree->root)
        tree->root = newroot;
}


void avlInsert(avltree *tree, int value) {
    if (!tree) {
        return;
    }

    tree->root = insertAvlNode(tree->root, value);
    avlBalance(tree);
}

void transversalPrintAvl(avltree *tree) {
    if(!tree) {
        return ;
    }
    transversalPrintAvlUtil(tree->root, 0);
}

int avlNodeHeight(Node *node) {
    int left  = 0;
    int right = 0;

    if (node->left ) left  = avlNodeHeight(node->left );
    if (node->right) right = avlNodeHeight(node->right);

    return (right > left) ? ++right : ++left;
}

int avlBalanceFactor(Node *node) {
    int balanceFactor = 0;
    
    if (node->left ) balanceFactor -= avlNodeHeight(node->left );
    if (node->right) balanceFactor += avlNodeHeight(node->right);

    return balanceFactor;
}


