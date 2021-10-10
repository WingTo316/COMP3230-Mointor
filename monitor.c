//
// Created by wingk on 10/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if (argc == 1) { exit(0); } // if no arg

    char** argVector = malloc(argc * sizeof *argVector);

    for (int i=1; i<argc; i++) {
        argVector[i-1] = strdup(argv[i]);
    }
    // argVector[argc] = NULL;

    for (int i = 0; i < argc-1; i++) {
        printf("%s\n", argVector[i]);
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