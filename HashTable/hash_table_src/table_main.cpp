#include "../hash_table_headers/hash_table.h"

int main ()
{
    HashTable_t fast_table = {}; 
    HashTable_t slow_table = {};
    HashTableCtor(&fast_table); 
    HashTableCtor(&slow_table);

    TableInput(&fast_table, &slow_table);

    TableDump(&fast_table);
    
    // WorkTableTest(&fast_table, &slow_table);

    SearchTableTest(&fast_table, &slow_table); //many searches 

    HashTableDtor(&fast_table);
    HashTableDtor(&slow_table);

    return 0;
}
