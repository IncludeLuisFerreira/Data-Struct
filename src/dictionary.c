#include "../include/dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dict_free_item(node *item) {
    if (!item) return;

    free(item->key);
}

node *criarNode(void *item, char *key) {
    node *newnode = (node*) malloc(sizeof(node));
    
    if (newnode) {
        newnode->data = item;
        newnode->key = strdup(key);
    }
    return newnode;
}

Dict *initDict(size_t maxsize) {
    Dict *newdict = (Dict*) malloc(sizeof(Dict));
    
    if (newdict) {
        newdict->table = (node**) calloc(maxsize, sizeof(node*));

        if (!newdict->table) {
            free(newdict);
            exit(EXIT_FAILURE);
        }
    
        newdict->maxsize = maxsize;
        newdict->size = 0;
        return newdict;
    }
}

size_t hash(const char *key, size_t hash_size, int attempts) {
    size_t len = strlen(key);
    unsigned int seed = 0x1234abcd;
    unsigned int h = seed ^ len;
    const unsigned char *data = (const unsigned char *)key;

    while (len >= 4) {
        unsigned int k = *(unsigned int*)data;
        data += 4;
        len -= 4;

        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> (32 - 15));
        k *= 0x1b873593;
        h ^= k;
        h = (h << 13) | (h >> (32 - 13));
        h = h * 5 + 0xe6546b64;
    }

    if (len > 0) {
        unsigned int k = 0;
        switch (len) {
            case 3: k ^= data[2] << 16; break;
            case 2: k ^= data[1] << 8; break;
            case 1: k ^= data[0]; break;
        }
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> (32 - 15));
        k *= 0x1b873593;
        h ^= k;
    }

    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return ((h % hash_size) + (attempts * attempts)) % hash_size;
}

void insertDict(Dict *dict, const char *key, void *item) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return;
    }

    if ((double)dict->size / dict->maxsize >= LOAD_FACTOR) {
        resize(dict);
    }

    int attempts = 0;
    size_t index;
    node *new_item = criarNode(item, key);
    size_t hash_key = hash(key, dict->maxsize, attempts++);

    while (attempts < 5) {
        if (dict->table[hash_key] == NULL) {
            dict->table[hash_key] = new_item;
            dict->size++;
            break;
        }
        else if (strcmp(key, dict->table[hash_key]->key) == 0) {
            dict_free_item(dict->table[hash_key]);
            dict->table[hash_key] = new_item;
            break;
        }
        else {
            hash_key = hash(key, dict->maxsize, attempts++);
        }
    }
}

void *search(Dict *dict, const char *key) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return NULL;
    }
   
   int attempts = 0;
   size_t index = hash(key, dict->maxsize, attempts++);
   
   while (attempts < 5) {
        node *current_item = dict->table[index];
        if (current_item != NULL && strcmp(current_item->key, key) == 0)
            return current_item->data;
        else
            index = hash(key, dict->maxsize, attempts++);
    }
    return NULL;
}

void printfDict(Dict *dict) {
    if (!dict) {
        return ;
    }

    printf("Size: %d\t MaxSize: %d\n", dict->size, dict->maxsize);
        
    for (int i = 0; i < dict->maxsize; i++) {
        if (dict->table[i] != NULL)
            printf("Key: %10s \t Item: %p\n", dict->table[i]->key, dict->table[i]->data);
    }
}

int contains(Dict *dict, const char *key) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return 0;
    }

    int attempts = 0;
    size_t index = hash(key, dict->maxsize, attempts++);
    
    while (attempts < 5) {
        node *current_item = dict->table[index];
        if (current_item != NULL && strcmp(current_item->key, key) == 0)
            return 1;
        else
            index = hash(key, dict->maxsize, attempts++);
    }
    return 0;
}

void freeutil(node **table) {
    node *aux = *table;
    
    if (aux->data) {
        free(aux->data);
        aux->data = NULL;
    }
    if (aux->key) {
        free(aux->key);
        aux->key = NULL;
    }
    free(aux);
    *table = NULL;
}

void resize(Dict *dict) {
    size_t new_size = 2 * dict->maxsize;
    node **new_items = (node**) calloc(new_size, sizeof(node*));
    
    if (!new_items) return;
    
    size_t new_hash_key = 0;
    node *current_item = NULL;
    int attempts = 0;
    
    for (size_t i = 0; i < dict->maxsize; i++) {
        if (dict->table[i] != NULL) {
            current_item = dict->table[i];
            while (attempts < 5) {
                new_hash_key = hash(current_item->key, new_size, attempts++);
                if (new_items[new_hash_key] == NULL) {
                    new_items[new_hash_key] = current_item;
                    attempts = 0;
                    break;
                }
            }
        }
    }
    
    free(dict->table);
    dict->table = new_items;
    dict->maxsize = new_size;
}

char **getAllKeys(Dict *dict) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return NULL;
    }
        
    char **keys = (char**) malloc(dict->size * sizeof(char*));
    
    int j = 0;
    if (keys != NULL) {
        
        for (int i = 0; i < dict->maxsize; i++) {
            if (dict->table[i] != NULL) {
                keys[j++] = strdup(dict->table[i]->key);
            }
        }
            
        for (int i = 0; i < dict->size; i++) {
            printf("Chave: %s\n", keys[i]);
        }
        return keys;
    }
    error("Error->getallKeys\n", 0);
}

size_t sizeofDict(Dict *dict) {
    if (!dict)
        return 0;
        
    return dict->size;
}

void clear(Dict *dict) {
    if (!dict)
        return;
    
    for (int i = 0; i < dict->maxsize; i++) {
        if (dict->table[i] != NULL) {
            memset(dict->table[i]->key, 0, sizeof(dict->table[i]->key));
            dict->table[i]->data = NULL;
        }
    }
    dict->size = 0;
}


