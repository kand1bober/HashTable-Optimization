#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#include <immintrin.h>
#include <nmmintrin.h>
#include <smmintrin.h>

#ifndef LIST_FUNC_HEADER
#define LIST_FUNC_HEADER

    const char LIST_POISON[] = "BADBABA";

    typedef enum ListInfo
    {
        kGoodList = 52,
        kBadList = 53,
    }ListInfo_t;

    typedef struct List
    {
        struct List* next; 
        struct List* prev;
        int str_len; // without '\0'
        size_t word_reps; // additional info about word 
    } List_t;

    #define GET_NODE_DATA(node_ptr) (char*)node_ptr + sizeof(List_t) // makes offset from struct beginning

    List_t* ListCreateNode (const char* string);

    List_t* ListCtor();

    ListInfo_t ListDtor (List_t* list);

    List_t* ListGetNode (List_t* list, int number);

    ListInfo_t ListAdd (List_t* list, const char* string, int number);

    ListInfo_t ListDelete (List_t* list, int number);

    int FastListFindNode (List_t* list, int list_size, const char* string, int str_len);

    int SlowListFindNode (List_t* list, int list_size, const char* string, int str_len);

    extern "C" { int MyStrcmp( const char* , int, const char* , int) __attribute__((nonnull(1, 3))); }

#endif
