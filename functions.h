#include <stdio.h>

int compare_strings(const void *a, const void *b) {
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcasecmp(*str_a, *str_b);
}

int handle_input(int* parameters) {
    
    int parameter = 0;

    for(int i = 0; i < 7; i++) {
        if(parameters[i] == 1) {
            parameter = 1;
        }
    }

    if (parameter) {
        printf("File in\n");
    }
    else {
        printf("Terminal in\n");
    }
    
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

    char buffer[50];
    int count = 0, len = 0, maxlen = 0;
    
    for (char c = getc(fp); c != EOF; c = getc(fp)) { //Number of lines in file and longest word

        if(c == '\n'){
            if(len > maxlen)
                maxlen = len;

            len = 0;
        }
        else
            len++;

        if (c == '\n' || c == '\t' || c == '/')
            count++;
    }

    char** dictionary = (char**) malloc(sizeof(char*) * count);

    for(int i = 0; i < count; i++)
    {
        dictionary[i] = (char*) malloc(sizeof(char) * (maxlen+1)); 
    }

    rewind(fp);

    int i = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) { //Stores dictionary into memory
        strcpy(dictionary[i], buffer);
        i++;
    }

    qsort(dictionary, count, sizeof(*dictionary), compare_strings);

    if (feof(fp)) {
        printf("End of file reached, closing...\n");
    } else if (ferror(fp)) {
        printf("An error occurred.\n");
    }

    for(int i = 0; i < count; i++)
        printf("%s", dictionary[i]);

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