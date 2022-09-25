#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char* argv[])
{
    int id0 = fork();
    int id1 = fork();

    if (id0 == 0 && id1 == 0)
    {
        puts("4 or son of son");
    }
    else if (id0 != 0 && id1 == 0)
    {
        puts("3 or younger son");
    }
    else if (id0 == 0 && id1 != 0)
    {
        puts("2 or first son");
    }
    else 
    {
        puts("1 or All-father");
    }

    while (wait(NULL) != -1 || errno != ECHILD)
    {
        puts("Waiting for children to end!");
    }
    
    return 0;
}