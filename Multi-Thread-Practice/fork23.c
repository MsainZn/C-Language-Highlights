#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define PROCESS_NUMBER 30

int main(int argc, char *argv[])
{
    // CREATE FORK
    int pipedesc[PROCESS_NUMBER+1][2];
    int i;
    for (i = 0; i < PROCESS_NUMBER+1; i++)
    {
        if (pipe(pipedesc[i]) == -1)
        {
            fprintf(stderr, "Number %i Descriptor Faced Problem: %s\n", i, strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    int forkID[PROCESS_NUMBER];
    for (i = 0; i < PROCESS_NUMBER; i++)
    {
        // CREATE PROCESS VIA FORK
        forkID[i] = fork();
        if (forkID[i] == -1)
        {
            fprintf(stderr, "Number %i FORK Faced Problem: %s\n", i, strerror(errno));
            exit(EXIT_FAILURE);
        }
        // DO THINGS
        if (forkID[i] == 0)
        {
            int j = 0;
            for (j = 0; j < PROCESS_NUMBER + 1; j++)
            {
                // READ
                if (i != j)   close(pipedesc[j][0]);
                // WRITE
                if (i+1 != j) close(pipedesc[j][1]);
            }
            
            int x;
            read (pipedesc[i][0], &x, sizeof(int));
            fprintf(stdout, "PROCESS %2d - GET:  %d\n", i, x);
            fflush(stdout);
            x++;
            write(pipedesc[i+1][1], &x, sizeof(int));
            fprintf(stdout, "PROCESS %2d - SENT: %d\n", i, x);
            fflush(stdout);
            close(pipedesc[i][0]);
            close(pipedesc[i+1][1]);
            return 0;
        }
            
    }
    
    // PARENT PROCESS
    int j;
    for (j = 0; j < PROCESS_NUMBER + 1; j++)
    {
        // READ
        if (j != PROCESS_NUMBER)   
            close(pipedesc[j][0]);
        // WRITE
        if (j != 0) 
            close(pipedesc[j][1]);
    }
    
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    write(pipedesc[0][1], &x, sizeof(int));    
    read(pipedesc[PROCESS_NUMBER][0], &x, sizeof(int));
    printf("The Final Number is: %d\n", x);
    fflush(stdout);

    close(pipedesc[0][1]);
    close(pipedesc[PROCESS_NUMBER][0]);

    // Finish all Child Process
    for (i = 0; i < PROCESS_NUMBER; i++)
        wait(NULL);
    
    return 0;
}