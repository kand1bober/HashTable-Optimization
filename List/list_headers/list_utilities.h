#include <stdlib.h>

#ifndef UTILITIES_LIST_HEADER
#define UTILITIES_LIST_HEADER

const double EPSILON = 0.00001; 

char* GetFilePath( char* filepath, const char* filename );
int CheckSize_t( size_t number );
void BufferResize( struct Writing_buffer* buffer );
void MakeOffset( struct File_text* file, int count );

#endif