#include <string.h>

#include "hash_table.h"

// Constructs a new key-value pair. Duplicates strings onto the heap
static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* new_item = malloc(sizeof(ht_item));
    new_item->key = strdup(k);
    new_item->value = strdup(v);
    return new_item;
}

// Constructs a new hash table
ht_hash_table* ht_new() {
    ht_hash_table* new_ht = malloc(sizeof(ht_hash_table));

    new_ht->size = 53; // Setting # of buckets to 53 until I implement resizing
    new_ht->count = 0;
    new_ht->items = calloc(new_ht->size, sizeof(ht_item*));
    return new_ht;
}

// Deletes an ht_item by freeing its allocated memory
static void ht_del_item(ht_item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

// Deletes an ht_hash_table by freeing its allocated memory
void ht_del_hash_table(ht_hash_table* ht) {
    ht_item* item = NULL; // We reassign in the next line so this should be safe
    for (size_t i = 0; i < ht->size; ++i) {
        item = ht->items[i];
        if (item != NULL) ht_del_item(item);
    }

    free(ht->items);
    free(ht);
}