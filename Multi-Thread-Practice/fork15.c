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
        while (1)
        {
            printf("do some process!\n");
            sleep(0.1);
        }
             
    }
    else
    {
        kill(forkID, SIGTSTP);
        printf("\n%d\n", forkID);
        int t;
        do
        {
            printf("Continue Execution: ");
            scanf(" %d", &t);

            if (t > 0)
            {
                kill(forkID, SIGCONT);
                printf("\n%d\n", forkID);
                sleep(t);
                kill(forkID, SIGTSTP);
                printf("\n%d\n", forkID);
            }

        } while(t > 0);


        kill(forkID, SIGKILL);
        wait(NULL);        

    }

    return 0;
}