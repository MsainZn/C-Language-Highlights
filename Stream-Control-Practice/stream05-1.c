#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


int main (int argc, char* argv [])
{
    FILE* passwdPtr     = fopen("/home/msain1995/Desktop/passwd", "r");
    FILE* passwdFakePtr = fopen("/home/msain1995/Desktop/passwd.fake", "w");
    
    char c;
    while ( (c = fgetc(passwdPtr)) != EOF)
    {
        fputc(c, passwdFakePtr);
        putc (c, stdout);
        //printf("%c", c);
    }

    fclose(passwdFakePtr);
    fclose(passwdPtr);
    
    return 0;
}