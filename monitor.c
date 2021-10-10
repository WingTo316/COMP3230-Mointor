//
// Created by wingk on 10/10/2021.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc == 1) { exit(0); } /* if no arg */

    if (argv[1][0] == '/') {
        printf("it is /\n");
    } else if (argv[1][0] == '.') {
        printf("it is .\n");
    } else {
        printf("it is %s\n", argv[1]);
    }

    return 0;
}