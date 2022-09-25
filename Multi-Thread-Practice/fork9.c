#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main (int argc, char* argv[])
{
    srand(time(NULL));

    int pipeFileDesc_C2P[2];
    int pipeFileDesc_P2C[2];
    int pipe_res1 = pipe(pipeFileDesc_C2P);
    int pipe_res2 = pipe(pipeFileDesc_P2C);

    if (pipe_res1 == -1)
    {
        fprintf(stderr, "Pipe-1: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (pipe_res2 == -1)
    {
        fprintf(stderr, "Pipe-2: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    int forkID = fork();

    if (forkID == 0)
    {
        close(pipeFileDesc_C2P[0]);
        close(pipeFileDesc_P2C[1]);
        int x = rand()%10;
        printf("x generated in child: %d\n", x);
        write(pipeFileDesc_C2P[1], &x, sizeof(int));
        read (pipeFileDesc_P2C[0], &x, sizeof(int));
        printf("x after Recieved in Child Again: %d\n", x);
        close(pipeFileDesc_C2P[1]);
        close(pipeFileDesc_P2C[0]);
    }
    else
    {
        close(pipeFileDesc_C2P[1]);
        close(pipeFileDesc_P2C[0]);
        int y;
        read (pipeFileDesc_C2P[0], &y, sizeof(int));
        y *= 4;
        write(pipeFileDesc_P2C[1], &y, sizeof(int));
        close(pipeFileDesc_C2P[0]);
        close(pipeFileDesc_P2C[1]);
        wait(NULL);
    }


    return 0;
}