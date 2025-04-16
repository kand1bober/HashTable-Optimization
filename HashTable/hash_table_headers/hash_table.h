#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <xmmintrin.h>
#include <immintrin.h>

#include "../../List/list_headers/list_func.h"

#ifndef HASH_TABLE_HEADER
#define HASH_TABLE_HEADER

#define kUsedCaseSize 160000
#define kParsedFile "/home/vyacheslav/HashTable/resources/Lotr_parsed.txt"
#define kFastTableMaxLen 32
#define kLongestWord 50

typedef uint32_t Key_t;             // murmur hash gives 

typedef struct 
{
    FILE* file;
    size_t size;
    char* array;
    size_t words_count;
} TextInfo;

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
    HashTableElem* array;
    size_t array_size;
} HashTable_t;


HashTableInfo HashTableCtor (HashTable_t* table);

HashTableInfo HashTableDtor (HashTable_t* table);

HashTableInfo TableSearch (const char* to_search, size_t* found, HashTable_t* table);

uint32_t MurmurHash2 (const char* key, unsigned int len);

HashTableInfo TableInput (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo LoadTable (TextInfo* text_info, HashTable_t *fast_table, HashTable_t *slow_table);

HashTableInfo TableAdd (const char* data, HashTable_t* table);

#endif
