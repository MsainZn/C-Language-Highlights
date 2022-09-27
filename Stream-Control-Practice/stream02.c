#include <stdio.h>
#include <string.h>


int main (int argc, char* argv[])
{
    double x = 22155.6548878;
    unsigned long long a = 159546847532;
    printf("%12.2lf\n%llu", x, a);

    printf("\n**********************\n");
    int dd = 13;
    printf("decimal: %d\n",  dd);
    printf("Octal: %011o\n", dd);
    printf("Hexadecimal: %#08x\n", dd);

    printf("Binary: ");

    long long int i, j;
    for (i = 0; i < sizeof(int); i++)
    {
        char byte = ((unsigned char*)&dd)[i];
        for (j = 7; j >= 0; j--)
        {
            char bit = (byte >> j) & 1;
            printf("%hhd", bit);
        }
        printf (" ");
        
    }
    puts("");



    return 0;
}