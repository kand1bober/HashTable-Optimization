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

#define kUsedCaseSize 1500
#define kParsedFile "/home/vyacheslav/HashTable/resources/Lotr_parsed.txt"
#define kFastTableMaxLen 32
#define kLongestWord 70

#define kDumpFile "/home/vyacheslav/HashTable/HashTable/table_dump/table_dump.csv"

typedef struct 
{
    FILE* file;
    size_t size;
    size_t words_count;
    char* array; 
} TextInfo; // file and it's text in array

typedef enum 
{
    kGoodTable = 6,
    kBadTable,

    kGoodSearchTest,
    kBadSearchTest

} HashTableInfo;

typedef struct
{
    uint32_t bucket_size;
    List_t* bucket;   // bucket = list of strings
} HashTableElem;

typedef struct
{
    size_t array_size;
    HashTableElem* array;
} HashTable_t;


HashTableInfo HashTableCtor (HashTable_t* table);

HashTableInfo HashTableDtor (HashTable_t* table);

HashTableInfo TableInput (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo TableAdd (const char* word, int word_length, HashTable_t* fast_table);

HashTableInfo LoadTable (TextInfo* text_info, HashTable_t *fast_table, HashTable_t *slow_table);

uint32_t MurmurHash2 (const char* key, unsigned int len);

size_t TableSearch (HashTable_t* table, const char* to_search, int* bucket_index);

HashTableInfo TableDump (HashTable_t* table);

#endif
