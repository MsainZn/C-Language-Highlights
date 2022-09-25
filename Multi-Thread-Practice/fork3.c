#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
    int id = fork();

    if (id == 0)
    {
        sleep(1);
        printf("FORK ID: %d, P-FORK ID: %d\n", getpid(), getppid());
    }
    else
    {
        printf("MAIN ID: %d, P-MAIN ID: %d\n", getpid(), getppid());
    }
        
    int re = wait(NULL);
    if (re == -1)
        puts("No children to wait!");
    else
        printf("%d wait for execution!\n", getpid());


    return 0;
}