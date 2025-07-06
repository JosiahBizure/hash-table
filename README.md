# hash-table
Simple hash table implementation in C.


## Goals

- Implement an associative array (map) from scratch
- Understand how hashing and collision resolution work for key-value storage
- Practice C fundamentals (memory, structs, and pointers)

## Supported Operations

- `insert(a, k, v)` – Store a string key-value pair
- `search(a, k)` – Retrieve the value for a given key
- `delete(a, k)` – Remove a key-value pair by key

## Constraints

- Keys and values are ASCII strings
- Hash table has a fixed capacity (no resizing)

## Project Structure

├── hash_table.c
├── hash_table.h
├── main.c

## Build and Run

gcc -Wall -Werror hash_table.c main.c -o main
./main