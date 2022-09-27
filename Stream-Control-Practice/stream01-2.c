#include <stdio.h>
#include <string.h>


int main (int argc, char* argv[])
{
    char mystr[3] =  {'\0'};
    printf("Please Enter a String: ");
    
    fgets(mystr, 3, stdin);
    printf("Your input is: %s\n", mystr);
    
    printf("String Length: %lu\n", (strlen(mystr)+1));
    int i;
    for (i = 0; i < strlen(mystr)+1; i++)
    {
        printf("%d-[%d] ", i, mystr[i]);
    }
    puts("");

    if (mystr[strlen(mystr)-1] == '\n') 
        mystr[strlen(mystr)-1] = '\0';

    for (i = 0; i < strlen(mystr)+1; i++)
    {
        printf("%d-[%d] ", i, mystr[i]);
    }
    puts("");
    printf("Your input is: %s\n", mystr);
    return 0;
}