#include "../hash_table_headers/hash_table.h"

int main ()
{
    HashTable_t fast_table = {}; 
    HashTable_t slow_table = {};

    TextInfo text_info = {};       
    TableInput (&text_info, &fast_table, &slow_table);

    return 0;
}