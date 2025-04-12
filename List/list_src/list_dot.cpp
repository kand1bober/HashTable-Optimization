#include "../list_obj/list_dot.h"

ListInfo_t ListDot( List_t* list )
{
    File_text file = {};

    BeginDotOutput( &file );

    DotDriver( list, &file );

    EndDotOutput( &file );

    return GOOD;
}


ListInfo_t BeginDotOutput( File_text* file )
{
    char code_filepath[200] = {};
    GetFilePath( code_filepath, output_graph_name );
    char html_filepath[200] = {};
    GetFilePath( html_filepath, output_html_name );
    char image_filepath[200] = {};
    GetFilePath( image_filepath, output_image_name );

    //=== HTML FIlE ===
    FILE* html_stream = fopen( html_filepath, "w" );
    fprintf(html_stream, "<img src=\"%s\"  alt=\"MyGraph\" >", image_filepath);  //width=\"1300px\" height=\"900px\"
    fclose( html_stream );
    //=================

    //=== GRAPH FILE ===
    file->stream = fopen(code_filepath, "w");
    //==================

    //=== Write node settings ===
    fprintf(file->stream, "digraph G\n{\nlabel=\"%s\";\n labelloc=\"t\";\n fontsize=30\n fontname=\"%s\";\n fontcolor=\"%s\"\n"
    "\nrankdir=LR; splines=ortho; size=\"200,300\"; bgcolor=\"%s\";\n", graph_header, fontname, fontcolor, bgcolor);
    //===========================

    return GOOD;
}


ListInfo_t EndDotOutput( File_text* file )
{
    fprintf(file->stream, "\n}\n");
    char cmd[256] = {};
    snprintf(cmd, sizeof(cmd), "dot -Tsvg %s%s > %s%s", project_directory, output_graph_name, project_directory, output_image_name);

    fclose(file->stream);

    system( cmd );

    return GOOD;
}


ListInfo_t DotDriver( List_t* list, File_text* file )
{   
    DotCollector( list, file );

    return GOOD;
}

ListInfo_t DotCollector( List_t* list, File_text* file )
{
    //=== Description ===
    fprintf( file->stream, "{ node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%s\", color=\"%s\", label=\" { Phantom } | { data: %lX } | { <curr%p> curr: %p } | { { <prev%p> prev: %p } | { <next%p> next: %p } }  \"] \n}\n",
                            list, first_fillcolor, default_pointer_color, ( uint64_t )list->data, list, list, list, list->prev, list, list->next );
    //===================

    List_t* curr_node = list->next;
    int nodes_count = 0;
    while( 1 )
    {
        //=== Description ===
        fprintf( file->stream, "node_%p [shape = record; style=\"rounded, filled\", fillcolor=\"%s\", color=\"%s\", label=\" { <num%d> num: %d } | { <data%.2lf> data: %.2lf } | { <curr%p> curr: %p } | { { <prev%p> prev: %p } | { <next%p> next: %p } }  \"] \n", 
                 curr_node, third_fillcolor, default_pointer_color, nodes_count, nodes_count, curr_node->data, curr_node->data, curr_node, curr_node, curr_node, curr_node->prev, curr_node, curr_node->next );
        //===================

        curr_node = curr_node->next;
        if( curr_node == list ) 
        {
            break;
        }

        nodes_count++;
    }
    fprintf( file->stream, "\n" );


    List_t* left_node = list;
    List_t* right_node = left_node->next;
    while( 1 )
    {
        //=== Arrows ===
        fprintf( file->stream, "node_%p -> node_%p [color =\"%s\"];\n", left_node, left_node->next, first_fillcolor );
        fprintf( file->stream, "node_%p -> node_%p [color =\"%s\"];\n", left_node, left_node->prev, second_fillcolor );
        //==============

        if( right_node == list )
        {
            break;
        }

        left_node = right_node;
        right_node = right_node->next;
    }

    return GOOD;
}

