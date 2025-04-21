#include "../hash_table_headers/table_funcs.h"

/*
* Simple test of HashTable work concept
*
* To check results, see "table_dump.csv" table
*/
HashTableInfo TableWorkTest (HashTable_t* fast_table, HashTable_t* slow_table)
{
    size_t arr_index = 0;
    int bucket_index = 0;
    char word[kLongestWord] = {0};
    while(1)
    {
        scanf("%s", word);
        getchar();  // skip '\n'
        arr_index = TableSearch(fast_table, slow_table, word, &bucket_index );
        if (arr_index > 0)
        {
            printf("\n---------------\n"
                   "Word found\n"
                   "bucket: %lu\n"
                   "position in bucket: %d\n"
                   "---------------\n", arr_index, bucket_index);
        }
        else  
        {
            printf("WorkTest: No such element in HashTable\n");
        }
    }

    return kGoodTable;
}


HashTableInfo TableDump (HashTable_t* table, int max_load_factor, const char* dump_file_name)
{   
    TextInfo src_info = {};
    OpenFile(&src_info, kParsedFile, "f");  // get info

    TextInfo output_info = {};
    OpenFile(&output_info, dump_file_name, "w");

    size_t table_data_shift = 0;
    char* table_data = (char*)calloc(src_info.size * 2, sizeof(char));
    if (!table_data)
    {
        printf("\nError in allocating memory\n");
        exit(1);
    } 

    //-------------Write in file------------------      
    char dump_head[30] = {0}; //number of bucket

    char* word = nullptr; // pointer to node data 
    char* list_data = (char*)calloc(kLongestWord * max_load_factor, sizeof(char)); //string with data of each node one after another
    int list_data_shift = 0; // offset frpm beggining of string
    List_t* tmp_node = nullptr;
    for (size_t i = 0; i < table->array_size; i++)
    {   
        tmp_node = table->array[i].bucket; 
        word = GET_NODE_DATA(tmp_node);

        for (size_t j = 0; j < table->array[i].bucket_size; j++)
        {
            sprintf(list_data + list_data_shift, "%s, ", word);
            list_data_shift += strlen(word) + 2;
            tmp_node = tmp_node->next;
            word = GET_NODE_DATA(tmp_node);
        }

        sprintf(list_data + list_data_shift, "%s", GET_NODE_DATA(tmp_node));
        list_data_shift += strlen(word);

        sprintf(dump_head, "%lu, ", i);
        sprintf(table_data + table_data_shift, "%s%s\n", dump_head, list_data);
        
        table_data_shift += list_data_shift + strlen(dump_head) + 1;
        list_data_shift = 0;
    }
    
    fwrite(table_data, sizeof(char), table_data_shift, output_info.file);
    //-------------------------------------------      

    free(table_data);
    free(list_data);

    fclose(output_info.file);
    fclose(src_info.file);

    return kGoodTable;
}


/*
* Repeated search of all word from table database in table
* 
* 1st & 2nd args -- tables, where to search 
*
* 3rd arg --
*/
HashTableInfo TableVerificate (HashTable_t* fast_table, HashTable_t* slow_table)
{   
    TextInfo text_info = {};

    OpenFile(&text_info, kParsedFile, "r");
    DeleteSlashN(&text_info);

    int word_length = 0;
    char* text_ptr = nullptr;

    size_t arr_index = 0;
    int bucket_index = 0;
    char word[kLongestWord] = {0};

    text_ptr = text_info.array;

    for (size_t i = 0; i < text_info.words_count; i++)
    {
        word_length = strlen(text_ptr);
        strncpy(word, text_ptr, word_length + 1);
        arr_index = TableSearch(fast_table, slow_table, word, &bucket_index);

        if (arr_index > 10000000) //impossible value for table 
        {
            printf("Verification: No such element in HashTable\n");
            exit(1);
        }

        text_ptr += word_length + 1;
    }

    printf("=========== VERIFICATION ============\n"
           "Search in HashTable works correctly !\n");

    free(text_info.array);
    fclose(text_info.file);

    return kGoodSearchTest;
}
 

/*
* Repeated search of all word from table database in table? but not checking for correctness
* 
* 1st & 2nd args -- tables, where to search 
*
* 3rd arg --
*/
HashTableInfo TableSearchTest (HashTable_t* fast_table, HashTable_t* slow_table, ProgConfig* config)
{   
    TextInfo text_info = {};

    OpenFile(&text_info, kParsedFile, "r");
    DeleteSlashN(&text_info);

    int word_length = 0;
    char* text_ptr = nullptr;

    int bucket_index = 0;
    char word[kLongestWord] = {0};

    int runs = config->runs;
    int searches = config->searches;

    // uint64_t ticks_start = 0, ticks_end = 0;

    printf("\n===============TESTS================\n"
            "runs: %d, searches: %d\n\n", config->runs, config->searches);
    for (int k = 0; k < runs; k++)
    {
        // ticks_start = __rdtsc();
        for (int j = 0; j < searches; j++)
        {
            text_ptr = text_info.array;

            for (size_t i = 0; i < text_info.words_count; i++)
            {
                word_length = strlen(text_ptr);
                strncpy(word, text_ptr, word_length + 1);
                TableSearch(fast_table, slow_table, word, &bucket_index);

                text_ptr += word_length + 1;
            }
        }
        // ticks_end = __rdtsc();

        // printf("%d time for one full run: %lu\n", k, (ticks_end - ticks_start) / searches );
    }
    printf("=====================================\n");

    free(text_info.array);
    fclose(text_info.file);

    return kGoodSearchTest;
}

