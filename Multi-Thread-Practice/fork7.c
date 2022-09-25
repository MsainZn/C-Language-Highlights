#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
    int x = 55;
    int fifo_res = mkfifo("bin/myfifo.txt", 0777);

    if (fifo_res == -1)
        fprintf(stderr, "%s", strerror(errno));

    int fifoDesc = open("bin/myfifo.txt", O_WRONLY);

    if (fifoDesc == -1)
        fprintf(stderr, "%s", strerror(errno));

    write(fifoDesc, &x, 4);

    close(fifoDesc);

    return 0;
}