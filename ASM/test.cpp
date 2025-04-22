#include <stdio.h>
#include <string.h> 

extern "C" { int MyStrcmp( const char*, const char*) __attribute__((nonnull(1, 2))); }

int main()
{
    char str1[33] = {};
    char str2[33] = {};

    strcpy(str1, "huy");
    strcpy(str2, "huy"); 
    printf("%d\n", strcmp(str1, str2));
    printf("%d\n\n", MyStrcmp(str1, str2));

    strcpy(str1, "huy");
    strcpy(str2, "nehuy"); 
    printf("%d\n", MyStrcmp(str1, str2));
    printf("%d\n\n", strcmp(str1, str2));

    return 0;
}
