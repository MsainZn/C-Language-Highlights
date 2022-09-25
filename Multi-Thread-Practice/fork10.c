#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
    int forkID = fork();
    if (forkID == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (forkID == 0)
    {
        execlp("ping", "ping", "-c", "5", "www.google.com", NULL);
        printf("NOTHING WOULD BE WRITTEN HAHAHA!\n");
    }
    else
    {
        wait(NULL);
        fprintf(stderr, "%s\n", strerror(errno));
        printf("The child process is done!\n");
        fflush(stdout);
    }

    return 0;
}