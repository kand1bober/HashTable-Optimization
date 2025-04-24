#include "list_func.h"

List_t* ListCreateNode (const char* string)
{
    int str_len = strlen(string);                       // word + '\0'
    List_t* new_node = (List_t* )calloc( sizeof(List_t) + str_len + 1, 1);

    if (!new_node)
    {   
        printf("Failed to allocate new node\n");
        exit(1);
    }

    new_node->str_len = str_len; //length without '\0'
    new_node->word_reps = 0;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    strncpy(GET_NODE_DATA(new_node), string, str_len + 1);

    return new_node;
}


List_t* ListCtor ()
{
    List_t* phantom = ListCreateNode (LIST_POISON);

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
 

List_t* ListGetNode (List_t* list, int number)
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
    List_t* new_node = ListCreateNode (string);

    List_t* tmp_node = ListGetNode (list, number);

    new_node->prev = tmp_node;
    new_node->next = tmp_node->next;
    
    tmp_node->next->prev = new_node;
    tmp_node->next = new_node;

    return kGoodList;
}       


ListInfo_t ListDelete (List_t* list, int number)
{
    List_t* tmp_node = ListGetNode(list, number);

    tmp_node->prev->next = tmp_node->next;
    tmp_node->next->prev = tmp_node->prev;

    free(tmp_node);

    return kGoodList;
}


/*
* 1st arg -- list, where to find
* 
* 2nd arg -- string to search 
*
* return -- number of elem node, if found; (< 0), if not found
*/
// int FastListFindNode (List_t* list, int list_size, const char* string, int str_len)
// {
//     List_t* tmp_node = list->next;
//     List_t* next_node = nullptr;
//     int iter = 0;

//     for (int i = 0; i < list_size; i++)
//     {   
//         next_node = tmp_node->next;

//         if ( (str_len == tmp_node->str_len) && 
//              (!MyStrcmp(GET_NODE_DATA(tmp_node), tmp_node->str_len, string, str_len)) )
//         {
//             return iter;
//         }
//         else  
//         {
//             tmp_node = next_node;
//             iter++;
//         }
//     }

//     return -1;
// }

int FastListFindNode (List_t* list, int list_size, const char* string, int str_len)
{
    List_t* tmp_node = list->next;
    List_t* next_node = nullptr;
    int iter = 0;

    while (1)
    {   
        next_node = tmp_node->next;

        if (next_node)
        {
            if (tmp_node != list)
            {
                if ( (str_len == tmp_node->str_len) && 
                     (!MyStrcmp(GET_NODE_DATA(tmp_node), tmp_node->str_len, string, str_len)) )
                {
                    return iter;
                }
                else  
                {
                    tmp_node = next_node;
                    iter++;
                }
            }
            else  
            {
                return -1;
            }
        }
        else  
        {
            printf("Bad list allocation");
            exit(1);
        }
    }


    return -1;
}


/*
* 1st arg -- list, where to find
* 
* 2nd arg -- string to search 
*
* return -- number of elem node, if found; (< 0), if not found
*/
// int SlowListFindNode (List_t* list, int list_size, const char* string, int str_len)
// {
//     List_t* tmp_node = list->next;
//     List_t* next_node = nullptr;
//     int iter = 0;

//     for (int i = 0; i < list_size; i++)
//     {    
//         next_node = tmp_node->next;

//         if ( (str_len == tmp_node->str_len) && 
//              (!strncmp( GET_NODE_DATA(tmp_node), string, str_len)) )
//         {
//             return iter;
//         }
//         else  
//         {
//             tmp_node = next_node;
//             iter++;
//         }
//     }

//     return -1;
// }


int SlowListFindNode (List_t* list, int list_size, const char* string, int str_len)
{
    List_t* tmp_node = list->next;
    List_t* next_node = nullptr;
    int iter = 0;

    next_node = tmp_node->next;

    while (1)
    {   
        next_node = tmp_node->next;

        if (next_node)
        {
            if (tmp_node != list)
            {
                if ( (str_len == tmp_node->str_len) && 
                    (!strncmp( GET_NODE_DATA(tmp_node), string, str_len)) )
                {
                    return iter;
                }
                else  
                {
                    tmp_node = next_node;
                    iter++;
                }
            }
            else  
            {
                return -1;
            }
        }
        else  
        {
            printf("Bad list allocation");
            exit(1);
        }
    }

    return -1;
}


