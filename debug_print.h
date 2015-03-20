#define _BSD_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#ifdef __GNUC__
#define _my_func__ __PRETTY_FUNCTION__
#else
#define _my_func__ __func__
#endif

#define _strdup strdup

#define _CSI "\x1b["
#define _code_to_chars(code) _CSI #code "m"

#define FORE_BLACK _code_to_chars(30)
#define FORE_RED _code_to_chars(31)
#define FORE_GREEN _code_to_chars(32)
#define FORE_YELLOW _code_to_chars(33)
#define FORE_BLUE _code_to_chars(34)
#define FORE_MAGENTA _code_to_chars(35)
#define FORE_CYAN _code_to_chars(36)
#define FORE_WHITE _code_to_chars(37)
#define FORE_RESET _code_to_chars(39)
#define BACK_BLACK _code_to_chars(40)
#define BACK_RED _code_to_chars(41)
#define BACK_GREEN _code_to_chars(42)
#define BACK_YELLOW _code_to_chars(43)
#define BACK_BLUE _code_to_chars(44)
#define BACK_MAGENTA _code_to_chars(45)
#define BACK_CYAN _code_to_chars(46)
#define BACK_WHITE _code_to_chars(47)
#define BACK_RESET _code_to_chars(49)
#define STYLE_BRIGHT _code_to_chars(1)
#define STYLE_RESET_ALL _code_to_chars(0)

#ifndef DEBUG_PRINT_DEFINITIONS
#define DEBUG_PRINT_DEFINITIONS

typedef struct debug_print_options {
	char colorscheme[10];
} debug_print_options;

typedef struct dsc_func_ptr {
	char * (*debug_string_create_function)(void * data);
} dsc_func_ptr;

#define UNUSED(x) (void)(x)

char * print_not_valid_type_for_debug_print(void * blank)
{
	UNUSED(blank);
	printf("This is not a valid type to DEBUG_PRINT, please add your type/"
			" library type to_string function wrapper to the"
			" GET_CREATE_DEBUG_STRING_FUNC _Generic Selection in the"
			"debug_print.h header.");
	exit(1);
}
char * debug_print_options_to_debug_string(void * options_v) {
	debug_print_options * options = ((debug_print_options *)options_v);
	char * buffer = malloc(100);
	strcpy(buffer, "debug_print_options:\n");
	strcat(buffer, "    colorscheme:");

	if (strcmp(options->colorscheme, FORE_BLACK) == 0)
	{
		strcat(buffer, "FORE_BLACK");
	}
	else if(strcmp(options->colorscheme, FORE_RED) == 0)
	{
		strcat(buffer, "FORE_RED");
	}
	else if(strcmp(options->colorscheme, FORE_YELLOW) == 0)
	{
		strcat(buffer, "FORE_YELLOW");
	}
	else if(strcmp(options->colorscheme, FORE_BLUE) == 0)
	{
		strcat(buffer, "FORE_BLUE");
	}
	else if(strcmp(options->colorscheme, FORE_MAGENTA) == 0)
	{
		strcat(buffer, "FORE_MAGENTA");
	}
	else if(strcmp(options->colorscheme, FORE_CYAN) == 0)
	{
		strcat(buffer, "FORE_CYAN");
	}
	else if(strcmp(options->colorscheme, FORE_WHITE) == 0)
	{
		strcat(buffer, "FORE_WHITE");
	}
	else if(strcmp(options->colorscheme, BACK_BLACK) == 0)
	{
		strcat(buffer, "FORE_BLACK");
	}
	else if(strcmp(options->colorscheme, BACK_RED) == 0)
	{
		strcat(buffer, "BACK_RED");
	}
	else if(strcmp(options->colorscheme, BACK_GREEN) == 0)
	{
		strcat(buffer, "BACK_GREEN");
	}
	else if(strcmp(options->colorscheme, BACK_YELLOW) == 0)
	{
		strcat(buffer, "BACK_YELLOW");
	}
	else if(strcmp(options->colorscheme, BACK_BLUE) == 0)
	{
		strcat(buffer, "BACK_BLUE");
	}
	else if(strcmp(options->colorscheme, BACK_MAGENTA) == 0)
	{
		strcat(buffer, "BACK_MAGENTA");
	}
	else if(strcmp(options->colorscheme, BACK_CYAN) == 0)
	{
		strcat(buffer, "BACK_CYAN");
	}
	else if(strcmp(options->colorscheme, BACK_WHITE) == 0)
	{
		strcat(buffer, "BACK_WHITE");
	}

	return buffer;
}

#define TYPE_TO_PRINTF_SPECIFIER(x) _Generic(*(x), \
		const char *: "s",                       \
		char *: "s",                             \
		float: "f" ,\
		double: "f" ,\
int8_t: PRIi8, 	uint8_t: PRIu8,                                \
int16_t: PRIi16, 	uint16_t: PRIu16,                                \
int32_t: PRIi32, 	uint32_t: PRIu32,                                \
int64_t: PRIi64, 	uint64_t: PRIu64,                                \
default: "")


#define GET_CREATE_DEBUG_STRING_FUNC(x) _Generic((x), \
		debug_print_options *: debug_print_options_to_debug_string, \
		default: print_not_valid_type_for_debug_print)

#define DEBUG_PRINT(x,...) \
	do \
	{\
		__typeof__(x) _x = x;\
		DEBUG_PRINT_PTR((#x), &_x, __VA_ARGS__);\
	} while(0)

#define DEBUG_PRINT_PTR(xstr, xp,...) \
		_Generic((xp),                    \
				debug_print_options *: DEBUG_PRINT_CUSTOM_TYPE(xstr, xp,  __VA_ARGS__),    \
				default: DEBUG_PRINT_BASIC_TYPE(xstr, xp, __VA_ARGS__))

#define DEBUG_PRINT_BASIC_TYPE(xstr, xp,...) \
		debug_print_printf_specifier(xstr, (void *)xp, TYPE_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__,\
			&((struct debug_print_options){__VA_ARGS__}))

#define DEBUG_PRINT_CUSTOM_TYPE(xstr, xp,...) \
		debug_print_custom_to_debug_string(xstr, xp, &((dsc_func_ptr){GET_CREATE_DEBUG_STRING_FUNC(xp)}), __FILE__, __LINE__, _my_func__,\
				&((debug_print_options){__VA_ARGS__}))

void debug_print_custom_to_debug_string(const char *expr, void * data,
		void * ptr_to_struct_func, const char * file,
		int line, const char * func_name, debug_print_options * options) {
	char * (*debug_string_create_function)(void * data) = ((dsc_func_ptr *)ptr_to_struct_func)->debug_string_create_function;
	if (!options->colorscheme[0]) {
		strcpy(options->colorscheme, FORE_BLUE);
	}
	char * temp_data_str = (*debug_string_create_function)(data);
	fprintf(stderr, "%sFile: %s | Line: %d | Func: %s\n"
			"%s: %s%s\n", options->colorscheme, file, line, func_name, expr,
			temp_data_str, STYLE_RESET_ALL);
	free(temp_data_str);
}

void debug_print_printf_specifier(const char *expr, void * data,
		void * printf_specifier_v, const char * file, int line,
		const char * func_name, debug_print_options * options) {
	char * printf_specifier = (char *) printf_specifier_v;
	if (!options->colorscheme[0]) {
		strcpy(options->colorscheme, FORE_BLUE);
	}
	if(printf_specifier[0]=='\0')
	{
		printf("Empty printf_specifier. Should never be reached");
		exit(1);
	}
	char format_string[100];
	snprintf(format_string, 100, "%%sFile: %%s | Line: %%d | Func: %%s\n"
			"%%s: %%%s%%s\n", printf_specifier);
	//printf("format_string:'%s'\n", format_string);
	fprintf(stderr, format_string, options->colorscheme, file, line, func_name,
			expr, *(char **)data, STYLE_RESET_ALL);
}

#endif /* DEBUG_PRINT_DEFINITIONS */
