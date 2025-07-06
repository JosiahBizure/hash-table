#include <stdlib.h>

typedef struct {
    char* key;
    char* value;
} ht_item;

/*
    This helped me understand double pointers a bit better.

    'items' is a pointer to an ht_item pointer, meaning, an array of ht_item pointers.
    Each ht_item* in the array can point to an ht_item object located anywhere in memory 
    (stack, heap, or static storage). The pointer array itself may be contiguous,
    but the actual ht_item structs it points to can be scattered.
*/
typedef struct {
    size_t size;   // Total number of buckets
    size_t count;  // Number of keys currently in the hash table
    ht_item** items; // Array of ht_item*
} ht_hash_table;

/*
    I'm choosing not to include the ht_item constructor / destructor logic to this file to keep it
    private / internal to the .c file. This prevents functionality from being accessible externally.
*/

ht_hash_table* ht_new();  // Allocates and initializes a new hash table
void ht_del_hash_table(ht_hash_table* ht); // Deallocates a hash table's heap memory
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);