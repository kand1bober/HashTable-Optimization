#include <stdio.h>
#include <string.h>
#include <immintrin.h>

int CustomStrcmp (const char* a, int len_a, const char* b, int len_b)
{
    __m128i str_a = _mm_loadu_si128((const __m128i*)a);
    __m128i str_b = _mm_loadu_si128((const __m128i*)b);

    int result = _mm_cmpestri(str_a, len_a, str_b, len_b, _SIDD_CMP_EQUAL_ORDERED | _SIDD_UBYTE_OPS);

    return result;
}


int main()
{
    printf("%d %d\n", strcmp("man", "man"), CustomStrcmp("women", 5, "women", 5));

    return 0;
}
