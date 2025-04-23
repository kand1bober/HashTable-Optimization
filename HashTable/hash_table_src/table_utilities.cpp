#include "../hash_table_headers/table_utilities.h"

HashTableInfo GetFileInfo (TextInfo* text_info, const char* filename, const char* open_mode)
{
    text_info->file = fopen(filename, open_mode);
    if (!text_info->file)
    {
        printf("Error in opening file\n");
        exit(1);
    }

    struct stat file_info = {};
    stat(filename, &file_info);
    text_info->size = (unsigned long int)(file_info.st_size) + 1; // + final '\0';

    return kGoodTable;
}


HashTableInfo OpenFile (TextInfo* text_info, const char* filename, const char* open_mode)
{
    switch (*open_mode)
    {
        case 'r': //read
        {
            GetFileInfo(text_info, filename, "r");

            text_info->array = (char*)malloc(text_info->size);
            if (!text_info->array)
            {
                printf("\nError in allocating memory\n");
                exit(1);
            }
            
            fseek(text_info->file, 0, SEEK_SET);
            fread(text_info->array, sizeof(char), text_info->size, text_info->file);

            break;
        }
        case 'w': //write
        {
            GetFileInfo(text_info, filename, "w");
            text_info->size = 0;

            break;      
        }
        case 'f': // open for reading(not clearing insides), get file info 
        {
            GetFileInfo(text_info, filename, "r");
        }
    }

    return kGoodTable;
}



HashTableInfo DeleteSlashN (TextInfo* text_info)
{
    char* text_ptr = text_info->array;
    char ch = 0;    
    size_t word_counter = 0;
    for (size_t i = 0; i < text_info->size; i++)
    {
        ch = *(text_ptr + i);
        if (ch == '\n')
        {
            *(text_ptr + i) = '\0';
            word_counter++;
        }
    }

    text_info->words_count = word_counter;

    return kGoodTable;
}


HashTableInfo GetCmdArguments (int argc, char* argv[], ProgConfig* config)
{
    for(int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-searches"))
        {
            i++;
            config->searches = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-runs"))
        {
            i++;
            config->runs = atoi(argv[i]);
        }
        else
        {
            printf("iter %d\n", i);
            printf("Wrong argument\n");
            exit(1);
        }
    }

    return kGoodTable;
}


/*
*  normal(left shift), no reverse
*
* return value should be divided into size of certain table
*/
uint32_t CRC32 (const char* data, int data_length)   
{
    uint32_t crc = 0xFFFFFFFF;
    
    for (int i = 0; i < data_length; i++)
    {
        crc ^= data[i];
        
        for (int j = 0; j < 8; j++) 
        {
            uint32_t mask = -(crc & 1);  // 0xFFFFFFFF если бит=1, иначе 0
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }
    
    crc = ~crc;

    return crc;
}


/*
* Create key, but not divided by size of table 
*
* return value should be divided into size of certain table
*/
uint32_t IntrinCRC32 (const char* word, int word_length)
{ 
    uint64_t crc_init[2] = {0};
    memcpy(crc_init, word, word_length);  
    
    uint32_t key = _mm_crc32_u64(-1, crc_init[0]);
    key += _mm_crc32_u64(-1, crc_init[1]);

    return key;
}
