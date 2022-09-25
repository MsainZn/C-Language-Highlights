#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

int main (int argc, char* argv[])
{
    int forkID = fork();

    if (forkID == 0)
    {
        int i = 0;
        while (1)
        {
            printf("%d im just a child!\n", i++);
            sleep(0.5);

        }
    }
    else
    {
        sleep(5);
        kill(forkID, SIGKILL);
        wait(NULL);
        printf("child is dead!\n");
    }
    


    return 0;
}