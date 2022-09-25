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
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    int forkID = fork();
    if (forkID == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (forkID == 0)
    {
        close(piped[0]);
        char buffer[20] = {'\0'};

        printf("Please Enter Your Name: ");
        fgets(buffer, 20, stdin);
        
        int i;
        for (i = 0; i < 20; i++)
            printf("%d ", buffer[i]);
        puts("");

        // replace '\n' inserted by fgets with '\0'
        buffer[strlen(buffer)-1] = '\0'; 

        for (i = 0; i < 20; i++)
            printf("%d ", buffer[i]);
        puts("");

        int n = strlen(buffer) + 1; 
        write(piped[1], &n, sizeof(int));
        puts("Size Sent");

        write(piped[1], buffer, n * sizeof(char));
        puts("String Sent");
        close(piped[1]);
    }
    else
    {
        close(piped[1]);      
        int iMAX;
        read(piped[0], &iMAX, sizeof(int));
        puts("Size Recieved");
        char* strRec = (char*) malloc(sizeof(char)*iMAX);       

        read(piped[0], strRec, iMAX*sizeof(char));
        puts("Array Recieved");

        printf("Recieved string is: %s\n", strRec);
        free(strRec);
        close(piped[0]);
        wait(NULL);
    }

    return 0;
}