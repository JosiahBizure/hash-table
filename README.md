# hash-table
Simple hash table implementation in C. This project is based on the [hash-table tutorial](https://github.com/jamesroutley/write-a-hash-table) from the [project-based-learning](https://github.com/practical-tutorials/project-based-learning?tab=readme-ov-file) repo.


## Goals

- Implement an associative array (map) from scratch
- Understand how hashing and collision resolution work for key-value storage
- Practice C fundamentals (memory, structs, pointers, string manipulation)

## Supported Operations

- `insert(a, k, v)` – Store a string key-value pair
- `search(a, k)` – Retrieve the value for a given key
- `delete(a, k)` – Remove a key-value pair by key

## Constraints

- Keys and values are ASCII strings

## Project Structure

.
├── build
└── src
    ├── hash_table.c
    ├── hash_table.h
    ├── main.c
    ├── prime.c
    └── prime.h

## Build and Run

tbd