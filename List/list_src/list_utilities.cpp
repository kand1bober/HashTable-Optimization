#include "../list_obj/list_dot.h"

int CheckSize_t( size_t number )
{
    if( number < 1000000 )
        return 1;
    else
        return -1;
}


char* GetFilePath( char* filepath, const char* filename )
{
    sprintf(filepath, "%s%s", project_directory, filename);

    return filepath;
}

void MakeOffset( struct File_text* file, int count )
{
    for(int i = 0; i < count; i++)
    {
        fprintf(file->stream, "\t");
    }
}
