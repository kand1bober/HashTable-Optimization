#ifndef HASH_TABLE_CONFIG
#define HASH_TABLE_CONFIG

    #ifdef TESTS
        #define ON_TESTS(expr) expr

        #define NO_TESTS(expr) 
    #else
        #define ON_TESTS(expr) 

        #define NO_TESTS(expr) expr
    #endif
    
#endif 
