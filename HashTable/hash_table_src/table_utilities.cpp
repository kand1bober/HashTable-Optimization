#include "../hash_table_headers/table_funcs.h"

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

