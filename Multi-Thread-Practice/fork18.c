#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int piped[2];
    srand(time(NULL));

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
        int iMAX = 10;
        int arr[10] = {0};

        int i;
        for (i = 0; i < 10; i++)
        {
            arr[i] = (rand() % 9) + 1;
            printf("%d  ", arr[i]);
        }
        puts("");
        write(piped[1], &iMAX, sizeof(int));
        puts("Size Sent");
        write(piped[1], arr, sizeof(int)*iMAX);
        puts("Array Sent");
        close(piped[1]);
    }
    else
    {
        close(piped[1]);      
        int iMAX;
        int arrElement = 0, summ = 0;
        read(piped[0], &iMAX, sizeof(int));
        puts("Size Recieved");
        
        int i;
        for (i = 0; i < iMAX; i++)
        {
            arrElement;
            read(piped[0], &arrElement, sizeof(int));
            summ+=arrElement;
        }
        puts("Array Recieved");

        printf("Sum is: %d\n",summ);
        close(piped[0]);
        wait(NULL);
    }

    return 0;
}