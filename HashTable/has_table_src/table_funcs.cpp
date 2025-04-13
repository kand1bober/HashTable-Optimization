#include "../hash_table_headers/hash_table.h"


HashTable_t* HashTableCtor ()
{
    HashTable_t* table = (HashTable_t* )malloc( sizeof(List) + sizeof(Key_t) );
    table->data_array_size = 0;
    table->array_size = used_case_size;

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

    h = h % used_case_size;   // this part is not from original murmur 

    return h;
}


//returns index of elem in array of hash table 
HashTableInfo TableSearch (const char* to_search, size_t* found, HashTable_t* table)
{
    size_t index = 0;
    *found = 0;

    uint32_t key = MurmurHash2 (to_search, strlen(to_search) );   
    int number = 0;  

    if (FindNode (table->array[key].bucket, to_search, &number) == kNodeNotFound )
        return kElemNotFound;  
    else 
        return kElemFound;
        // GetNode (table->array[key].bucket, number);    //increment counter
}
