#include "../hash_table_headers/table_funcs.h"
int main ()
{
    HashTable_t fast_table = {}; 
    HashTable_t slow_table = {};
    HashTableCtor(&fast_table); 
    HashTableCtor(&slow_table);

    TableInput(&fast_table, &slow_table);

    TableVerificate(&fast_table, &slow_table);

    TableDump(&fast_table);
    
    NO_TESTS(TableWorkTest(&fast_table, &slow_table);)  //looped search and answer
    
    ON_TESTS(TableSearchTest(&fast_table, &slow_table);) //cycled search and measure time

    HashTableDtor(&fast_table);
    HashTableDtor(&slow_table);

    return 0;
}
