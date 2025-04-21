#include "../hash_table_headers/table_funcs.h"

#define kOutputFileFast "/home/vyacheslav/HashTable/hash_table_analyze/dispersia_fast_table.csv"
#define kOutputFileSlow "/home/vyacheslav/HashTable/hash_table_analyze/dispersia_slow_table.csv"

int CheckTableDispersia (HashTable_t* fast_table, HashTable_t* slow_table)
{
    CollectTableData(fast_table, kFastTableSize, kOutputFileFast);
    CollectTableData(slow_table, kSlowTableSize , kOutputFileSlow);

    return 0;
}

void CollectTableData(HashTable_t* table, size_t table_size, const char* dump_file_name)
{   
    FILE* output_file = fopen(dump_file_name, "w");
    if (!output_file)
    {
        perror("Error to open file");
        exit(1);
    }

    char* data = (char* )calloc(table_size * 30, sizeof(char));
    if (!data)
    {
        printf("Error in allocating memory");
        exit(1);
    }

    size_t offset = 0;

    char line[30] = {};

    sprintf(data, "bucket_num,bucket_size\n");
    offset += strlen(data);
    for (size_t i = 0; i < table_size; i++)
    {
        sprintf(line, "%lu, %d\n", i, table->array[i].bucket_size);
        sprintf(data + offset, "%s", line);
        offset += strlen(line);
    }
    fwrite(data, sizeof(char), offset, output_file);

    free(data);
    fclose(output_file);
}
