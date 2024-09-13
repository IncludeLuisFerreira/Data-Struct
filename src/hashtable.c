#include "../include/hashtable.h"

hashTable* initializeHashTable(size_t size, size_t (*hashFunction) (size_t ,int)) {
    hashTable *newHashTable = (hashTable*) malloc(sizeof(hashTable));

    if (newHashTable) {
        newHashTable->table = (Node**) malloc(size * sizeof(Node));
        newHashTable->size = size;
        newHashTable->hashFunction = hashFunction;

        if (newHashTable->table) {
            for (int i = 0; i < size; i++) 
                newHashTable->table[i] = NULL;

            return newHashTable;
        }
    }
    return NULL;
}

int hashTableRemove(hashTable *hashtable, int value) {
    if (!hashtable || !hashtable->table) {
        return INT_MIN;
    }

    int index = hashtable->hashFunction(hashtable->size, value);
    Node *temp = hashtable->table[index];
    Node *prev = NULL;

    while (temp != NULL) {
        
        if (temp->value == value) {

            if (prev == NULL) {
                prev = hashtable->table[index];
                hashtable->table[index] = hashtable->table[index]->next;
                index = prev->value;
                free(prev);
                prev = NULL;
                return index;
            }

            else {
                index = temp->value;
                prev->next = temp->next;
                free(temp);
                temp = NULL;
                return index;
            }
        }

        prev = temp;
        temp = temp->next;
    }
    return INT_MIN;
}

Node *createNode(int value) {
    Node *newnode = (Node*) malloc(sizeof(Node));
    
    if (!newnode) {
        fprintf(stderr, "Erro em createNode\n");
        return NULL;
    }

    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}


Node* hashTableFind(hashTable *hashtable, int value) {
    if (!hashtable || !hashtable->table) {
        return NULL;
    }

    int index = hashtable->hashFunction(hashtable->size, value);
    Node *aux = hashtable->table[index];
    
    while (aux != NULL) {
        
        if (aux->value == value)
            return aux;

        aux = aux->next;
    }
    return NULL;
}

void hashTableInsert(hashTable *hash, int value) {
    if (!hash || !hash->table) {
        return ;
    }

    int index = hash->hashFunction(hash->size, value);
    Node *newnode = createNode(value);

    if (newnode) {    
        newnode->next = hash->table[index];
        hash->table[index] = newnode;
    }
}

void printHashTable(hashTable *hashtable) {
    if (!hashtable) {
        return;
    }

    for (int i = 0; i < hashtable->size; i++) {
        if (hashtable->table[i] != NULL) {
            Node *temp = hashtable->table[i];

            printf("Index %d: ", i);
            while (temp != NULL) {
                printf("-> %d", temp->value);
                temp = temp->next;
            }
            puts("\n");
        }
    }
}

void printAllHashTable(hashTable *hashtable) {
    if (!hashtable || !hashtable->table) {
        return ;
    }

    for (int i = 0; i < hashtable->size; i++) {
        Node *temp = hashtable->table[i];
        printf("Index %d: ", i);

        while (temp != NULL) {
            printf("-> %d", temp->value);
            temp = temp->next;
        }
        puts("\n");
    }
}

void printIndexHashTable(hashTable *hashtable, int index) {
    if (!hashtable || !hashtable->table) {
        return ;
    }

    Node *temp = hashtable->table[index];
    printf("Index %d: ", index);
    while (temp != NULL) {
        printf("-> %d", temp->value);
        temp = temp->next;
    }
}

void freeHashTable(hashTable **hash) {
    hashTable *H = *hash;
    
    if (H != NULL) {
        
        if (H->table) {
            
            for(int i = 0; i < H->size; i++) {
                if (H->table[i] != NULL) {
                    Node *temp = H->table[i];
                    Node *next = NULL;
                    
                    while (temp->next != NULL) {
                        next = temp->next;
                        free(temp);
                        temp = next;
                    }
                }
            }
            free(H->table);
        }
        free(H);
        *hash = NULL;
    }
}
