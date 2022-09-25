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
    int piped[2];
    int pipeRes = pipe(piped);
    if (pipeRes == -1)
    {
        perror("pipe: ");
        exit(EXIT_FAILURE);
    }

    int forkID = fork();
    if (forkID == -1)
    {
        perror("First fork: ");
        exit(EXIT_FAILURE);
    }

    
    if (forkID == 0)
    {
        close(piped[0]);
        dup2(piped[1], STDOUT_FILENO);
        close(piped[1]);

        int execRes;
        execRes = execlp("ping", "ping", "-c", "5", "google.com", NULL);
        if (execRes == -1)
        {
            perror("Website or ping setting has error: ");
            exit(EXIT_FAILURE);
        }
    } 
    else
    {
        int wstat;
        wait(&wstat);
        if (WIFEXITED(wstat))
        {
            if (WEXITSTATUS(wstat) == 0)
                fprintf(stdout, "ping process was successfull!\n");
            else
            {
                perror("Website or ping setting has error: ");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "Process Signaled and Ended Unsuccessfully!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    
    int forkID2 = fork();
    if (forkID2 == -1)
    {
        perror("Second fork: ");
        exit(EXIT_FAILURE);
    }

    if (forkID2 == 0)
    {
        close(piped[1]);
        dup2(piped[0], STDIN_FILENO);
        close(piped[0]);

        int execRes;
        execRes = execlp("grep", "grep", "rtt", NULL);
        if (execRes == -1)
        {
            perror("grep has error: ");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        close(piped[0]);
        close(piped[1]);

        int wstat;
        wait(&wstat);
        if (WIFEXITED(wstat))
        {
            if (WEXITSTATUS(wstat) == 0)
                fprintf(stdout, "grep process was successfull!\n");
            else
            {
                perror("grep has error: ");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "grep is Signaled and Ended Unsuccessfully!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    
    return 0;
}