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
    I learned double pointers by making this struct!

    'items' is a pointer to a pointer to an ht_item — that is, an array of ht_item pointers.
    Each ht_item* in the array may point to an ht_item object located anywhere in memory 
    (stack, heap, or static storage). The pointer array itself may be contiguous (if allocated via calloc),
    but the actual ht_item structs it points to can be scattered.

    This layout allows for flexible allocation and dynamic management of key-value entries.
*/
typedef struct {
    size_t size;   // Total number of buckets
    size_t count;  // Number of keys currently in the hash table
    ht_item** items;
} ht_hash_table;

/*
    I learned that we can choose not to add function declarations to .h files if we want it to be
    private / internal to the .c file. This prevents functionality from being accessible externally.
*/

ht_hash_table* ht_new();  // Allocates and initializes a new hash table
void ht_del_hash_table(ht_hash_table* ht); // Deallocates a hash table's heap memory
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);