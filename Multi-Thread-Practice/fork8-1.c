#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main (int argc, char* argv[])
{
    int arr[10];

    srand(time(0));

    for (size_t i = 0; i < 10; i++)
    {
        sleep(0.05);
        arr[i] = rand()%20;
        printf("%d  ", arr[i]);
        fflush(stdout);
    }
    printf("\n");

    int fifoRes = mkfifo("myfifoSender.txt", 0777);
 
    if (fifoRes == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
   
    int fifoDesc = open("myfifoSender.txt", O_WRONLY);

    if (fifoDesc == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    write(fifoDesc, arr, 10 * sizeof(int));

    close(fifoDesc);

    return 0;
}