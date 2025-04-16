#include "../hash_table_headers/hash_table.h"
#include <cstdio>


HashTableInfo HashTableCtor (HashTable_t* table)
{
    table->array = (HashTableElem* )malloc (sizeof(HashTableElem) * kUsedCaseSize);
    table->array_size = kUsedCaseSize;

    if (!table->array)
    {
        printf ("\nError in memory allocating\n");
        exit (1);
    }
    else
    {
        return kGoodTable;
    }
}


HashTableInfo HashTableDtor (HashTable_t* table)
{
    free (table->array);

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

    //-------------------------------------------
    text_info.file = fopen (kParsedFile, "r");

    struct stat file_info = {};

    stat (kParsedFile, &file_info);

    text_info.size = (unsigned long int)file_info.st_size + 1; // + final '\0';
 
    text_info.array = (char*)malloc (text_info.size);
    if (!text_info.array)
    {
        printf ("\nError in allocating memory\n");
        exit (1);
    }
    
    // printf ("\n\narray: %p\nfile: %p\nsize: %lu\n\n", text_info.array, text_info.file, text_info.size);
    fseek (text_info.file, 0, SEEK_SET);
    fread (text_info.array, sizeof(char), text_info.size, text_info.file);
    //-------------------------------------------

    //-------------------------------------------
    char* text_ptr = text_info.array;
    char ch = 0;    
    size_t word_counter = 0;
    for (size_t i = 0; i < text_info.size; i++)
    {
        ch = *(text_ptr + i);
        if (ch == '\n')
        {
            *(text_ptr + i) = '\0';
            word_counter++;
        }
    }
    // printf("======= WORDS: %lu ==========\n", word_counter);
    text_info.words_count = word_counter;
    //-------------------------------------------

    LoadTable (&text_info, fast_table, slow_table);

    fclose (text_info.file);
    free (text_info.array);

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
    char word[kLongestWord] = {};
    size_t shift = 0;
    int word_length = 0;
    for (size_t i = 0; i < text_info->words_count; i++)
    {
        word_length = strlen (text_info->array + shift); // measure word length + '\0'
        strncpy (word, text_info->array + shift, word_length); // take the word 
        shift += (word_length) + 1; // shift = skip word + '\0'
        
        // if (word_length <= kFastTableMaxLen)
        // {
        //     TableAdd (word, fast_table);
        // }
        // else 
        // {
        //     TableAdd (word, slow_table);
        // }

        TableAdd (word, fast_table);
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
HashTableInfo TableAdd (const char* data, HashTable_t* table)
{
    uint32_t key = MurmurHash2 (data, strlen(data));   
    int number = 0;  

    if (FindNode (table->array[key].bucket, data, &number) == kNodeNotFound)
    {
        printf("=======HUY 1=========");
        printf ("%s\n", data);
        getchar ();
        AddNode (table->array[key].bucket, data, table->array[key].bucket_size); //push new node to the end of bucket 
        table->array[key].bucket_size++;
    }
    else 
    {
        printf("=======HUY 2=========");

        GetNode (table->array[key].bucket, number)->data.reps++; //increment counter
    }       
                    
    return kGoodTable;
}


/*
* 1st arg -- ptr to string
*
* 2nd arg -- lentgh of string 
*
* return -- num of bucket 
*/
uint32_t MurmurHash2 (const char* key, unsigned int len)
{
    const uint32_t m = 0x5bd1e995;
    const uint32_t seed = 0;
    const uint32_t r = 24;

    uint32_t h = seed ^ len;

    const unsigned char * data = (const unsigned char *)key;
    uint32_t k = 0;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];        
         
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    h = h % kUsedCaseSize;   // this part is not from original murmur 

    return h;
}


//returns index of elem in array of hash table 
HashTableInfo TableSearch (const char* to_search, size_t* found, HashTable_t* table)
{
    *found = 0;

    uint32_t key = MurmurHash2 (to_search, strlen(to_search) );   
    int number = 0;  

    if (FindNode (table->array[key].bucket, to_search, &number) == kNodeNotFound)
        return kElemNotFound;  
    else 
        return kElemFound;
        // GetNode (table->array[key].bucket, number);    //increment counter
}
