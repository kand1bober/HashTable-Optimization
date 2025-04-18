#include "../hash_table_headers/hash_table.h"


HashTableInfo HashTableCtor (HashTable_t* table)
{   
    table->array = (HashTableElem* )calloc (kUsedCaseSize, sizeof(HashTableElem)); // allocating memory for storing pointers to lists
    table->array_size = kUsedCaseSize;

    for (size_t i = 0; i < kUsedCaseSize; i++)
    {
        table->array[i].bucket = ListCtor(); // add phantom element 
        table->array[i].bucket_size = 0;
    }

    if (!table->array)
    {
        printf("\nError in memory allocating\n");
        exit(1);
    }
    else
    {
        return kGoodTable;
    }
}


HashTableInfo HashTableDtor (HashTable_t* table)
{
    for (size_t i = 0; i < kUsedCaseSize; i++)
    {
        ListDtor(table->array[i].bucket);
    }

    free(table->array);

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

    //------------------OPEN---------------------
    text_info.file = fopen(kParsedFile, "r");

    struct stat file_info = {};

    stat(kParsedFile, &file_info);

    text_info.size = (unsigned long int)file_info.st_size + 1; // + final '\0';
 
    text_info.array = (char*)malloc(text_info.size);
    if (!text_info.array)
    {
        printf("\nError in allocating memory\n");
        exit(1);
    }
    
    fseek(text_info.file, 0, SEEK_SET);
    fread(text_info.array, sizeof(char), text_info.size, text_info.file);
    //-------------------------------------------

    //--------------Delete '\n'------------------
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
    text_info.words_count = word_counter;
    //-------------------------------------------

    LoadTable(&text_info, fast_table, slow_table);

    fclose(text_info.file);
    free(text_info.array);

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
    char word[kLongestWord] = {0};
    size_t shift = 0;
    int word_length = 0;
    for (size_t i = 0; i < text_info->words_count; i++)
    {
        word_length = strlen(text_info->array + shift) + 1; // measure word length + '\0'
        strncpy(word, text_info->array + shift, word_length); // take the word 
        shift += (word_length); // shift = skip word + '\0'
        
        // if (word_length <= kFastTableMaxLen)
        // {
        //     TableAdd (word, word_length, fast_table);
        // }
        // else 
        // {
        //     TableAdd (word, word_length, slow_table);
        // }

        TableAdd(word, word_length, fast_table);
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
HashTableInfo TableAdd(const char* word, int word_length, HashTable_t* table)
{
    uint32_t key = MurmurHash2 (word, word_length - 1);   

    int number = 0;
    number = ListFindNode (table->array[key].bucket, word);
    if (number >= 0) //if same element in bucket exists
    {
        ListGetNode(table->array[key].bucket, number)->word_reps++; //increment counter
    }
    else  
    {
        ListAdd (table->array[key].bucket, word, table->array[key].bucket_size); //push new node to the end of bucket 
        table->array[key].bucket_size++;
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


HashTableInfo TableDump (HashTable_t* table)
{   
    TextInfo output_info = {};
    //------------------OPEN---------------------
    output_info.file = fopen(kDumpFile, "w");

    struct stat file_info = {};

    stat(kParsedFile, &file_info);

    output_info.size = (unsigned long int)file_info.st_size * 2; // с запасом (так называемым горемыкой) 

    fseek(output_info.file, 0, SEEK_SET);
    fread(output_info.array, sizeof(char), output_info.size, output_info.file);

    size_t table_data_shift = 0;
    char* table_data = (char*)calloc(output_info.size, sizeof(char));
    if (!table_data)
    {
        printf("\nError in allocating memory\n");
        exit(1);
    }
    //-------------------------------------------      

    //-------------Write in file------------------      
    char dump_head[30] = {0}; //number of bucket

    char* word = nullptr; // pointer to node data 
    char* list_data = (char*)calloc(3000, sizeof(char)); //string with data of each node one after another
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

    return kGoodTable;
}


/*
* 1st arf -- hashtable, where to search //TODO: fast and slow instead of one 
*
* 2nd arg -- word to search 
* 
* 3rd arg -- index of word in this bucket 
*
* return = number of bucket, if found; if not, then return < 0
*/
size_t TableSearch (HashTable_t* table, const char* to_search, int* bucket_index)
{
    int local_bucket_index = 0;

    // int word_length = strlen(to_search);

    uint32_t key = MurmurHash2 (to_search, strlen(to_search) );   

    local_bucket_index = ListFindNode(table->array[key].bucket, to_search);

    *bucket_index = local_bucket_index;

    return( (local_bucket_index > 0) ? key : -1 );
}


// //===============================================
// HashTableInfo SearchTableTest (HashTable_t* table /*массив со всеми словами (мб без повторов)*/)
// {   
    

//     return kGoodSearchTest;
// }

