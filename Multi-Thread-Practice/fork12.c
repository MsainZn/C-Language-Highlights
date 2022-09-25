#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{

    //execl("/bin/ping", "ping", "-c", "5", "www.google.com", NULL);
    //execlp("ping", "ping", "-c", "5", "www.google.com", NULL);

    char* arr [] = {"ping", "-c", "5", "www.google.com", NULL};

    //execvp("ping", arr);

    execv("/bin/ping", arr);


    return 0;
}