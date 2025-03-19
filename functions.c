#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/******************************************************
* WRAPPER FUNCTION TO COMPARE STRINGS USING QSORT AND BSEARCH
******************************************************/

int compare_strings(const void *a, const void *b) {
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcasecmp(*str_a, *str_b);
}

/******************************************************
* THIS FUNTION CHECKS IF A DICTIONARY FILE HAS BEEN GIVEN
* IN THE COMMAND LINE ARGUMENTS AND STORES IT INTO MEMORY,
* THEN SORTS IT ALPHABETICALLY. IF NO DICTIONARY FILE WAS
* PROVIDED USE THE "words" DICITIONARY ****************
******************************************************/

char** handle_dic(int flag, char* dic, int* dict_count) {
    if ((flag == 3) && (dic == NULL)) 
        exit(EXIT_FAILURE);

    if(dic == NULL)
        dic = "words";

    FILE *fp = fopen(dic, "r");

    if(fp == NULL)
        exit(EXIT_FAILURE);

    char line_buffer[MAX_LEN + 1];
    int count = 0;
    
    for (char c = getc(fp); c != EOF; c = getc(fp)) { //Number of lines in file and longest word
        if (c == '\n' || c == '\t' || c == '/')
            count++;
    }

    char** dictionary = (char**) malloc(sizeof(char*) * count);

    if(dictionary == NULL)
        exit(EXIT_FAILURE);

    for(int i = 0; i < count; i++) {
        dictionary[i] = (char*) malloc(sizeof(char) * (MAX_LEN + 1)); 

        if(dictionary == NULL)
            exit(EXIT_FAILURE);
    }

    rewind(fp);

    int i = 0;

    while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL) { 
        remove_newline(line_buffer); 
        strcpy(dictionary[i], line_buffer);
        i++;
    }

    qsort(dictionary, count, sizeof(*dictionary), compare_strings);

    fclose(fp);

    *dict_count = count;
    return dictionary;
}

/******************************************************
* THIS BLOCK OF CODE FORMATS THE INPUT SO IT IS EASIER
* TO SEARCH FOR THE WORDS IN THE DICTIONARY ***********
******************************************************/

int is_allowed_char(char c) {
    char* allowed_chars = "àáéíóúãõâêôçÀÁÉÍÓÚÃÕÂÊÔÇ";
    if (isalpha(c) || strchr(allowed_chars, c) != NULL) {
        return 1;
    }
    return 0;
}

void format_input(char* str) {
    int len = strlen(str);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isdigit(str[i]) || ispunct(str[i]) || !is_allowed_char(str[i])) {
            str[j++] = ' ';
        } else {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void remove_newline(char* str) {
    str[strcspn(str, "\n")] = '\0';
}

/******************************************************
*******************************************************
******************************************************/

/******************************************************
* THIS FUNCTION TAKES INPUT FROM STDIN AND STORES IT INTO
* MEMORY, ASWELL AS A COPY, AND FORMATS ONE OF THE INPUTS
* TO EVALUATE WRONG WORDS *****************************
******************************************************/

char** handle_terminal_input(int *count, char** formated_input) {

    char line_buffer[MAX_LINE_LEN];
    char** input = (char**) malloc(sizeof(char*)*MAX_LINES);

    if(input == NULL)  
        exit(EXIT_FAILURE);

    int i = 0;
    
    for (int i = 0; i<MAX_LINES; i++) {
        input[i] = (char*) malloc(sizeof(char)*MAX_LINE_LEN);
        if(input == NULL)
            exit(EXIT_FAILURE);
    }

    while(fgets(line_buffer, MAX_LINE_LEN , stdin) != NULL)
    {
        remove_newline(line_buffer);
        strcpy(input[i],line_buffer);
        format_input(line_buffer);
        strcpy(formated_input[i], line_buffer);
        i++;
        (*count)++; //PARENTHISIS INCREMENT THE VARIABLE INSTEAD OF THE POINTER
    }

    return input;
}

/******************************************************
* THIS FUNTION SPLITS A LINE OF INPUT INTO SEPARATE WORDS
* AND THEN FORMATS IT USING format_input() ************
******************************************************/

char** split_line_into_words(char* line, int* word_count) {
    char** words = (char**) malloc(MAX_WORDS * sizeof(char*));

    if(words == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < MAX_WORDS; i++) {
        words[i] = (char*) malloc(MAX_LEN * sizeof(char));
        if(words == NULL)
            exit(EXIT_FAILURE);
    }

    char* line_copy = (char*) malloc(strlen(line) + 1);

    if(line_copy == NULL)
        exit(EXIT_FAILURE);

    strcpy(line_copy, line);

    *word_count = 0;
    char* token = strtok(line_copy, " ");
    while (token != NULL) {
        format_input(token);
        strcpy(words[*word_count], token);
        (*word_count)++;
        token = strtok(NULL, " ");
    }

    free(line_copy);

    return words;
}

/******************************************************
* THIS FUNTION SIMPLY PRINTS THE LINE WHERE THERE ARE WRONG
* WORDS AND THE, IN ORDER, THE WRONG WORDS ARE PRINTED
* TO STDOUT *******************************************
******************************************************/

int handle_terminal_output(char* input_line, int line, char** wrong_words, int ww_count) {

    printf("%d: %s\n", line+1, input_line);

    for (int j = 0; j < ww_count; j++) {
        printf("Erro na palavra \"%s\"\n", wrong_words[j]);
    }

    return 0;
}

/******************************************************
* THIS FUNTION SEARCHES THE DICTIONARY FOR WORDS IN THE
* WORDS ARRAY, GIVEN BY THE FUNCTION split_line_into_words()
* AND IF THEY ARE NOT FOUND ARE STORED IN THE wrong_words ARRAY
******************************************************/

int handle_wrong_words(char** input, char** formated_input, int line_count, char** dictionary, int dic_count) {

    for (int i = 0; i < line_count; i++) {
        int word_count = 0;
        char** words = split_line_into_words(formated_input[i], &word_count);

        char** wrong_words = (char**) malloc(MAX_WORDS * sizeof(char*));

        if(wrong_words == NULL)
            exit(EXIT_FAILURE);

        int wrong_word_count = 0;

        for (int j = 0; j < word_count; j++) {
            if (bsearch(&words[j], dictionary, dic_count, sizeof(char*), compare_strings) == NULL) {
                wrong_words[wrong_word_count] = (char*) malloc((strlen(words[j]) + 1) * sizeof(char));

                if(wrong_words == NULL)
                    exit(EXIT_FAILURE);

                strcpy(wrong_words[wrong_word_count], words[j]);
                wrong_word_count++;
            }
        }

        if(wrong_word_count != 0)
            handle_terminal_output(input[i], i, wrong_words, wrong_word_count);

        for (int j = 0; j < MAX_WORDS; j++) {
            free(words[j]);
        }
        free(words);

        for (int j = 0; j < wrong_word_count; j++) {
            free(wrong_words[j]);
        }
        free(wrong_words);
    }

    return 0;

}
