#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

typedef struct Points
{
    int x;
    int y;

} Points;

int main (int argc, char* argv [])
{
    
    Points p1 = 
    {
        .x = 12,
        .y = -23
    };
    
    Points p2;

    char writeBuffer[BUFFER_SIZE] = {'\0'};
    char readBuffer[BUFFER_SIZE]  = {'\0'};

    FILE* readPtr;
    FILE* writePtr;

    writePtr = fopen("/home/msain1995/Desktop/dataWrite.txt", "w");
    if (writePtr == NULL)
    {
        perror("Write Process: ");
        exit(EXIT_FAILURE);
    }
    
    snprintf(writeBuffer, BUFFER_SIZE, "%d, %d\n", p1.x, p1.y);
    fwrite(writeBuffer, sizeof(char), strlen(writeBuffer), writePtr);
    
    fclose(writePtr);

//*************************************************************************************//

    readPtr = fopen("/home/msain1995/Desktop/dataWrite.txt", "r");
    if (writePtr == NULL)
    {
        perror("Read Process: ");
        exit(EXIT_FAILURE);
    }
    
    fgets(readBuffer, BUFFER_SIZE, readPtr);
    
    sscanf(readBuffer, "%d, %d\n", &p2.x, &p2.y);

    printf("x = %d \t y = %d\n", p2.x, p2.y);

    fclose(readPtr);
    
    return 0;
}