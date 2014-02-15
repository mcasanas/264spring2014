#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{
  int i;
  //int quote = 34;
  for(i = 1; i < argc; i++)
  {
    if(*argv[i] == '\"'){printf(" ");}
    else{printf("%s", argv[i]);}
    
    if (i != argc - 1 ) 
    {
      printf(" ");
    }
  }


  printf("\n");
  return EXIT_SUCCESS;
}
