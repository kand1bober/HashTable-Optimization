#ifndef TEXT_PARSER_HEADER
#define TEXT_PARSER_HEADER

#include <sys/stat.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define kPathToSrcFile "/home/vyacheslav/HashTable/resources/Lotr_orig.txt" 
#define kPathToOutFile "/home/vyacheslav/HashTable/resources/Lotr_parsed.txt" 

typedef struct 
{
    FILE* file;
    size_t size;
    char* array;    
} TextInfo;

int FileOpening (TextInfo* src_info, TextInfo* out_info);
int FileClosing (TextInfo* src_info, TextInfo* out_info);

int SeparateWords (TextInfo* src_info, TextInfo* out_info);


#endif
