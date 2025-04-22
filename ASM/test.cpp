#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

extern "C" { int MyStrcmp( const char* , const char*); }

int Print(const char* str1, const char* str2);

int main()
{
    char str1[33] = {0};
    char str2[33] = {0};

    memset(str1, 0, 32);
    memset(str2, 0, 32);

    strcpy(str1, "women");
    strcpy(str2, "man");

    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);
    Print(str1, str2);

    return 0;
}

int Print(const char* str1, const char* str2)
{
    printf("%d\n\n", MyStrcmp(str1, str2) );

    return 0;
}
