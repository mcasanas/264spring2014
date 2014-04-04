#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * strcat_ex(char * * dest, int * n, const char * src)
{
  size_t src_len = strlen(src);
  size_t dest_len = *dest == NULL ? 0 : strlen(*dest);
  if (*dest == NULL || src_len + dest_len + 1 >= *n){
    *n = 1 + 2 * (src_len + dest_len);
    char *buffer = malloc(*n * sizeof(char));
    *buffer = '\0';
    if (*dest != NULL) strcpy(buffer, *dest);
    free(*dest);
    *dest = buffer;
  }
  strcat(*dest, src);
  return *dest;
}

char * * explode(const char * str, const char * delims, int * arrLen)
{
  *arrLen = 1;
  const char *pos = str;
  while(*pos != '\0'){
    if(strchr(delims, *pos)) (*arrLen)++;
    pos++;
  }
 
  char **list = malloc(*arrLen * sizeof(char *));
 
 
  int ind = 0;
  const char *start = str;
  pos = str;
  while (*pos != '\0') {
    if (strchr(delims, *pos)){
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
  memcpy(string_list[ind], start, len * sizeof(char));
  list[ind][len] = '\0';
  return list;
}
char * implode(char * * strArr, int len, const char * glue)
{
   char * str = malloc(sizeof(char));
   strcpy(str, "");
   int ind;
   int length = 0;
   for(ind = 0; ind < len; ind++)
   {
     strcat_ex(&str, &length, strArr[ind]);
     if(ind  < (len - 1))
     {
       str = strcat_ex(&str, &length, glue);
     }
   }
   return(str);
}
int compare_Array1(const void * a, const void * b)
{
  return(strcmp(*(char**)a , *(char**)b));
}
int compare_Array2(const void * a, const void *b)
{
  return(*(char*)a - *(char*)b);
}

void sortStringArray(char * * arrString, int len)
{      
   qsort(arrString, len, sizeof(char*), compare_Array1);
   return;
}    
void sortStringCharacters(char * str)
{
  qsort(str, strlen(str), sizeof(char), compare_Array2);
  return;
}
void destroyStringArray(char * * strArr, int len)
{
  int ind = 0;
  if(strArr == NULL)
  {
    return;
  }
 
  for(ind = 0; ind < len; ind++) {      
    free(strArr[ind]);
  }
  free(strArr);
  return;
  
}
