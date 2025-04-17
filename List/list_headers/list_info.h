#include <stdint.h>
#include <sys/types.h>

#ifndef LIST_INFO_HEADER
#define LIST_INFO_HEADER

    const char LIST_POISON[] = "BADBABA";

    typedef enum ListInfo
    {
        kGoodList = 52,
        kBadList = 53,
    }ListInfo_t;

#endif
