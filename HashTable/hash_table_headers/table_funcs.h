#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <nmmintrin.h>
#include <mmintrin.h>

#include "../../List/list_func.h"
#include "table_config.h"

#ifndef HASH_TABLE_HEADER
#define HASH_TABLE_HEADER

static const char* kParsedFile = "/home/vyacheslav/HashTable/resources/Lotr_parsed.txt";
static const char* kDumpFileFastTable = "/home/vyacheslav/HashTable/HashTable/table_dump/fast_table_dump.csv";
static const char* kDumpFileSlowTable = "/home/vyacheslav/HashTable/HashTable/table_dump/slow_table_dump.csv";

#define kFastTableSize 900
#define kSlowTableSize 1

#define kFastTableMaxLen 16 // this separation caused by "MyStrcmp" work mechanic
#define kLongestWord 70

typedef struct 
{
    FILE* file;
    size_t size;
    size_t words_count;
    char* array; 
} TextInfo; // file and it's text in array

typedef struct
{
    int runs;
    int searches;
}ProgConfig;

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

//------------- Main functions ------------------
HashTableInfo HashTableCtor (HashTable_t* table, size_t table_size);

HashTableInfo HashTableDtor (HashTable_t* table, size_t table_size);

HashTableInfo TableInput (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo LoadTable (TextInfo* text_info, HashTable_t *fast_table, HashTable_t *slow_table);

HashTableInfo FastTableAdd(const char* word, int word_length, HashTable_t* fast_table);

HashTableInfo SlowTableAdd(const char* word, int word_length, HashTable_t* slow_table);

size_t TableSearch (HashTable_t* fast_table, HashTable_t* slow_table, const char* to_search, int word_length, int* bucket_index);
//-----------------------------------------------

//----------------- Utilities -------------------
HashTableInfo OpenFile (TextInfo* text_info, const char* filename, const char* open_mode);

HashTableInfo GetFileInfo (TextInfo* text_info, const char* filename, const char* open_mode);

HashTableInfo DeleteSlashN (TextInfo* text_info);

HashTableInfo TableDump (HashTable_t* table, int max_load_factor, const char* dump_file_name);

HashTableInfo GetCmdArguments (int argc, char* argv[], ProgConfig* config);
//-----------------------------------------------

//-------------------- DLC ----------------------

HashTableInfo TableVerificate (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo TableSearchTest (HashTable_t* fast_table, HashTable_t* slow_table, ProgConfig* config);
//-----------------------------------------------

//-------------- Hash Functions -----------------
uint32_t CRC32 (const char* data, int data_length);

uint32_t IntrinCRC32 (const char* word, int word_length);
//-----------------------------------------------

//-----------------------------------------------
int CheckTableDispersia (HashTable_t* fast_table, HashTable_t* slow_table);

void CollectTableData(HashTable_t* table, size_t table_size, const char* dump_file_name);
//-----------------------------------------------

#endif
