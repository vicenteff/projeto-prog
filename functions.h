#include <stdio.h>

#define MAX_LEN 30

int compare_strings(const void *a, const void *b) {
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcasecmp(*str_a, *str_b);
}

char** handle_input(int flag, char* input_file, int* count) {
    
    char line_buffer[100];

    if ((flag == 1) && (input_file == NULL)) 
        exit(1);
    else if(input_file == NULL) {
        while(fgets(line_buffer, 100 , stdin) != NULL)
        {
            printf("%s", line_buffer);
        }
    }
    else if((flag == 1) && (input_file != NULL)) {
        FILE *fp = fopen(input_file, "r");

        *count = 0; 
        int len = 0, maxlen = 0;

        for (char c = getc(fp); c != EOF; c = getc(fp)) { //Number of lines in file and longest word
            if(c == '\n'){
                (*count)++;

                if(len > maxlen)
                    maxlen = len;
    
                len = 0;
            }
            else
                len++;
        }
        
        char** input = (char**) malloc(sizeof(char*) * *count);

        for(int i = 0; i < *count; i++)
        {
            input[i] = (char*) malloc(sizeof(char) * (MAX_LEN+1)); 
        }

        rewind(fp);

        int i = 0;

        while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL) { //Stores dictionary into memory
            strcpy(input[i], line_buffer);
            i++;
        }

        for(int i = 0; i < *count; i++)
            printf("%s", input[i]);

        fclose(fp);

        return input;
    }
    else    
        exit(1);
}

int printinput(char** input,int count) {

    for(int i = 0; i < count; i++)
        printf("%s", input[i]);

}

int handle_output(int* parameters) {
    
    int parameter = 0;

    for(int i = 0; i < 7; i++) {
        if(parameters[i] == 2) {
            parameter = 1;
        }
    }

    if (parameter) {
        printf("File out\n");
    }
    else {
        printf("Terminal out\n");
    }
    
}

int handle_dic(int flag, char* dic) {
    
    if ((flag == 3) && (dic == NULL)) 
        exit(1);

    if(dic == NULL)
        dic = "words";

    FILE *fp = fopen(dic, "r");

    if(fp==NULL)
        exit(2);

    char line_buffer[MAX_LEN+1];
    int count = 0, len = 0, maxlen = 0;
    
    for (char c = getc(fp); c != EOF; c = getc(fp)) { //Number of lines in file and longest word
        if (c == '\n' || c == '\t' || c == '/')
            count++;
    }

    char** dictionary = (char**) malloc(sizeof(char*) * count);

    for(int i = 0; i < count; i++)
    {
        dictionary[i] = (char*) malloc(sizeof(char) * (MAX_LEN+1)); 
    }

    rewind(fp);

    int i = 0;

    while (fgets(line_buffer, sizeof(line_buffer), fp) != NULL) { //Stores dictionary into memory
        strcpy(dictionary[i], line_buffer);
        i++;
    }

    qsort(dictionary, count, sizeof(*dictionary), compare_strings);

    /*for(int i = 0; i < count; i++)
        printf("%s", dictionary[i]);
    */
   
    fclose(fp);
}

int handle_alternatives(int* parameters) {

    int parameter = 0;

    for(int i = 0; i < 7; i++) {
        if(parameters[i] == 4) {
            parameter = 1;
        }
    }

    if (parameter) {
        printf("Specific Alternatives\n");
    }
    else {
        printf("10 Alternatives\n");
    }

}

int handle_differences(int* parameters) {

    int parameter = 0;

    for(int i = 0; i < 7; i++) {
        if(parameters[i] == 5) {
            parameter = 1;
        }
    }

    if (parameter) {
        printf("Specific diffs\n");
    }
    else {
        printf("2 diffs\n");
    }

}

int handle_mode(int* parameters) {

    int parameter = 0;

    for(int i = 0; i < 7; i++) {
        if(parameters[i] == 6) {
            parameter = 1;
        }
    }

    if (parameter) {
        printf("Specific Mode\n");
    }
    else {
        printf("Mode 1\n");
    }

}