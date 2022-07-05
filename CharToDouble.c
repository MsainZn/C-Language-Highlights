#include <stdio.h>
// char* buffer = fgets (char* buffer, size_t buffer size, Input stream stdin) input could also be a FILE*
// int puts (const char *str) if successfull non-negetive > 0 

#include <stdlib.h>
// integer = atoi (char buffer)


int main ()
{
  // buffer size   
  size_t sizebuffer = 100;
  char *mbuffer = (char *) calloc (sizebuffer, sizeof (char));
  // integer
  int Converted_i;

  /*
    case (1): READ FROM INPUT
    returns the mbuffer from the input stream :: stdin == scanf
  */
 
  // returns mbuffer again and also copies stdin into mbuffer
  printf("Please Enter number [it would be like a character]: ");
  fgets (mbuffer, sizebuffer, stdin);

  // display string via put and also check calidity of mbuffer 
  if ( puts (mbuffer) > 0)    printf("Buffer is not NULL\n");
  //if ( puts (mbuffer) == "EOF") printf("\nBAD BAD BOY!!\n");

  if (mbuffer == NULL)
    {
      // Display Error
      perror ("Error Reading From Stream\n");
      return 1;
    }

  Converted_i = atoi (mbuffer);

  printf ("The number is doubled: %d\n", 2 * Converted_i);

  /*
    case (2): READ FROM FILE
    returns the mbuffer from a file :: fscanf
  */

  FILE *mbufferFile;

  // opening file for reading 
  mbufferFile = fopen ("mbufferfile.txt", "r");

  if (mbufferFile == NULL)
    {
      perror ("Error Reading From Stream\n");
      return -1;
    }

  // writing content to stdout 
  if ( fgets (mbuffer, sizebuffer, mbufferFile) != NULL)
  {
    printf ("The File Number is: ");
    puts (mbuffer);
  }

  fclose (mbufferFile);

  // returns the integer from char buffer
  Converted_i = atoi (mbuffer);

  printf ("The number is doubled: %d\n", 2 * Converted_i);

  return 0;

}

