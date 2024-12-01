#include "ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* prime for FNV hash (http://isthe.com/chongo/tech/comp/fnv/)
 */
#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261

unsigned int fnvHash(char *data) {
    unsigned int hash = FNV_OFFSET_BASIS;

    for (int i = 1; i <= strlen(data); i++) {
        hash = hash ^ data[i];
        hash = hash * FNV_PRIME;
    }

    return hash;
}

HT_Item *createItem(char *key, int value) {
    HT_Item *item = malloc(sizeof(HT_Item));

    item->key = malloc(strlen(key) + 1);
    item->value = value;
    item->next = NULL;

    strcpy(item->key, key);

    return item;
}

HashTable *htInit(int size) {
    HashTable *table = malloc(sizeof(HashTable));

    table->size = size;
    table->count = 0;
    table->items = calloc(size, sizeof(HT_Item));

    for (int i = 0; i < size; i++) {
        table->items[i] = NULL;
    }

    return table;
}

int *htget(HashTable *table, char *key) { 
    unsigned int itemHash = fnvHash(key);
    HT_Item *item = table->items[itemHash % table->size];

    while (!strcmp(key, item->key)) {
        if (item->next == NULL) {
            return NULL;
        }

        item = item->next;
    }

    return &item->value;
}

void htput(HashTable *table, char *key, int value) {
    HT_Item *item = createItem(key, value);

    unsigned int itemHash = fnvHash(key);
    
    if (table->items[itemHash % table->size] == NULL) {
        table->items[itemHash % table->size] = item;
    }
    else {
        HT_Item *lastItem = table->items[itemHash % table->size];

        while (lastItem->next != NULL) {
            lastItem = lastItem->next;
        }

        lastItem->next = item;
    }
}

void htifree(HT_Item *item) {
    free(item->key);
    free(item);
}

void htfree(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            free(table->items[i]);
        }
    }

    free(table->items);
    free(table);
}

void htprint(HashTable *table) {
    HT_Item *item;

    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            item = table->items[i];
            printf("'%s': '%d'\n", item->key, item->value);

            while (item->next != NULL) {
                item = item->next;
                printf("'%s': '%d'\n", item->key, item->value);
            }
        }
    }
}
