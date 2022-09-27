#include <stdio.h>
#include <string.h>

typedef struct
{
    int a;              //4
    char k;             //1
    char myStr [10];    //10
    int* pointee;       //8
    //struct Things* th;
    short ish;          //2
} Things; // 32 - 25 = 7 bytes MISSING!!!



int main (int argc, char* argv [])
{
    int dd = 5;
    Things myth = {12, 'L', "Bijan", &dd, 256};

    int i = 0;
    printf("sizeof(Things) = %zu\n", sizeof(Things));
    for (i = 0; i < sizeof(Things); i++)
    {
        if (i%4 == 0)
            printf("\n");
        unsigned char byte = *(((unsigned char*)&dd)+i);
        printf("%c", byte);
    }
    printf("\n");




    return 0;
}