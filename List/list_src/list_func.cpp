#include "../list_headers/list_func.h"
#include "../list_headers/list_info.h"
#include "../list_headers/list_dot.h"

List_t* CreateNode (const char* string)
{
    int str_len = strlen(string); 
    List_t* new_node = (List_t* )malloc( sizeof(List_t) + str_len + 1);
    new_node->str_len = str_len;

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->next = nullptr;
    new_node->prev = nullptr;
    strncpy( ( GET_NODE_DATA(new_node) ), string, str_len + 1);

    return new_node;
}


List_t* ListCtor ()
{
    List_t* phantom = CreateNode (LIST_POISON);

    phantom->next = phantom;
    phantom->prev = phantom;

    return phantom;
}


ListInfo_t ListDtor (List_t* list) 
{
    List_t* curr_node = list;
    List_t* next_node = curr_node->next;

    while (curr_node->next != list)
    {
        free (curr_node);
        curr_node = next_node;
        next_node = next_node->next;
    }

    free (curr_node);

    return kGoodList;
}
 

List_t* GetNode (List_t* list, int number)
{
    List_t* curr_node = list;

    for (int i = 0; i < number; i++)
    {
        curr_node = curr_node->next; 
    }

    return curr_node;
}


/*
* 1st arg -- list, where to add
*
* 2nd arg -- string to add 
*
* 3rd arg -- position in the list (if you want to add in the end, 3rd arg = size of list)
*/
ListInfo_t ListAdd (List_t* list, const char* string, int number)
{
    List_t* new_node = CreateNode (string);

    List_t* tmp_node = GetNode (list, number);

    new_node->prev = tmp_node;
    new_node->next = tmp_node->next;
    
    tmp_node->next->prev = new_node;
    tmp_node->next = new_node;

    return kGoodList;
}       


ListInfo_t ListDelete (List_t* list, int number)
{
    List_t* tmp_node = GetNode( list, number );

    tmp_node->prev->next = tmp_node->next;
    tmp_node->next->prev = tmp_node->prev;

    free( tmp_node );

    return kGoodList;
}


ListInfo_t TextListDump (List_t* list)
{
    List_t* curr_node = list;

    printf("||================\n");
    printf("||   \"%s\" --- phantom\n\n", GET_NODE_DATA(curr_node) );
    curr_node = curr_node->next;
    while( curr_node->next != list ) 
    {
        printf("||   \"%s\"   \n"
               "||    ||     \n"
               "||    \\/     \n", GET_NODE_DATA(curr_node) );

        curr_node = curr_node->next;
    }
    printf("||   \"%s\"   \n", GET_NODE_DATA(curr_node) );
    printf("||================\n\n");

    return kGoodList;
}

/*
* 1st arg -- list, where to find
* 
* 2nd arg -- string to search 
*
* 3rd arg -- pointer to return value of function = number of found element in list 
*
* return -- number of elem node, if found; (< 0), if not found
*/
int FindNode (List_t* list, const char* string)
{
    List_t* tmp_node = list;
    List_t* next_node = list;
    int iter = 0;

    while (1)
    {   
        next_node = tmp_node->next;
        if (next_node != nullptr)
        {   
            tmp_node = next_node;
            iter++;
        }
        else
        {
            return -1;
        }

        if( !strcmp( GET_NODE_DATA(tmp_node), string) )
        {
            return iter;
        }

    }

    return -1;
}
