#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "answer03.h"

char * strcat_ex(char ** dest, int * n, const char * src)
{
  /*
  char * buffer = NULL;
  buffer = malloc(1 + 2*(strlen(*dest) + strlen(src)));
  buffer = strcpy(buffer, *dest);
  //free(dest);
  dest = &buffer;
  strcat(buffer, src);
  *n = sizeof(buffer);
  printf("%d %s\n",*n, buffer);
  *dest = buffer;
  free(buffer);
  return *dest;*/
  
  size_t src_len = strlen(src);
  size_t dest_len = (*dest == NULL ? 0 : strlen(*dest));
  
  if(*dest == NULL || src_len + dest_len + 1 >= *n){
    
    *n = 1 + 2*(src_len + dest_len);
    printf("%d\n", *n);
    char * buffer = malloc(*n * sizeof(char));
    printf("%s\n", buffer);
    *buffer = '\0';
    if(*dest != NULL) strcpy(buffer, *dest);
    printf("%s  %d\n%s  %d\n", buffer, strlen(buffer),  *dest, strlen(*dest));
    //free(buffer);
    //dest = malloc(*n * sizeof(char));
    *dest = buffer;
    free(buffer);
    
  }
  strcat(*dest, src);
  return *dest;
}
/*
char * * explode(const char * str, const char * delims, int * arrLen)
{
  *arrLen = 1;
  const char *pos = str;
  while(*pos != '\0'){
    if (strchr(delims, *pos)) *arrLen++;
  }

  char **list = malloc(*arrLen * sizeof(char*));

  int ind = 0;
  const char *start = str;
  pos = str;
  while(*pos != '\0'){
    if(strchr(delims, *pos)){
      int len = pos - start;
      list[ind] = malloc((len + 1) * sizeof(char));
      memcpy(list[ind], start, len * sizeof(char));
      list[ind][len] = '\0';
      ind++;
      start = pos + 1;
    }
    pos++;
  }


  int len = pos - start;
  list[ind] = malloc((len + 1) * sizeof(char));
  
  }*/
