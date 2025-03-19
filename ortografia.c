#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[])  
{ 
    int opt; 

    int *parameters = (int*) calloc(7, sizeof(int)); //Array to check if all parameters were specified

    if(parameters == NULL)
        exit(EXIT_FAILURE);

    /*
    Paramater IDs:
    0 - Help
    EXIT_FAILIURE - Input
    2 - Dictionary
    3 - Output
    4 - Alternatives
    5 - Differences
    6 - Mode
    */

    char* dic = NULL;
    char* input_file = NULL;
    char** dictionary = NULL;
    int count = 0, dic_count = 0;
    char** input;

    /******************************************************
    * THIS BLOCK OF CODE HANDLES THE COMMAND LINE ARGUMENTS
    ******************************************************/
    while((opt = getopt(argc, argv, "hd:i:o:n:m:a:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'h':  
                printf("Usage: ./ortografia -h -d [file] -i [file] -o [file] -n [integer] -m [integer] -a [integer]\n\t-h: help\n\t-d dictionary, if absent use \"words\"\n\t-i input file, if absent use stdin\n\t-o output file, if absent use stdout\n\t-n maximum number of differences, if absent 2\n\t-m mode, if absent 1\n\t-a number of alternatives, if absent 10\n");
                exit(EXIT_SUCCESS);
                break;  
            case 'i':  
                input_file = (char*) malloc(strlen(optarg));

                if(input_file == NULL)
                    exit(EXIT_FAILURE);

                strcpy(input_file,optarg);
                parameters[1]=1;
                break;
            case 'd':  
                dic = (char*) malloc(strlen(optarg));

                if(dic == NULL)
                    exit(EXIT_FAILURE);

                strcpy(dic,optarg);
                parameters[2]=2; 
                break;  
            case 'o':  
                char* out = (char*) malloc(strlen(optarg));

                if(out == NULL)
                    exit(EXIT_FAILURE);

                strcpy(out,optarg);
                printf("Output: %s\n", out);
                parameters[3]=3;           
                break;  
            case 'a':  
                char* alt = (char*) malloc(strlen(optarg));

                if(alt == NULL)
                    exit(EXIT_FAILURE);

                strcpy(alt,optarg);
                printf("Alternatives: %d\n", atoi(alt));
                parameters[4]=4;
                break;  
            case 'n':  
                char* diff = (char*) malloc(strlen(optarg));

                if(diff == NULL)
                    exit(EXIT_FAILURE);

                strcpy(diff,optarg);
                printf("Differences: %d\n", atoi(diff));
                parameters[5]=5; 
                break;  
            case 'm':
                char* mode = (char*) malloc(strlen(optarg));

                if(mode == NULL)
                    exit(EXIT_FAILURE);

                strcpy(mode,optarg);
                printf("Mode: %d\n", atoi(mode));
                parameters[6]=6;
                break;
            default:
                exit(EXIT_FAILURE);
        }  
    }  
    /******************************************************
    *******************************************************
    ******************************************************/

    dictionary = handle_dic(parameters[2], dic, &dic_count);
     
    char** formated_input = (char **) malloc (sizeof(char*) * MAX_LINES);

    if(formated_input == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i<MAX_LINES; i++) {
        formated_input[i] = (char*) malloc(sizeof(char)*MAX_LINE_LEN);

        if(formated_input == NULL)
            exit(EXIT_FAILURE);
    }

    input = handle_terminal_input(&count, formated_input);
 
    handle_wrong_words(input, formated_input, count, dictionary, dic_count);
    
    /******************************************************
    * THIS BLOCK OF CODE FREES ALLOCATED MEMMORY **********
    ******************************************************/

    free(parameters);

    for (int i = 0; i < dic_count; i++) {
        free(dictionary[i]);
    }
    free(dictionary);

    for (int i = 0; i < MAX_LINES; i++) {
        free(input[i]);
    }
    free(input);

    for (int i = 0; i < MAX_LINES; i++) {
        free(formated_input[i]);
    }
    free(formated_input);

    return EXIT_SUCCESS;
} 

