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


#define DEBUG_PRINT_INTERNAL_STRING_BUFFER_SIZE 50
#define DEBUG_PRINT_NUMBER_OF_GROUPS 50
typedef struct debug_print_group_options {
	char colorscheme[DEBUG_PRINT_INTERNAL_STRING_BUFFER_SIZE];
	FILE * filestream;
	_Bool disabled;
} debug_print_group_options;

typedef struct debug_print_options {
	char colorscheme[DEBUG_PRINT_INTERNAL_STRING_BUFFER_SIZE];
	FILE * filestream;
	int group;
	_Bool _private_is_group_disabled;
} debug_print_options;

//Initialize default group
//Can't initialize filestream to stderr so just leave it null and treat null as equivalent of stderr
debug_print_group_options debug_print_group_options_list[DEBUG_PRINT_NUMBER_OF_GROUPS] = {
		{.colorscheme = FORE_BLUE, .disabled=0}};

debug_print_options * debug_print_options_apply_group_options(debug_print_options * options)
{
	int group = options->group;
	if (!options->colorscheme[0])
	{
		strncpy(options->colorscheme, debug_print_group_options_list[group].colorscheme, DEBUG_PRINT_INTERNAL_STRING_BUFFER_SIZE-1);
	}

	if (!options->filestream)
	{		if (!debug_print_group_options_list[group].filestream)
		{
			options->filestream = stderr;
		}
		else
		{
			options->filestream = debug_print_group_options_list[group].filestream;
		}
	}
	options->_private_is_group_disabled = debug_print_group_options_list[group].disabled;
	return options;
}

typedef struct dsc_func_ptr {
	char * (*debug_string_create_function)(void * data);
} dsc_func_ptr;

#define UNUSED(x) (void)(x)

char * print_not_valid_type_for_debug_print(void * blank)
{
	UNUSED(blank);
	fprintf(stderr, "This is not a valid type to DEBUG_PRINT, please add your type/"
			" library type to_string function wrapper to the"
			" GET_CREATE_DEBUG_STRING_FUNC _Generic Selection in the"
			"debug_print.h header. Exiting program with non-zero exit code.\n");
	exit(1);
}

char * debug_print_group_options_to_debug_string(void * options_v) {
	debug_print_group_options * options = ((debug_print_group_options *)options_v);
	char * buffer = malloc(200);
	char mini_buffer[50] = {0};
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

	strcat(buffer, "\n    filestream: ");
	if (options->filestream == stdout)
	{
		strcat(buffer, "stdout");
	}
	else if (options->filestream == stderr)
	{
		strcat(buffer, "stderr");
	}
	else
	{
		snprintf(mini_buffer, 50, "ptr to filestream:%p", options->filestream);
		strcat(buffer, mini_buffer);
	}

	if (options->disabled)
	{
		strcat(buffer, "\ndisabled\n");
	}
	else
	{
		strcat(buffer, "\nenabled\n");
	}

	return buffer;
}
char * debug_print_options_to_debug_string(void * options_v) {
	debug_print_options * options = ((debug_print_options *)options_v);
	char * buffer = malloc(200);
	char mini_buffer[50] = {0};
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

	strcat(buffer, "\n    filestream: ");
	if (options->filestream == stdout)
	{
		strcat(buffer, "stdout");
	}
	else if (options->filestream == stderr)
	{
		strcat(buffer, "stderr");
	}
	else
	{

		snprintf(mini_buffer, 50, "ptr to filestream:%p", options->filestream);
		strcat(buffer, mini_buffer);
	}
	snprintf(mini_buffer, 50, "\ngroup index:%i\n", options->group);
	strcat(buffer, mini_buffer);
	return buffer;
}

#define TYPE_PTR_TO_PRINTF_SPECIFIER(x) _Generic((*x), \
		const char *: "s",                       \
		char *: "s",                             \
		int: "d", \
		float: "f" ,\
		double: "f" ,\
		char: "c",\
int16_t: PRIi16, \
uint16_t: PRIu16, \
uint32_t: PRIu32,                                \
int64_t: PRIi64, 	\
uint64_t: PRIu64,                                \
default: "")


#define GET_CREATE_DEBUG_STRING_FUNC(x) _Generic((x), \
		debug_print_options *: debug_print_options_to_debug_string, \
		debug_print_group_options *: debug_print_group_options_to_debug_string, \
		default: print_not_valid_type_for_debug_print)

//Coerce string literal to char* and avoid segfault with (0,x) trick
//HT:http://stackoverflow.com/questions/18857056/c11-generic-how-to-deal-with-string-literals
#define DEBUG_PRINT(x,...) \
	do \
	{\
		_Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wunused-value\"") \
		__typeof__((0,x)) _x = x; \
		_Pragma("GCC diagnostic pop") \
		DEBUG_PRINT_PTR((#x), &_x, __VA_ARGS__);\
	} while(0)

//The repetition of debug_print_printf_specifier is to avoid repetition for custom types.
#define DEBUG_PRINT_PTR(xstr, xp,...) \
		_Generic((*xp),                    \
				const char *:  debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				char *:        debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				int:           debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				float:         debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				double:        debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				char:          debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				int16_t:       debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				uint16_t:      debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				uint32_t:      debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				int64_t:       debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				uint64_t:      debug_print_printf_specifier(xstr, (void *)xp, TYPE_PTR_TO_PRINTF_SPECIFIER(xp), __FILE__, __LINE__, _my_func__, debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__}))),\
				default: DEBUG_PRINT_CUSTOM_TYPE(xstr, xp,  __VA_ARGS__))

#define DEBUG_PRINT_CUSTOM_TYPE(xstr, xp,...) \
		debug_print_custom_to_debug_string(xstr, xp, &((dsc_func_ptr){GET_CREATE_DEBUG_STRING_FUNC(xp)}), __FILE__, __LINE__, _my_func__,\
				debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__})))

#define DEBUG_PRINT_MESSAGE(message_str_literal, ...) \
		debug_print_message(message_str_literal, __FILE__, __LINE__, _my_func__,\
				debug_print_options_apply_group_options(&((debug_print_options){__VA_ARGS__})))


void debug_print_message(const char *message,
		const char * file, int line,
		const char * func_name, debug_print_options * options) {
	if(options->_private_is_group_disabled)
	{
		return;
	}

	if (!options->colorscheme[0]) {
		strcpy(options->colorscheme, FORE_BLUE);
	}

	char format_string[100];
	snprintf(format_string, 100,
		STYLE_BRIGHT "%sFile: %%s " STYLE_RESET_ALL "| %sLine: %%d " STYLE_RESET_ALL "| " STYLE_BRIGHT "%sFunc: %%s\n" STYLE_RESET_ALL
		STYLE_BRIGHT" %s%%s\n" STYLE_RESET_ALL, options->colorscheme, options->colorscheme, options->colorscheme,
		options->colorscheme);
	fprintf(options->filestream, format_string, file, line, func_name,
			message);

}

void debug_print_custom_to_debug_string(const char *expr, void * data,
		void * ptr_to_struct_func, const char * file,
		int line, const char * func_name, debug_print_options * options) {

	if(options->_private_is_group_disabled)
	{
		return;

	}
	if (!options->colorscheme[0]) {
		strcpy(options->colorscheme, FORE_BLUE);
	}
	char format_string[100];
	snprintf(format_string, 100,
		STYLE_BRIGHT "%sFile: %%s " STYLE_RESET_ALL "| %sLine: %%d " STYLE_RESET_ALL "| " STYLE_BRIGHT "%sFunc: %%s\n" STYLE_RESET_ALL
		"%s%%s -> " STYLE_RESET_ALL  STYLE_BRIGHT" %s%%s\n" STYLE_RESET_ALL,
		options->colorscheme, options->colorscheme, options->colorscheme, options->colorscheme,  options->colorscheme);

	char * (*debug_string_create_function)(void * data) = ((dsc_func_ptr *)ptr_to_struct_func)->debug_string_create_function;
	char * temp_data_str = (*debug_string_create_function)(data);

	fprintf(options->filestream, format_string, file, line, func_name,
			expr, temp_data_str);

	free(temp_data_str);
}

void debug_print_printf_specifier(const char *expr, void * data,
		void * printf_specifier_v, const char * file, int line,
		const char * func_name, debug_print_options * options) {
	if(options->_private_is_group_disabled)
	{
		return;
	}
	char * printf_specifier = (char *) printf_specifier_v;
	if (!options->colorscheme[0]) {
		strcpy(options->colorscheme, FORE_BLUE);
	}
	if(printf_specifier[0]=='\0')
	{
		printf("Empty printf_specifier. Should never be reached. Exiting program with non-zero exit code.");
		exit(1);
	}
	char format_string[100];
	snprintf(format_string, 100,
		STYLE_BRIGHT "%sFile: %%s " STYLE_RESET_ALL "| %sLine: %%d " STYLE_RESET_ALL "| " STYLE_BRIGHT "%sFunc: %%s\n" STYLE_RESET_ALL
		"%s%%s -> " STYLE_RESET_ALL  STYLE_BRIGHT" %s%%%s\n" STYLE_RESET_ALL,
		options->colorscheme, options->colorscheme, options->colorscheme, options->colorscheme, options->colorscheme, printf_specifier);
	fprintf(options->filestream, format_string, file, line, func_name,
			expr, *(char **)data);
}

#endif /* DEBUG_PRINT_DEFINITIONS */
