Some ideas I had for simple debug print macros I had where you don't have to specify the type or fmt string. Just a single header and a single interface. Plus in one of a number of colors. 
When done with debugging just CTRL-F and delete.

To add your own or library types just add a line like

    custom_type *: DEBUG_PRINT_CUSTOM_TYPE(xstr, xp,  __VA_ARGS__),    \
in `DEBUG_PRINT_PTR` Macro

and 
    
    custom_type *: custom_type_to_debug_string, \

in `GET_CREATE_DEBUG_STRING_FUNC` Macro

where `custom_type_to_debug_string` is a function with the following signature:

    char * custom_type_to_debug_string(void * obj_of_custom_type_v)
    
that takes a pointer to the custom type as void * and returns a 
dynamically allocated string with the debug string representing 
the object of the custom type.

This works on gcc>4.9 (due to use of designated initializers) and llvm/clang >3.3
(maybe earlier but I tested it with 3.3).
I think microsofts c compiler may have added designated initializers 
and _Generic but I'm not sure and haven't had the chance to test it yet.
Also U used typeof which is a gcc/llvm only extension
(I'll try to replace it later).
Doesn't seem to work with a c++ compiler, might be cool to get compiling for both languages
at the same time.

I may make non backwards compatible changes
but it probably doesn't matter as this is designed as a single dropin header
(debug_print.h). 
the API is
DEBUG_PRINT(expr, ...) where ... is an optional comma seperated list of options in the format
.option=value, (.option is one of the fields in debug_print_options)
currently the only option/field is a colorscheme string for printing in color.

examples:
    
    DEBUG_PRINT(i); 
    //prints in Blue
    //File: example.c | Line: 9 | Func: main
    //i: 5
    DEBUG_PRINT(0+22);
	 //prints in Blue
	 //File: example.c | Line: 10 | Func: main
	 //0+22: 22
    //prints in Blue
    DEBUG_PRINT(s);
    //File: example.c | Line: 11 | Func: main
    //s: yo
    //prints in Green
    //    debug_print_options o = (struct debug_print_options){.colorscheme=FORE_BLUE};
    DEBUG_PRINT(o, .colorscheme=FORE_GREEN);
    //File: example.c | Line: 12 | Func: main
    //o: debug_print_options:
	 //    colorscheme:FORE_BLUE
    