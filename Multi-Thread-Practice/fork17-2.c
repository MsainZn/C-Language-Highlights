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
        printf("\nhelp\n");
    }
    else
    {
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