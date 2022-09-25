#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
    int forkID = fork();

    if (forkID == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (forkID == 0)
    {
        int fileDesc = open("myfile.txt", O_WRONLY | O_CREAT, 0777);

        int dupedFileDesc = dup2(fileDesc, STDOUT_FILENO);
        close(fileDesc);

        int pfate = execlp("ping", "ping", "-c", "3", "www.google.com", NULL);
        if (pfate == -1)
        {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int wstatus;
        wait(&wstatus);

        if (WIFEXITED(wstatus))
        {
            if (WEXITSTATUS(wstatus) == 0)
            {
                fprintf(stdout, "Very Goode Siniore!\n");
            }
            else
            {
                fprintf(stderr, "program Failed!\n");
            }
        }
        else
        {
            fprintf(stdout, "NOT NORMALLY EXITED (SIGNALED)!\n");
        }
    }


    return 0;
}