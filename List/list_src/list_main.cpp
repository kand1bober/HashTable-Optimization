#include "../list_headers/list_func.h"
#include "../list_headers/list_info.h"
#include "../list_headers/list_dot.h"

int main ()
{
    Run();

    return 0;
}

ListInfo_t Run ()
{
    List_t* my_list = nullptr;

    my_list = ListCtor();

    // ListData_t data = 0;
    // int number = 0;

    // data = 11;
    // number = 0;
    // AddNode( my_list, data, number );


    // data = 22;
    // number = 1;
    // AddNode( my_list, data, number );

    // data = 33;
    // number = 2;
    // AddNode( my_list, data, number );

    // TextListDump( my_list );

    // ListDot( my_list );
    // getchar();

    // number = 2;
    // DeleteNode( my_list, number );
    // ListDot( my_list );
    // getchar();

    // number = 1;
    // DeleteNode( my_list, number );
    // ListDot( my_list );
    // getchar();

    // number = 0;
    // DeleteNode( my_list, number );
    // ListDot( my_list );
    // getchar();

    // data = 11;
    // number = 0;
    // AddNode( my_list, data, number );
    // ListDot( my_list );
    // getchar();


    // data = 22;
    // number = 1;
    // AddNode( my_list, data, number );
    // ListDot( my_list );
    // getchar();

    // data = 33;
    // number = 2;
    // AddNode( my_list, data, number );
    // ListDot( my_list );
    // getchar();

    // data = 67;
    // number = 2;
    // AddNode( my_list, data, number );
    // ListDot( my_list );
    // getchar();

    ListDtor( my_list );

    return kGoodList;
}
