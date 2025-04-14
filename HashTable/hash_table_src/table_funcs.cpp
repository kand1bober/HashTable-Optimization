#include "../hash_table_headers/hash_table.h"


HashTable_t* HashTableCtor ()
{
    HashTable_t* table = (HashTable_t* )malloc( sizeof(List) + sizeof(Key_t) );
    table->data_array_size = 0;
    table->array_size = kUsedCaseSize;

    if( !table )
    {
        printf("\nError\n");
        exit(1);
    }

    return table;
}


HashTableInfo HashTableDtor (HashTable_t* table)
{
    free(table->data_array);
    free(table->array);

    if(!table->array & !table->data_array)
    {
        return kGoodTable;
    }
    else 
    {
        return kBadTable;
    }
}


HashTableInfo TableInput (TextInfo* text_info )
{
    FILE* poem_file = fopen (kSrcFile, "rw");

    struct stat file_info = {};

    stat (kSrcFile, &file_info);

    text_info->size = (unsigned long int)file_info.st_size;
 
    text_info->array = (char*)malloc (text_info->size);
    
    fread(text_info->file, sizeof(char), text_info->size, poem_file);

    char* text_ptr = text_info->array;
    char ch = *text_ptr;
    size_t word_counter = 0;
    while (ch != EOF)
    {
        if ( ch == '\n' )
        {
            *text_ptr = '\0';
            word_counter++;
        }

        text_info++;
        ch = *text_ptr;

    }
    text_info->words_count = word_counter;

    return kGoodTable;
}


HashTableInfo LoadTable (TextInfo* text_info, HashTable_t* fast_table, HashTable_t* slow_table)
{
    size_t shift = 0;
    int word_length = 0;
    for (size_t i = 0; i < text_info->words_count; i++)
    {
        word_length = strlen (text_info->array + shift);
        shift += (word_length + 1);

    }

    return kGoodTable;          
}


HashTableInfo TableAdd (const char* data, HashTable_t* table)
{
    uint32_t key = MurmurHash2 (data, strlen(data) );   
    int number = 0;  

    if (FindNode (table->array[key].bucket, data, &number) == kNodeNotFound )
    {
        AddNode (table->array[key].bucket, data, table->array[key].bucket_size);    //push new node to the end of bucket 
        table->array[key].bucket_size++;
    }
    else 
    {
        GetNode (table->array[key].bucket, number)->data.reps++;    //increment counter
    }       
                    
    return kGoodTable;
}


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

    if (FindNode (table->array[key].bucket, to_search, &number) == kNodeNotFound )
        return kElemNotFound;  
    else 
        return kElemFound;
        // GetNode (table->array[key].bucket, number);    //increment counter
}