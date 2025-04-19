#include "../hash_table_headers/table_funcs.h"


HashTableInfo HashTableCtor (HashTable_t* table)
{   
    table->array = (HashTableElem* )calloc (kUsedCaseSize, sizeof(HashTableElem)); // allocating memory for storing pointers to lists
    table->array_size = kUsedCaseSize;

    for (size_t i = 0; i < kUsedCaseSize; i++)
    {
        table->array[i].bucket = ListCtor(); // add phantom element 
        table->array[i].bucket_size = 0;
    }

    if (!table->array)
    {
        printf("\nError in memory allocating\n");
        exit(1);
    }
    else
    {
        return kGoodTable;
    }
}


HashTableInfo HashTableDtor (HashTable_t* table)
{
    for (size_t i = 0; i < kUsedCaseSize; i++)
    {
        ListDtor(table->array[i].bucket);
    }

    free(table->array);

    if (!table->array)
    {
        return kGoodTable;
    }
    else
    {
        return kBadTable;
    }
}


HashTableInfo TableInput (HashTable_t* fast_table, HashTable_t* slow_table)
{
    TextInfo text_info = {};

    OpenFile(&text_info, kParsedFile, "r");

    DeleteSlashN(&text_info);

    LoadTable(&text_info, fast_table, slow_table);

    fclose(text_info.file);
    free(text_info.array);

    return kGoodTable;
}


/*
* 1st arg -- struct with info about input text 
*
* 2nd arg -- ptr to fast version of hash table
*
* 3rd arg -- ptr to slow version of hash table
*/
HashTableInfo LoadTable (TextInfo* text_info, HashTable_t* fast_table, HashTable_t* slow_table)
{
    char word[kLongestWord] = {0};
    size_t offset = 0;
    int word_length = 0;
    for (size_t i = 0; i < text_info->words_count; i++)
    {
        word_length = strlen(text_info->array + offset) + 1; // measure word length + '\0'
        strncpy(word, text_info->array + offset, word_length); // take the word 
        offset += (word_length); // offset = skip word + '\0'
        
        // if (word_length <= kFastTableMaxLen)
        // {
        //     TableAdd (word, word_length, fast_table);
        // }
        // else 
        // {
        //     TableAdd (word, word_length, slow_table);
        // }

        TableAdd(word, word_length, fast_table);
    }

    return kGoodTable;          
}


/*
* 1st arg -- string to add in hash table
*
* 2nd arg -- ptr to certain version of hash table
*
* result -- new string added or existing string counter incremented  
*/
HashTableInfo TableAdd(const char* word, int word_length, HashTable_t* table)
{
    uint32_t key = CRC32(word);
    // uint32_t key = MurmurHash2 (word, word_length - 1);   
    // uint32_t key = AsciiSumHash(word);

    int number = 0;
    number = ListFindNode (table->array[key].bucket, word);
    if (number >= 0) //if same element in bucket exists
    {
        ListGetNode(table->array[key].bucket, number)->word_reps++; //increment counter
    }
    else  
    {
        ListAdd (table->array[key].bucket, word, table->array[key].bucket_size); //push new node to the end of bucket 
        table->array[key].bucket_size++;
    }
       
    return kGoodTable; 
}


/*
* 1st & 2nd args -- hashtables, where to search
*
* 3rd arg -- word to search 
* 
* 4th arg -- index of word in this bucket 
*
* return = number of bucket, if found; if not, then return < 0
*/
size_t TableSearch (HashTable_t* fast_table, HashTable_t* slow_table, const char* to_search, int* bucket_index)
{
    int local_bucket_index = 0;

    // int word_length = strlen(to_search);

    uint32_t key = CRC32(to_search); // 1
    // uint32_t key = MurmurHash2(to_search, strlen(to_search) ); // 2  
    // uint32_t key = AsciiSumHash(to_search); // 3

    local_bucket_index = ListFindNode(fast_table->array[key].bucket, to_search); //поменять при добавлении второй таблицы

    *bucket_index = local_bucket_index;

    return( (local_bucket_index >= 0) ? key : -1 );
}
