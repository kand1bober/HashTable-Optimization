#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <x86intrin.h>
#include <xmmintrin.h>
#include <immintrin.h>

#include "../../List/list_headers/list_func.h"
#include "table_config.h"

#ifndef HASH_TABLE_HEADER
#define HASH_TABLE_HEADER

#define kParsedFile "/home/vyacheslav/HashTable/resources/Lotr_parsed.txt"
#define kDumpFile "/home/vyacheslav/HashTable/HashTable/table_dump/table_dump.csv"

#define kUsedCaseSize 905
#define kFastTableMaxLen 32
#define kLongestWord 70

#define CHOOSE_TABLE(res_table, table_1, table_2, word) \
    if (strlen(word) <= kFastTableMaxLen)               \
        res_table = table_1;                            \
    else                                                \
        res_table = table_2;                            \
        
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
HashTableInfo HashTableCtor (HashTable_t* table);

HashTableInfo HashTableDtor (HashTable_t* table);

HashTableInfo TableInput (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo LoadTable (TextInfo* text_info, HashTable_t *fast_table, HashTable_t *slow_table);

HashTableInfo TableAdd (const char* word, int word_length, HashTable_t* table);

size_t TableSearch (HashTable_t* fast_table, HashTable_t* slow_table, const char* to_search, int* bucket_index);
//-----------------------------------------------

//----------------- Utilities -------------------
HashTableInfo OpenFile (TextInfo* text_info, const char* filename, const char* open_mode);

HashTableInfo GetFileInfo (TextInfo* text_info, const char* filename, const char* open_mode);

HashTableInfo DeleteSlashN (TextInfo* text_info);

HashTableInfo TableDump (HashTable_t* table);

HashTableInfo GetCmdArguments (int argc, char* argv[], ProgConfig* config);
//-----------------------------------------------

//-------------------- DLC ----------------------
HashTableInfo TableWorkTest (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo TableVerificate (HashTable_t* fast_table, HashTable_t* slow_table);

HashTableInfo TableSearchTest (HashTable_t* fast_table, HashTable_t* slow_table, ProgConfig* config);
//-----------------------------------------------

//----------------- Analyze ---------------------
int CheckTableDispersia (HashTable_t* table);
//-----------------------------------------------

//-----------------------------------------------
uint32_t MurmurHash2 (const char* key, unsigned int len);

uint32_t CRC32 (const char* data);

uint32_t AsciiSumHash (const char* data);
//-----------------------------------------------

#endif
