#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    
    int forkID_1 = fork();
    if (forkID_1 == -1)
    {
        perror("forkID_1: ");
        exit(EXIT_FAILURE);
    }

    if (forkID_1 == 0)
    {
        printf("%d \t %d\n", forkID_1, getpid());
        return 0;
    }


    int forkID_2 = fork();
    if (forkID_2 == -1)
    {
        perror("forkID_2: ");
        exit(EXIT_FAILURE);
    }


    if (forkID_2 == 0)
    {
        printf("%d \t %d\n", forkID_2, getpid());
        return 0;
    }

    printf("%d \t %d\n", forkID_1, getpid());
    printf("%d \t %d\n", forkID_2, getpid());
    
    waitpid(forkID_1, NULL, 0);
    waitpid(forkID_2, NULL, 0);

    return 0;
}