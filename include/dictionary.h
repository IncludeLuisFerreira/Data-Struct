#ifndef DICITIONARY_H
#define DICITIONARY_H

#include <stdio.h>
#define LOAD_FACTOR     0.75
#define MAX_ATTEMPT     5

typedef struct node {
    char *key;
    void *data;
}node;

typedef struct dictionary {
    node ** table;
    size_t size;
    size_t maxsize;
}Dict;

/***********************************************************/

Dict *initDict(size_t maxsize);

void insertDict(Dict *, const char *key, void *item);

void *search(Dict *, const char *key);

int contains(Dict *, const char *key);

void printfDict(Dict *);

void resize(Dict *dict);

char **getAllKeys(Dict *);

size_t sizeofDict(Dict *);

void clear(Dict *);


/***********************************************************/

#endif