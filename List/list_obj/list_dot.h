#include "list_func.h"
#include"list_info.h"
#include "list_decoration.h"
#include "list_utilities.h"

#ifndef LIST_DOT_HEADER
#define LIST_DOT_HEADER

const char project_directory[100] = "/home/vyacheslav/StandartList/list_dump/";

const char output_image_name[40] = "TreeGraph.svg";
const char output_graph_name[40] = "TreeGraph.dot";
const char output_html_name[40] =  "TreeGraph.html";

const size_t START_OUTPUT_FILE_SIZE =  10;
const char default_pointer_color[20] = "#FFE9C7";
const char pointer_left_color[20] =    "#9ACD32"; 
const char pointer_right_color[20] =   "#FF2B00";

const char first_fillcolor[20] = "#ff6699"; //#FFA9B8
const char second_fillcolor[20] = "#34cb34";
const char third_fillcolor[20] = "#9966FF";

const char bgcolor[20] =   "#ffd480";
const char fontcolor[20] = "#FFFFFF";

const char fontname[30] =     "Verdana";
const char graph_header[30] = "List";


typedef struct File_text
{
    FILE* stream;
    size_t stream_size;
    char* buffer;
}File_text;

//-------------------------------------------------------------------
ListInfo_t ListDot( List_t* list );

ListInfo_t BeginDotOutput( File_text* file );

ListInfo_t EndDotOutput( File_text* file );

ListInfo_t DotDriver( List_t* list, File_text* file );

ListInfo_t DotCollector( List_t* list, File_text* file );
//-------------------------------------------------------------------

#endif