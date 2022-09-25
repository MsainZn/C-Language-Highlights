#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        int proRes = execlp("/bin/ping", "/bin/ping", "-c", "5", "www.yahoo.com", NULL);

        if (proRes == -1)
        {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
            exit(EXIT_SUCCESS);
    }
    else
    {
        int chiledStatus;
        wait(&chiledStatus);
        
        if (WIFEXITED(chiledStatus))
        {
            if(WEXITSTATUS(chiledStatus) == 0)
                fprintf(stdout, "Very Nice %d\n", WEXITSTATUS(chiledStatus));
            else
                fprintf(stderr, "SHoot %d\n", WEXITSTATUS(chiledStatus));
        }
        

    }


    return 0;
}