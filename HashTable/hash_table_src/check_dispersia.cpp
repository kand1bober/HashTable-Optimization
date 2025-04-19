#include "../hash_table_headers/table_funcs.h"

#define kOutputFile "/home/vyacheslav/HashTable/HashTable/analyzis/dispersia_2.csv"

int CheckTableDispersia (HashTable_t* table)
{
    FILE* output_file = fopen(kOutputFile, "w");

    char* data = (char* )calloc(kUsedCaseSize * 30, sizeof(char));
    if (!data)
    {
        printf("Error in allocating memory");
        exit(1);
    }

    size_t offset = 0;

    char line[30] = {};

    sprintf(data, "bucket_num,bucket_size\n");
    offset += strlen(data);
    for (size_t i = 0; i < kUsedCaseSize; i++)
    {
        sprintf(line, "%lu, %d\n", i, table->array[i].bucket_size);
        sprintf(data + offset, "%s", line);
        offset += strlen(line);
    }
    fwrite(data, sizeof(char), offset, output_file);

    free(data);
    fclose(output_file);

    return 0;
}
