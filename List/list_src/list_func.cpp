#include "../list_obj/list_func.h"
#include "../list_obj/list_info.h"
#include "../list_obj/list_dot.h"

List_t* CreateNode( ListData_t data )
{
    List_t* new_node = (List_t* )malloc( sizeof( List_t ) );

    new_node->data = data;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    return new_node;
}


List_t* ListCtor()
{
    List_t* phantom = CreateNode( LIST_POISON );

    phantom->next = phantom;
    phantom->prev = phantom;

    return phantom;
}


ListInfo_t ListDtor( List_t* list ) 
{
    List_t* curr_node = list;
    List_t* next_node = curr_node->next;

    while( curr_node->next != list )
    {
        free( curr_node );
        curr_node = next_node;
        next_node = next_node->next;
    }

    return GOOD;
}
 

List_t* GetNode( List_t* list, int number )
{
    List_t* curr_node = list;

    for( int i = 0; i < number + 1; i++ ) //TODO: по-хорошему сюда проверку на то, что номер элемента не больше, чем последний + 1
    {
        curr_node = curr_node->next; 
    }

    return curr_node;
}


ListInfo_t AddNode( List_t* list, ListData_t data, int number )
{
    List_t* new_node = CreateNode( data );

    List_t* tmp_node = GetNode( list, number );

    new_node->prev = tmp_node->prev;
    tmp_node->prev->next = new_node;

    tmp_node->prev = new_node;
    new_node->next = tmp_node;
    
    return GOOD;
}       


ListInfo_t DeleteNode( List_t* list, int number )
{
    List_t* tmp_node = GetNode( list, number );

    tmp_node->prev->next = tmp_node->next;
    tmp_node->next->prev = tmp_node->prev;

    free( tmp_node );

    return GOOD;
}


ListInfo_t TextListDump( List_t* list )
{
    List_t* curr_node = list;

    printf("||================\n");
    printf("||   %lX --- phantom\n\n", (uint64_t )curr_node->data );
    curr_node = curr_node->next;
    while( curr_node->next != list ) 
    {
        printf("||   %.2lf   \n"
               "||    ||     \n"
               "||    \\/     \n", curr_node->data );

        curr_node = curr_node->next;
    }
    printf("||   %.2lf   \n", curr_node->data );
    printf("||================\n\n");

    return GOOD;
}

