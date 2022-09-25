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
    int arr2[10];

    int fifoDesc = open("myfifoSender.txt", O_RDONLY);

    if (fifoDesc == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    read(fifoDesc, arr2, 10 * sizeof(int));

    for (size_t i = 0; i < 10; i++)
    {
        printf("%d  ", arr2[i]+1);
    }
    printf("\n");
    close(fifoDesc);
    int delinfo = remove("myfifoSender.txt");

    if (delinfo == -1)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return 0;
}