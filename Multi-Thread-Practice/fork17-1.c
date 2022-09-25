#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

int i = -1;


void handle_SIGUSR1(int sig)
{
    if (i == -1)
        printf("\nHINT: 15\n");
}

int main(int argc, char *argv[])
{
    int forkID = fork();
    if (forkID == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (forkID ==0)
    {
        sleep(5);
        kill(getppid(), SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    else
    {
        struct sigaction sa_SIGUSR1;
        sa_SIGUSR1.sa_handler = &handle_SIGUSR1;
        sa_SIGUSR1.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &sa_SIGUSR1, NULL);

        printf("what is 5 * 3: ");
        scanf("%d", &i);

        if (i == 15)
            printf("Success...\n");  
        else
            printf("Try Again Later.\n");
        wait(NULL);
    }

    return 0;
}