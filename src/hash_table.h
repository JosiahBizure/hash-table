#include <stdlib.h>

/*
    I leanred 'typedef' by making this struct!

    'typedef' allows us to create aliases for types — both built-in and user-defined.
    Here, we define an unnamed struct and simultaneously create an alias for it: ht_item.
    This way, we can declare variables using 'ht_item' instead of 'struct { ... }'.
*/
typedef struct {
    char* key;
    char* value;
} ht_item;

/*
    'items' is a pointer to an ht_item pointer — that is, an array of ht_item pointers.
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
    We can choose not to add function declarations to .h files if we want it to be
    private / internal to the .c file. This prevents functionality from being accessible externally.
*/

ht_hash_table* ht_new();  // Allocates and initializes a new hash table
void ht_del_hash_table(ht_hash_table* ht); // Deallocates a hash table's heap memory
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* ht, const char* key);