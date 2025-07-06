#include <string.h>
#include <math.h>

#include "hash_table.h"

static const size_t HT_PRIME1 = 151;
static const size_t HT_PRIME2 = 163;

// Global sentinel item that represents a bucket which contains a deleted item
// See ht_delete for description of why this is needed
static ht_item HT_DELETED_ITEM = {NULL, NULL};

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
    free(item); // Can't forget the item itself
}

// Deletes an ht_hash_table by freeing its allocated memory
void ht_del_hash_table(ht_hash_table* ht) {
    ht_item* item = NULL; // We reassign in the next line so this should be safe
    for (size_t i = 0; i < ht->size; ++i) {
        item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) { ht_del_item(item); }
    }

    free(ht->items);
    free(ht);
}

// Polynomial string hashing function (variation of base-`a` positional hashing)
//
// Each character in the string contributes to the final hash value, weighted by its position.
// Using a base `a` > 128 (prime) helps spread values out better in the hash space.
// The result is modded by `num_buckets` to ensure it maps to a valid index.
//
// This improves distribution from the standard summing ASCII values approach.
static size_t ht_hash(const char* str, const size_t a, const size_t num_buckets) {
    size_t hash = 0;
    const size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
        hash += (size_t)pow(a, len - (i+1)) * str[i];
        hash = hash % num_buckets;
    }
    return hash;
}

// Secondary hashing function used for double hashing collision resolution
//
// Given a key and an "attempt" number, compute a new index each time we collide.
// This approach ensures repeated collisions don’t land near each other.
//
// hash_i(key) = (hash_a(key) + attempt * (hash_b(key) + 1)) % num_buckets
// We add 1 to hash_b to avoid multiplying by 0 and generating the same result over and over.
static size_t ht_get_hash(const char* str, const size_t num_buckets, const size_t attempt) {
    const size_t hash_a = ht_hash(str, HT_PRIME1, num_buckets);
    const size_t hash_b = ht_hash(str, HT_PRIME2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

// Insert a key-value pair into the hash table (open addressing with double hashing)
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // Create a new key-value item
    ht_item* item = ht_new_item(key, value);

    // Compute the initial index using the primary hash function
    size_t index = ht_get_hash(key, ht->size, 0);
    ht_item* cur_item = ht->items[index];

    // Initialize the collision probe counter
    size_t attempt = 1;

    // Probe until we find an empty slot using double hashing algorithm
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        // If key already exists in the table, update it the new value
        if (strcmp(cur_item->key, key) == 0) {
            ht_del_item(cur_item);
            ht->items[index] = item;
            return;
        }

        index = ht_get_hash(key, ht->size, attempt);
        cur_item = ht->items[index];
        ++attempt;
    }

    // Insert the new item and update the count
    ht->items[index] = item;
    ++(ht->count);
}

// Return the item's value if found otherwise return NULL
char* ht_search(ht_hash_table* ht, const char* key) {
    // Compute the initial index using the primary hash function
    size_t index = ht_get_hash(key, ht->size, 0);

    // Retrieve the item at that index
    ht_item* item = ht->items[index];
    size_t attempt = 1;

    // If item is NULL then we've checked all possible buckets and the
    // key isn't in the table. Return NULL. 
    // Otherwise, continue searching until the key-value pair is found
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = ht_get_hash(key, ht->size, attempt);
        item = ht->items[index];
        ++attempt;
    }
    return NULL;
}

/*
    I had to look up how to handle deletions from an open addressed hash table
    because it is complicated. It's possible that the item we want to delete
    is part of a collision chain. Removing it directly will break that chain.
    The solution I found is to create a global sentinel item which represents
    a bucket containing a deleted item and replace the target item with a pointer
    to that global item
*/

void ht_delete(ht_hash_table* ht, const char* key) {
    // Compute the initial index using the primary hash function
    size_t index = ht_get_hash(key, ht->size, 0);

    // Retrieve the item at that index
    ht_item* item = ht->items[index];
    size_t attempt = 1;

    while (item != NULL) {
        if (item != &HT_DELETED_ITEM && strcmp(item->key, key) == 0) {
            ht_del_item(item); // only safe if not the sentinel
            ht->items[index] = &HT_DELETED_ITEM;
            --(ht->count);
            return;
        }

        index = ht_get_hash(key, ht->size, attempt);
        item = ht->items[index];
        ++attempt;
    }
}