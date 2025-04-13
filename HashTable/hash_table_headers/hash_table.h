#include <stdint.h>
#include <string.h>
#include <x86intrin.h>
#include <xmmintrin.h>
#include <immintrin.h>

#include "../../List/list_headers/list_func.h"

#ifndef HASH_TABLE_HEADER
#define HASH_TABLE_HEADER

#define used_case_size 160000;

typedef uint32_t Key_t;             // murmur hash gives 

typedef enum 
{
    kGoodTable = 1,
    kBadTable = 2,
    kElemFound,
    kElemNotFound,
} HashTableInfo;

typedef struct
{
    uint64_t key;
    uint32_t bucket_size;
    List* bucket;   // bucket = list of strings
} HashTableElem;

typedef struct
{
    HashTableElem* data_array;    //contains all strings present in hash table
    size_t data_array_size;

    HashTableElem* array;
    size_t array_size;
} HashTable_t;


HashTable_t* HashTableCtor ();
HashTableInfo HashTableDtor (HashTable_t* table);
HashTableInfo TableAdd (const char* data, HashTable_t* table);
HashTableInfo TableSearch (const char* to_search, size_t* found, HashTable_t* table);

uint32_t MurmurHash2 (const char* key, unsigned int len);

#endif
