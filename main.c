#include <stdio.h>
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();

    // Insert key-value pairs
    ht_insert(ht, "name", "Joe");
    ht_insert(ht, "language", "C");
    ht_insert(ht, "project", "hash table");

    // Search for existing keys
    printf("name: %s\n", ht_search(ht, "name"));         // Expect "Joe"
    printf("language: %s\n", ht_search(ht, "language")); // Expect "C"
    printf("project: %s\n", ht_search(ht, "project"));   // Expect "hash table"

    // Update an existing key
    ht_insert(ht, "name", "Code");
    printf("updated name: %s\n", ht_search(ht, "name")); // Expect "Code"

    // Delete a key and try to retrieve it
    ht_delete(ht, "language");
    printf("deleted language: %s\n", ht_search(ht, "language")); // Expect "(null)"

    // Try searching for a key that was never inserted
    printf("missing key: %s\n", ht_search(ht, "unknown")); // Expect "(null)"

    ht_del_hash_table(ht);
    return 0;
}