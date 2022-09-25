#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

int main (int argc, char* argv[])
{
    
    int arr[] = {1,2,3,4,5,6};
    size_t arrSize = sizeof(arr)/sizeof(arr[0]);
    size_t start, end;
    printf("arr size is = %lu\n", arrSize);
    int pipeDesc[2];
    int pipeRes = pipe(pipeDesc);

    if (pipeRes == -1)
    {
        fprintf(stderr, "Pipe did not created!\n");
        EXIT_FAILURE;
    }


    int forkID = fork();
    if (pipeRes == -1)
    {
        fprintf(stderr, "Fork did not created!\n");
        EXIT_FAILURE;
    }

    if (forkID == 0)
    {
        start = 0;
        end = arrSize/2;
        printf("<<CHILD>> start = %lu\t end = %lu\n", start, end);

    }        
    else
    {
        start = arrSize/2;
        end = arrSize;
        printf("<<PARENT>> start = %lu\t end = %lu\n", start, end);
    }

    size_t i;
    int summ = 0; 
    for (i = start; i < end; i++)
    {
        summ += arr[i];
    }
    

    if (forkID == 0)
    {
        close(pipeDesc[0]);
        write(pipeDesc[1], &summ, sizeof(int));
        close(pipeDesc[1]);
        printf("summ in child = %d\n", summ);
    }
    else
    {
        int summChild;
        close(pipeDesc[1]);
        read(pipeDesc[0], &summChild, sizeof(int));
        close(pipeDesc[0]);
        printf("summ in parent = %d\n", summ);
        summ+= summChild;
        printf("All sum = %d\n", summ);
        wait(NULL);
    }

    return 0;
}