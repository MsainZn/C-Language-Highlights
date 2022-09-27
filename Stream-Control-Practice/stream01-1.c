#include <stdio.h>
#include <string.h>


int main (int argc, char* argv[])
{
    char mystr[80];
    printf("Please Enter a String: ");
    
    scanf("%[^\n]s", mystr);
    
    printf("Your input is: %s\n", mystr);
    
    getchar();

    printf("Please Enter a String: ");
    
    scanf("%[^\n]s", mystr);
    
    printf("Your input is: %s\n", mystr);

    return 0;
}