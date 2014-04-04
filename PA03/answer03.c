#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "answer03.h"

char * strcat_ex(char ** dest, int * n, const char * src)
{
  size_t src_len = strlen(src);
  size_t dest_len = *dest == NULL ? 0 : strlen(*dest);
  
  if(*dest == NULL || src_len + dest_len + 1 >= *n){
    *n = 1 + 2 * (src_len + dest_len);
    char *buffer = malloc(*n * sizeof(char));
    *buffer = '\0';
    if(*dest != NULL) strcpy(buffer, *dest);
    //free(*dest);
    //free(buffer);
    *dest = buffer;
  }
  strcat(*dest, src);
  return *dest;
}

char **explode(const char *str, const char *delims, int * arrlen)
{
  *arrlen = 1;
  const char *pos = str;
  while(*pos != '\0'){
    if(strchr(delims, *pos)) (*arrlen)++;
  }

  char **list = malloc(*arrlen * sizeof(char *));

  int ind = 0;
  const char *start = str;
  pos = str;
  while(pos != '\0'){
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
  list[ind] = malloc((len+1) * sizeof(char));
  memcpy(list[ind], start, len * sizeof(char));
  list[ind][len] = '\0';
  
  return list;
}

char * implode(char ** strArr, int len, const char * glue)
{
  char *together;
  char *buffer;
  int ind;
  int n = 0;
  strcpy(buffer, strArr[0]);
  for(ind = 1; ind < len; ind++){
    together = strcat_ex(&buffer,&n,glue);
    together = strcat_ex(&buffer,&n,strArr[ind]);
  }
  return together;
}

int strcmpvoid(const void * a , const void * b)
{
  const char *pa = *(const char**)a;
  const char *pb = *(const char**)b;
  return strcmp(pa,pb);
}

void sortStringArray(char ** arrString, int len)
{
  
  //int strcmpvoid = mystrcmp();
  qsort(arrString, len, sizeof(char *), strcmpvoid);
}


void sortStringCharacters(char * str)
{
  qsort(str, sizeof(str), sizeof(char), strcmpvoid);
}

void destroyStringArray(char ** strArr, int len)
{
  int ind;
  for(ind = 0; ind < len; ind++){
    free(strArr[ind]);
  }
}
