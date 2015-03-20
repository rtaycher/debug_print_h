#include "debug_print.h"

int main()
{
    int i    = 5;
    char * s = "yo";
    debug_print_options o = (struct debug_print_options){.colorscheme=FORE_BLUE};

    DEBUG_PRINT(i);
    DEBUG_PRINT(0+22);
    DEBUG_PRINT(s);
    DEBUG_PRINT(o, .colorscheme=FORE_GREEN);
    return 0;
}

