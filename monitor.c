//
// Created by wingk on 10/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc == 1) { exit(0); } // if no arg

    int num_of_cmd = 1;

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i],"!") == 0)
            num_of_cmd++;
    }

    int* cmd_len = (int*) malloc(num_of_cmd * sizeof(int));

    int tmp_len = 0;
    int index = 0;
    for (int i=1; i<argc; i++) {
        tmp_len++;
        if (strcmp(argv[i],"!") == 0) {
            cmd_len[index] = tmp_len - 1;
            index++;
            tmp_len = 0;
        }
        if (i == argc-1) {
            cmd_len[index] = tmp_len;
        }
    }

    char*** arg_vector = (char***) malloc(num_of_cmd * sizeof(char**));
    for (int i=0; i<num_of_cmd; i++)
        arg_vector[i] = (char**) malloc(num_of_cmd * sizeof(char*));

    tmp_len = 0;
    index = 0;
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i],"!") == 0) {
            index++;
            tmp_len = 0;
            continue;
        }
        arg_vector[index][tmp_len] = strdup(argv[i]);
        tmp_len++;
    }

    for (int i=0; i<num_of_cmd; i++) {
        for (int j=0; j<cmd_len[i]; j++) {
            printf("%s ", arg_vector[i][j]);
        }
        printf("\n");
    }

    return 0;
}

char* get_progname(char* arg[]) {
    if (arg[0] == '/') {
        printf("it is /\n");
    } else if (arg[0] == '.') {
        printf("it is .\n");
    } else {
        printf("it is %s\n", arg[2]);
    }
}