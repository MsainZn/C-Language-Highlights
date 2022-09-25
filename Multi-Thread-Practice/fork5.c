#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char* argv[])
{
    int pipeDest[2];
    int pd = pipe(pipeDest);

    if (pd == -1)
    {
        fprintf(stderr, "Pipe did not open, though we have to exit!\n");
        exit(1);
    }
        
    int forkID = fork();
    if (forkID == -1)
    {
        fprintf(stderr, "Fork faced error, though we have to exit!\n");
        exit(1);
    }

    if (forkID != 0)
    {
        close(pipeDest[0]);
        int x;
        printf("Please Enter a number: ");
        scanf(" %d", &x);
        write(pipeDest[1], &x, sizeof(int));
        close(pipeDest[1]);
    }
    else
    {
        close(pipeDest[1]);
        int y;
        read(pipeDest[0], &y, sizeof(int));
        close(pipeDest[0]);
        printf("You have Entered: %d\n", y);
    }

    wait(NULL);

    return 0;
}