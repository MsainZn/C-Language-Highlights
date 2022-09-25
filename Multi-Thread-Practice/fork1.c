#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char* argv[])
{
    int id = fork();
    if (id == 0)
    {
        printf("hello world from child: %d\n", id);
    }
    else
    {
        printf("hello world from main: %d\n", id);
    }

    return 0;
}