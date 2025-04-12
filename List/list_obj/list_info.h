#include <stdint.h>
#include <sys/types.h>

#ifndef LIST_INFO_HEADER
#define LIST_INFO_HEADER

    const uint LIST_POISON = 0xBADBABA;

    typedef enum ListInfo
    {
        GOOD = 52,
        BAD = 53,

    }ListInfo_t;

#endif
