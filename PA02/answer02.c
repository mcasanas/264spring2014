#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "answer02.h"

size_t my_strlen(const char * str)
{
  //if(str == NULL) return NULL;
  size_t count = 0;
  while(str[count] != '\0'){
    count++;
  }
  return count;
}

int my_countchar(const char * str, char ch)
{
  int count = 0;
  int ind = 0;
  while(str[ind] != '\0'){
    //printf("%c\n", str[ind]);
    if(str[ind] == ch){
      count++;
      ind++;
    }
    else{
      ind++;
    }
  }
  return count;
}

char * my_strchr(const char * str, int ch)
{
  //IF \0 IS INPUT
  if(ch == '\0') return (char *)(str + my_strlen(str));
  
  while(*str){
    if(*str == ch) return (char *) str;
    str++;
  }
  return NULL;

}

char * my_strrchr(const char * str, int ch)
{
  const char *end = str + my_strlen(str);
  while(end >= str){
    if(*end == ch) return (char *) end;
    end--;
  }
  return NULL;
}

char * my_strstr(const char * haystack, const char * needle)
{
  if(*needle == '\0') return (char*)haystack;
  while(*haystack != '\0'){
    const char *p1 = haystack;
    const char *p2 = needle;
    while(*p1 == *p2 && *p1 != '\0' && *p2 != '\0'){
      p1++;
      p2++;
    }
    if(*p2 == '\0') return (char*)haystack;
    haystack++;
  }
  return NULL;
}

char * my_strcpy(char * dest, const char * src)
{
  char *original = dest;
  while(*src){
    *dest++ = *src++;
  }
  *dest = '\0';
  return original;
}
