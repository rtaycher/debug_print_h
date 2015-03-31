#include "debug_print.h"
#include "stdio.h"
#include "stdbool.h"

char * static_string_with_side_effect_only_once()
{
	puts("side effect");
	return "yoho";
}

#define RED_GROUP 1
#define EXTRA_INFO_GROUP 2
int main()
{
    int i    = 5;
    char * s = "yo";

    FILE * a = fopen("/tmp/a", "w");
    debug_print_options o = (struct debug_print_options){.colorscheme=FORE_BLUE};
    strncpy(debug_print_group_options_list[RED_GROUP].colorscheme, FORE_RED, DEBUG_PRINT_INTERNAL_STRING_BUFFER_SIZE-1);
    debug_print_group_options_list[EXTRA_INFO_GROUP].disabled = true;

    DEBUG_PRINT(7, .group=1);
    DEBUG_PRINT(i);
    DEBUG_PRINT('A');
    DEBUG_PRINT(s);
    DEBUG_PRINT("yo");
    DEBUG_PRINT_MESSAGE("yo message");
    DEBUG_PRINT(0+22);
    DEBUG_PRINT(s, .group=EXTRA_INFO_GROUP);
    DEBUG_PRINT(o, .colorscheme=FORE_GREEN, .group=RED_GROUP);
    DEBUG_PRINT(debug_print_group_options_list[RED_GROUP], .group=RED_GROUP);
    DEBUG_PRINT(static_string_with_side_effect_only_once());
    fclose(a);
    return 0;
}
