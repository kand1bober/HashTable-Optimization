#include "../hash_table_headers/table_funcs.h"


HashTableInfo HashTableCtor (HashTable_t* table, size_t table_size)
{   
    table->array = (HashTableElem* )calloc (table_size, sizeof(HashTableElem)); // allocating memory for storing pointers to lists
    table->array_size = table_size;

    for (size_t i = 0; i < table_size; i++)
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


HashTableInfo HashTableDtor (HashTable_t* table, size_t table_size)
{
    for (size_t i = 0; i < table_size; i++)
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
        word_length = MyStrlen(text_info->array + offset); // measure word length without '\0'
        if (word_length == 32)
        {
            word_length = word_length = strlen(text_info->array + offset);
        }

        strncpy(word, text_info->array + offset, word_length + 1); // take the word with '\0'
        offset += (word_length + 1); // offset = skip word + '\0'
        
        if (word_length <= kFastTableMaxLen)
        {
            FastTableAdd (word, word_length, fast_table);
        }
        else 
        {
            SlowTableAdd (word, word_length, slow_table);
        }
    }

    return kGoodTable;          
}


/*
* 1st arg -- string to add in hash table
*
* 2nd arg -- string length without '\0'
*
* 3rd arg -- ptr to fast table (word length <= max len)
*
* result -- new string added or existing string counter incremented  
*/
HashTableInfo FastTableAdd(const char* word, int word_length, HashTable_t* fast_table) 
{
    uint32_t key = IntrinCRC32(word, word_length) % kFastTableSize;

    HashTableElem table_position = fast_table->array[key];
 
    int number = FastListFindNode(table_position.bucket, table_position.bucket_size, word, word_length);

    if (number >= 0) //if same element in bucket exists
    {
        ListGetNode(table_position.bucket, number)->word_reps++; //increment counter
    } 
    else  
    {
        ListAdd (table_position.bucket, word, table_position.bucket_size); //push new node to the end of bucket 
        fast_table->array[key].bucket_size++;
    }

    return kGoodTable; 
}


/*
* 1st arg -- string to add in hash table
*
* 2nd arg -- string length without '\0'
*
* 3rd arg -- ptr to slow table (word length <= max len)
*
* result -- new string added or existing string counter incremented  
*/
HashTableInfo SlowTableAdd(const char* word, int word_length, HashTable_t* slow_table)
{
    uint32_t key = CRC32(word, word_length) % kSlowTableSize; 

    HashTableElem table_position = slow_table->array[key];

    int number = SlowListFindNode (table_position.bucket, table_position.bucket_size, word, word_length);

    if (number >= 0) //if same element in bucket exists
    {
        ListGetNode(table_position.bucket, number)->word_reps++; //increment counter
    } 
    else  
    {
        ListAdd (table_position.bucket, word, table_position.bucket_size); //push new node to the end of bucket 
        slow_table->array[key].bucket_size++;
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
size_t TableSearch (HashTable_t* fast_table, HashTable_t* slow_table, 
                    const char* to_search, int word_length, int* bucket_index)
{
    int local_bucket_index = 0;
    uint32_t key = 0;

    if (word_length <= kFastTableMaxLen)
    {  
        key = IntrinCRC32(to_search, word_length) % kFastTableSize;

        HashTableElem table_position = fast_table->array[key];

        local_bucket_index = FastListFindNode(table_position.bucket, table_position.bucket_size, to_search, word_length); 
    }
    else 
    {
        key = CRC32(to_search, word_length) % kSlowTableSize;

        HashTableElem table_position = slow_table->array[key];

        local_bucket_index = SlowListFindNode(table_position.bucket, table_position.bucket_size, to_search, word_length);
    }

    *bucket_index = local_bucket_index;

    return( (local_bucket_index >= 0) ? key : -1 );
}
