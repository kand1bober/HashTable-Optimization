#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "list_info.h"

#ifndef LIST_FUNC_HEADER
#define LIST_FUNC_HEADER

    typedef struct List
    {
        struct List* next; 
        struct List* prev;
        int str_len; // without '\0'
    } List_t;

    #define GET_NODE_DATA(node_ptr) (char*)node_ptr + sizeof(List_t) // makes offset from struct beginning

    List_t* CreateNode (const char* string);

    List_t* ListCtor();

    ListInfo_t ListDtor (List_t* list);

    List_t* GetNode (List_t* list, int number);

    ListInfo_t ListAdd (List_t* list, const char* string, int number);

    ListInfo_t ListDelete (List_t* list, int number);

    ListInfo_t TextListDump (List_t* list);

    ListInfo FindNode (List_t* list, const char* string, int* number);

#endif
