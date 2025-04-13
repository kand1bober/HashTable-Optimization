#include "parser.h"
#include <cstdio>

int main()
{   
    TextInfo src_info = {};
    TextInfo out_info = {};

    FileOpening (&src_info, &out_info);

    SeparateWords (&src_info, &out_info);

    FileClosing (&src_info, &out_info);

    return 0;
}


int FileOpening (TextInfo* src_info, TextInfo* out_info)
{
    src_info->file = fopen (kPathToSrcFile, "r");
    out_info->file = fopen (kPathToOutFile, "w");

    struct stat src_file_info = {};
    stat (kPathToSrcFile, &src_file_info);
    src_info->size = (unsigned long int)src_file_info.st_size;

    src_info->array = (char*)malloc (src_info->size * sizeof(char));
    fread (src_info->array, sizeof(char), src_info->size, src_info->file);

    out_info->array = (char*)malloc (src_info->size * sizeof(char));

    return 0;
}


int FileClosing (TextInfo* src_info, TextInfo* out_info)
{
    fclose (src_info->file);
    free (src_info->array);

    fclose (out_info->file);
    free (out_info->array);

    return 0;
}


int SeparateWords (TextInfo* src_info, TextInfo* out_info)
{   
    char ch = 0;
    for(int src_i = 0, out_i = 0; src_i < strlen(src_info->array); src_i++, out_i++)
    {
        if (isalpha(*(src_info->array + src_i)))
        {   
            ch = *(src_info->array + src_i);
            fprintf(out_info->file, "%c", ch);
        }
        else 
        {
            fprintf(out_info->file, "\n");  
            while (!isalpha(*(src_info->array + src_i)))
            {
                src_i++;
            }
            src_i--;
        }
    }

    return 0;
}       


