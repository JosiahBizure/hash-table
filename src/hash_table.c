#include <string.h>
#include <math.h>

#include "hash_table.h"

static const size_t HT_PRIME1 = 151;
static const size_t HT_PRIME2 = 163;

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

// Polynomial hash function that takes a string as input and returns the hashed index
static size_t ht_hash(const char* str, const size_t a, const size_t num_buckets) {
    size_t hash = 0;
    const size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        hash += (size_t)pow(a, len - (i+1)) * str[i];
        hash = hash % num_buckets;
    }
    return hash;
}

// Function to handle collisions (double hashing)
static size_t ht_get_hash(const char* str, const size_t num_buckets, const size_t attempt) {
    const size_t hash_a = ht_hash(str, HT_PRIME1, num_buckets);
    const size_t hash_b = ht_hash(str, HT_PRIME2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

// Insert a key-value pair into the hash table (open addressing with double hashing)
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    size_t index = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    size_t attempt = 1;
    while (cur_item != NULL) {
        index = ht_get_hash(item->key, ht->size, attempt);
        cur_item = ht->items[index];
        ++attempt;
    }
    ht->items[index] = item;
    ++(ht->count);
}

// Return the item's value if found otherwise return NULL
