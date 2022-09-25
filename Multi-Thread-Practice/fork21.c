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
    int pipefd[3][2];

    int i;
    for (i = 0; i < 3; i++)
    {
        if (pipe(pipefd[i]) == -1)
        {
            fprintf(stderr, "%i has error: %s\n", i, strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
            fprintf(stdout, "%d Successfull!\n", i);
    }
    
    
    int forkID_1 = fork();
    if (forkID_1 == -1)
    {
        perror("forkID_1: ");
        exit(EXIT_FAILURE);
    }

    if (forkID_1 == 0)
    {
        int x;
        read(pipefd[0][0], &x, sizeof(int));
        x+=5;
        write(pipefd[1][1], &x, sizeof(int));
        
        int ii, jj;
        for(ii = 0; ii < 3; ii++)
            for(jj = 0; jj < 2; jj++)
                close(pipefd[ii][jj]);

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
        int x;
        read(pipefd[1][0], &x, sizeof(int));
        x+=5;
        write(pipefd[2][1], &x, sizeof(int));

        int ii, jj;
        for(ii = 0; ii < 3; ii++)
            for(jj = 0; jj < 2; jj++)
                close(pipefd[ii][jj]);

        return 0;
    }


    int x;
    printf("please Enter a Number: ");
    scanf("%d", &x);
    write(pipefd[0][1], &x, sizeof(int));

    read(pipefd[2][0], &x, sizeof(int));
    printf("Number is: %d\n", x);
    
    int ii, jj;
    for(ii = 0; ii < 3; ii++)
        for(jj = 0; jj < 2; jj++)
            close(pipefd[ii][jj]);


    waitpid(forkID_1, NULL, 0);
    waitpid(forkID_2, NULL, 0);

    return 0;
}