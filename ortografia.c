#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h>
#include <string.h>
#include "functions.h"
  
int main(int argc, char *argv[])  
{ 
    int opt; 

    char* dic = NULL;
    char* input_file = NULL;

    int *parameters = (int*) malloc(7 * sizeof(int)); //Array to check if all parameters were specified

    for(int i = 0; i < 7; i++) {
        parameters[i] = 0;
    }
       
    /*
    Paramater IDs:
    0 - Help
    1 - Input
    2 - Dictionary
    3 - Output
    4 - Alternatives
    5 - Differences
    6 - Mode
    */

    while((opt = getopt(argc, argv, "hd:i:o:n:m:a:")) != -1)  
    {  
        switch(opt)  
        {  
            case 'h':  
                printf("Help\n");  
                break;  
            case 'i':  
                input_file = (char*) malloc(strlen(optarg));
                strcpy(input_file,optarg);
                printf("Input: %s\n", input_file);
                parameters[1]=1;
                break;
            case 'd':  
                dic = (char*) malloc(strlen(optarg));
                strcpy(dic,optarg);
                printf("Dictionary: %s\n", dic);
                parameters[2]=2; 
                break;  
            case 'o':  
                char* out = (char*) malloc(strlen(optarg));
                strcpy(out,optarg);
                printf("Output: %s\n", out);
                parameters[3]=3;           
                break;  
            case 'a':  
                char* alt = (char*) malloc(strlen(optarg));
                strcpy(alt,optarg);
                printf("Alternatives: %d\n", atoi(alt));
                parameters[4]=4;
                break;  
            case 'n':  
                char* diff = (char*) malloc(strlen(optarg));
                strcpy(diff,optarg);
                printf("Differences: %d\n", atoi(diff));
                parameters[5]=5; 
                break;  
            case 'm':
                char* mode = (char*) malloc(strlen(optarg));
                strcpy(mode,optarg);
                printf("Mode: %d\n", atoi(mode));
                parameters[6]=6;
                break;
        }  
    }  

    int count = 0;

    handle_dic(parameters[2], dic);
    char** input = handle_input(parameters[1], input_file, &count);
    printinput(input, count);
      
    return 0; 
} 

