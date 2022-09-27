#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int main (int argc, char* argv [])
{
    char str[1024];

    FILE* passwdPtr     = fopen("/home/msain1995/Desktop/passwd", "r");
    FILE* passwdFakePtr = fopen("/home/msain1995/Desktop/passwd.fgets", "w");

    int lineCount = 0;
    while (fgets(str, 1024, passwdPtr))
    {
        lineCount++;
        //write(fileno(passwdFakePtr), str, strlen(str));
        fputs(str, passwdFakePtr);
    }
    printf("\n%d\n", lineCount);
    fclose(passwdFakePtr);
    fclose(passwdPtr);
    
    return 0;
}