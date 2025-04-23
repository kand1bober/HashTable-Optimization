#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

extern "C" { int MyStrcmp( const char* , int, const char* , int); }

int Print(const char* str1, const char* str2);

int main()
{
    printf("%d %d\n", strcmp("man", "man"), MyStrcmp("fomen", 5, "women", 5));

    return 0;
}
