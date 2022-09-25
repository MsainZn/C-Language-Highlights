#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
    // fork happend!
    int id = fork();
    int n;
    
    if (id == 0) // child
    {
        n = 0;
    }
    else // parent
    {
        n = 6;
    }

    if (id != 0) //parent
    {
        puts("parent waits!");
        wait(NULL);
        puts("parent re-initiated!");  
    }

    if (id == 0) //parent
    {
        puts("child is started!");
    }
    else 
    {
        puts("parent is started!");
    }
    

    int i;
    for (i = n; i < n+5; i++)
    {
        printf("%d\n", i);
        fflush(stdout);
    }

    if (id == 0) //parent
    {
        puts("child is done!");
    }
    else 
    {
        puts("parent is done!");
    }
    return 0;
}