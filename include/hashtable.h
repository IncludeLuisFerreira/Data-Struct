#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int value;
    struct node *next;
}Node;

typedef struct hashTable {
    Node **table;
    size_t size;
    size_t (*hashFunction) (size_t , int);
}hashTable;


hashTable* initializeHashTable(size_t size, size_t (*hashFunction) (size_t ,int));

int hashTableRemove(hashTable *hashtable, int value);
Node *createNode(int value);
Node* hashTableFind(hashTable *hashtable, int value);
void hashTableInsert(hashTable *hash, int value);
void printHashTable(hashTable *hashtable);
void printAllHashTable(hashTable *hashtable);
void printIndexHashTable(hashTable *hashtable, int index);
void freeHashTable(hashTable **hash);

#endif