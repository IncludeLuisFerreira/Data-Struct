#include "../include/hashtable.h"

size_t Hash(size_t size, int value) {
    return value % size;
}

size_t HashV2(size_t size, int value) {
    size_t index = 0;
    index = value * 97 + 10213;
    return (size_t) index % size;
}

int main(int argc, char **argv) {

    hashTable *hash = initializeHashTable(13, &HashV2);
    hashTableInsert(hash, 0);
    hashTableInsert(hash, 10);
    printHashTable(hash);
    hashTableRemove(hash, 0);
    printHashTable(hash);

    freeHashTable(&hash);

    return 0;
}