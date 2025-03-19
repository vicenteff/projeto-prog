#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50
#define MAX_LINES 500
#define MAX_LINE_LEN 100
#define MAX_WORDS 100

int handle_terminal_output(char* input, int line, char** wrong_words, int ww_count);
int is_allowed_char(char c);
void format_input(char* str);
void remove_newline(char* str);
int compare_strings(const void *a, const void *b);
char** handle_terminal_input(int *count, char** formated_input);
char** split_line_into_words(char* line, int* word_count);
int handle_wrong_words(char** input, char** formated_input, int line_count, char** dictionary, int dic_count);
int handle_terminal_output(char* input_line, int line, char** wrong_words, int ww_count);
char** handle_dic(int flag, char* dic, int* dict_count);