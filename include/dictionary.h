#ifndef DICITIONARY_H
#define DICITIONARY_H

#include <stdio.h>
#define NULLSTRING      "nullstring"

typedef struct node {
    char *key;
    void *data;
}node;

typedef struct dictionary {
    char *objectName;
    node ** table;
    size_t size;
    size_t maxsize;
}Dict;

/***********************************************************/

Dict *initDict(char *nameofobject, size_t maxsize);

void insertDict(Dict *, const char *key, void *item);

void *search(Dict *, const char *key);

void update(Dict *, const char *key, void *newitem);

int contains(Dict *, const char *key);

void printfDict(Dict *);


char **getAllKeys(Dict *);

size_t sizeofDict(Dict *);

void clear(Dict *);


/***********************************************************/

#endif