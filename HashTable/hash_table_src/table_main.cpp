#include "../hash_table_headers/hash_table.h"

int main ()
{
    HashTable_t fast_table = {}; 
    HashTable_t slow_table = {};
    HashTableCtor (&fast_table); 
    HashTableCtor (&slow_table);

    TableInput (&fast_table, &slow_table);

    HashTableDtor (&fast_table);
    HashTableDtor (&slow_table);

    return 0;
}
