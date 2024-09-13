#include "../include/dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *initDictKeyUtil(size_t size) {
    char *key = (char*) calloc(size, sizeof(char));
    
    if (key)
        strncpy(key, NULLSTRING, size-1);
    
    return key;
}

node *criarNode(void *item, char *key) {
    node *newnode = (node*) malloc(sizeof(node));
    
    if (newnode) {
        newnode->data = item;
        newnode->key = key;
    }
    return newnode;
}

void error(char *mensage, int shutdow) {
    fprintf(stderr, "%s\n", mensage);
    if (shutdow == 1)
        exit(EXIT_FAILURE);
}

/*******************************************************************************/

Dict *initDict(char *nameofobject,size_t maxsize) {
    Dict *newdict = (Dict*) malloc(sizeof(Dict));
    
    if (newdict) {
        newdict->objectName = initDictKeyUtil(strlen(nameofobject));
        newdict->table = (node**) calloc(maxsize, sizeof(node*));

        for (int i = 0; i < maxsize; i++) {
            newdict->table[i] = criarNode(NULL, initDictKeyUtil(20));  
        }
        
        strcpy(newdict->objectName, nameofobject);
        newdict->maxsize = maxsize;
        newdict->size = 0;
        return newdict;
    }
    error("Error-> initDict", 1);
}

size_t hash(const char *key, size_t maxsize) {
    size_t hash = 5381;  
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % maxsize;  
}
void insertDict(Dict *dict, const char *key, void *item) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return;
    }

    if (dict->size < dict->maxsize) {
        size_t index = hash(key, dict->maxsize);

        if (strncmp(dict->table[index]->key, NULLSTRING, 19) == 0) {
            strncpy(dict->table[index]->key, key, 19);
            dict->table[index]->data = item;
            dict->size++;
        }
        else
            printf("Index ocupado!\n");
    }
}

void *search(Dict *dict, const char *key) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return NULL;
    }
    size_t index = hash(key, dict->maxsize);
    
    if (dict->table[index]->data != NULL && strncmp(dict->table[index]->key, key, 19) == 0) {
        return dict->table[index]->data;
    }
    else
        printf("Elemento nao encontrado!\n");
    return NULL;
        
}

void printfDict(Dict *dict) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return ;
    }

    printf("Name of object: %s\n", dict->objectName);
    printf("Size: %d\t MaxSize: %d\n", dict->size, dict->maxsize);
        
    for (int i = 0; i < dict->maxsize; i++) {
        if (dict->table[i]->data != NULL)
            printf("Key: %10s \t Item: %p\n", dict->table[i]->key, dict->table[i]->data);
    }
}

void update(Dict *dict, const char *key, void *newitem) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return ;
    }

    size_t index = hash(key, dict->maxsize);
    
    if (dict->table[index]->data != NULL) {
        dict->table[index]->data = newitem;
        printf("Item atualizado com sucesso!\n");
    }
    else
        printf("Index vazio!\n");
}

int contains(Dict *dict, const char *key) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return 0;
    }

    size_t index = hash(key, dict->maxsize);
    
    if (strcmp(dict->table[index]->key, key) == 0)
        return 1;
    else
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
node *backUpData(Dict *dict) {
    if (!dict) 
        return NULL;
        
    int j = 0, tam = dict->size;
    node *vetor = (node*) malloc(tam * sizeof(node));

    for (int i = 0; i < dict->maxsize; i++) {
        if (dict->table[i]->data != NULL) {
            vetor[j++] = *dict->table[i];
        }
    }
    return vetor;
}

void resize(Dict **dict, size_t newsize) {
}

char **getAllKeys(Dict *dict) {
    if (!dict) {
        error("Dictionary not initialized!\n", 0);
        return NULL;
    }
        
    char **keys = (char**) malloc(dict->size * sizeof(char*));
    
    int j = 0;
    if (keys != NULL) {
        for (int i = 0; i< dict->size; i++) {
            keys[i] = initDictKeyUtil(20);
        }
        
        for (int i = 0; i < dict->maxsize; i++) {
            if (dict->table[i]->data != NULL) {
                strncpy(keys[j++], dict->table[i]->key, 19);
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
        if (dict->table[i]->data != NULL) {
            free(dict->table[i]->data);
            strcpy(dict->table[i]->key, NULLSTRING);
            dict->table[i]->data = NULL;
        }
    }
    dict->size = 0;
}
