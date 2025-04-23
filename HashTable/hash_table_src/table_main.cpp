#include "../../List/list_func.h"
#include "../hash_table_headers/table_utilities.h"

int main (int argc, char* argv[])
{
    ProgConfig config = {};
    GetCmdArguments(argc, argv, &config); //get args

    HashTable_t fast_table = {}; //
    HashTable_t slow_table = {}; //
    HashTableCtor(&fast_table, kFastTableSize);  // create tables 
    HashTableCtor(&slow_table, kSlowTableSize);  //

    TableInput(&fast_table, &slow_table); // input words 

    // TableDump(&fast_table, 50, kDumpFileFastTable); // csv dump 
    // TableDump(&slow_table, 50, kDumpFileSlowTable); // csv dump 

    // TableVerificate(&fast_table, &slow_table); // verificate
    
    NO_TESTS(TableWorkTest(&fast_table, &slow_table);)  //looped search and answer
    
    ON_TESTS(TableSearchTest(&fast_table, &slow_table, &config);) //cycled search and measure time

    // //-------------------------------------------
    // CheckTableDispersia(&fast_table, &slow_table);
    // //-------------------------------------------

    HashTableDtor(&fast_table, kFastTableSize); // destroy tables
    HashTableDtor(&slow_table, kSlowTableSize); // 

    return 0;
}
