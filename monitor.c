//
// Created by wingk on 10/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>

pid_t start_process(char**, struct timeval*);

void statistics(struct rusage, struct timeval, struct timeval);

void sighandler(int);

int main(int argc, char* argv[]) {

    if (argc == 1) { exit(0); } // if no arg

    signal(SIGINT,sighandler);

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

    int* pipefd = (int*) malloc((num_of_cmd-1) * sizeof(int));
    for (int i=0; i<num_of_cmd-1; i++) {
        pipe(&pipefd[2*i]);
    }

    pid_t* pids = (pid_t*) malloc(num_of_cmd * sizeof(pid_t));
    struct rusage state;
    int wstatus;
    struct timeval start, end;

    for (int i=0; i<num_of_cmd; i++) {
        pids[i] = start_process(arg_vector[i], &start);
        printf("\nProcess with id: %d created for the command: %s\n", pids[i], arg_vector[i][0]);
        wait4(pids[i], &wstatus, 0, &state);
        gettimeofday(&end, NULL);

        if (WIFEXITED(wstatus))
            printf("The command \"%s\" terminated with returned status code = %d\n\n", arg_vector[i][0], WEXITSTATUS(wstatus));
        if (WIFSIGNALED(wstatus))
            printf("The command \"%s\" is interrupted by the signal number = %d (%s)\n\n",
                   arg_vector[i][0], WTERMSIG(wstatus), strsignal(WTERMSIG(wstatus)));

        statistics(state, start, end);
    }

    return 0;
}

pid_t start_process(char** arg, struct timeval* start) {
    gettimeofday(start, NULL);
    pid_t pid = fork();
    if (pid == -1) {
        printf("fork() error!\n");
        exit(-1);
    } else if (pid == 0) {
        if (arg[0][0] == '/') {
            execv(arg[0], arg);
        } else {
            execvp(arg[0], arg);
        }
        printf("exec: : No such file or directory\n");
        printf("monitor experienced an error in starting the command: %s\n", arg[0]);
        exit(-1);
    }
    return pid;
}

void statistics(struct rusage usage, struct timeval start, struct timeval end) {
    struct timeval real;
    timersub(&end, &start, &real);
    double r_sec = real.tv_sec + (double) real.tv_usec / 1000000.0;
    double u_sec = usage.ru_utime.tv_sec + (double) usage.ru_utime.tv_usec / 1000000.0;
    double s_sec = usage.ru_stime.tv_sec + (double) usage.ru_stime.tv_usec / 1000000.0;
    printf("real: %.3f s, user: %.3f s, system: %.3f s\n", r_sec, u_sec, s_sec);
    printf("no. of page faults: %ld\n", usage.ru_minflt + usage.ru_majflt);
    printf("no. of context switches: %ld\n", usage.ru_nvcsw + usage.ru_nivcsw);
}

void sighandler(int signum) { return; }