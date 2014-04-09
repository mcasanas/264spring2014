#include <stdlib.h>
#include <stdio.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
  int sum = 0;
  int ind;
  for (ind = 0; ind < len; ind++){
    sum += array[ind];
  }
  return sum;
}

int arrayCountNegative(int * array, int len)
{
  int count = 0;
  int ind;
  for (ind = 0; ind < len; ind++){
    if(array[ind] < 0){
      count++;
    }
  }
    return count;
}

int arrayIsIncreasing(int * array, int len)
{
  int ind;
  if(len == 1 || array == NULL){
    return 1;
  }
  for(ind = 1; ind < len; ind++){
<<<<<<< HEAD
    if(array[ind] <= array[ind - 1]){
=======
    if(array[ind] <= array[ind -1]){
>>>>>>> d2dc3455765402c62fd71afe2701d35a6ad931f5
      return 0;
    }
  }
  return 1;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
  int ind;
<<<<<<< HEAD
  //printf("%d\n",len);
  for(ind = len-1; ind >= 0; ind--){
=======
  for(ind = len - 1; ind >= 0; ind--){
>>>>>>> d2dc3455765402c62fd71afe2701d35a6ad931f5
    if(haystack[ind] == needle){
      return ind;
    }
  }
    return -1;
}

int arrayFindSmallest(int * array, int len)
{
  if(array == NULL){
    return 0;
  }
  int ind;
  int temp = array[0];
<<<<<<< HEAD
  int pos;
=======
  int pos = 0;
>>>>>>> d2dc3455765402c62fd71afe2701d35a6ad931f5
  if(len == 1){
    return 0;
  }
  for(ind = 1; ind < len; ind++){
    if(array[ind] < temp){
      temp = array[ind];
      pos = ind;
    }
  }
  
  return pos;
}
