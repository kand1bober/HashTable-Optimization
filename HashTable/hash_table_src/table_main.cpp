#include "../hash_table_headers/table_funcs.h"
#include "../hash_table_headers/table_utilities.h"

int main (int argc, char* argv[])
{
    ProgConfig config = {};
    GetCmdArguments(argc, argv, &config); //get args

    HashTable_t fast_table = {}; //
    HashTable_t slow_table = {}; //
    HashTableCtor(&fast_table);  // create tables 
    HashTableCtor(&slow_table);  //

    TableInput(&fast_table, &slow_table); // input words 

    printf("========= MAAAAAAAAAAAN success! =============\n");

    // TableVerificate(&fast_table, &slow_table); // verificate

    TableDump(&fast_table); // csv dump 
    
    NO_TESTS(TableWorkTest(&fast_table, &slow_table);)  //looped search and answer
    
    ON_TESTS(TableSearchTest(&fast_table, &slow_table, &config);) //cycled search and measure time

    // //-------------------------------------------
    // CheckTableDispersia (&fast_table);
    // //-------------------------------------------

    HashTableDtor(&fast_table); // destroy tables
    HashTableDtor(&slow_table); // 

    return 0;
}
