#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "list_info.h"

#ifndef LIST_FUNC_HEADER
#define LIST_FUNC_HEADER

    typedef double ListData_t;

    typedef struct List
    {
        ListData_t data;
        struct List* next; 
        struct List* prev;
    } List_t;

    ListInfo_t Run();

    List_t* CreateNode( ListData_t data );

    List_t* ListCtor();

    ListInfo_t ListDtor( List_t* list );

    List_t* GetNode( List_t* list, int number );

    ListInfo_t AddNode( List_t* list, ListData_t data, int number );

    ListInfo_t DeleteNode( List_t* list, int number );

    ListInfo_t TextListDump( List_t* list );

#endif