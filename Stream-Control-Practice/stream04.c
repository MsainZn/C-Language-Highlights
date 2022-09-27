#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

int myPrintf (const char* strr, ...)
{
    va_list args;

    va_start(args, strr);

    vprintf(strr, args);
    
    va_end(args);
}


int main (int argc, char* argv [])
{
    char buffer[100];
    dprintf(fileno(stdout), "hello there!\n");
       
    snprintf(buffer, 100, "GENRAL KENOBI!");
    fprintf(stdout, "%s\n", buffer);


    myPrintf("salam kaftar %d hezari!\n", 2);

    return 0;
}