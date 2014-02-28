#include <stdio.h>
#include <stdlib.h>


void printPartition(int *partition, int length)
{

  int ind;
  printf("= ");
  for(ind = 0; ind < length; ind++)
  {
    if(ind != 0)
    {
      printf(" + ");
    }
    printf("%d", partition[ind]);
  }
  printf("\n");

}

void partitionAllHelper(int a, int *array, int pos)
{
  if(a == 0)
  {
    printPartition(array, pos);
    return;
  }

  int b;
  for(b = 1; b <= a; b++)
  {
    array[pos] = b;
    partitionAllHelper(a - b, array, pos + 1);
  }
}



void partitionIncreasingHelper(int a, int *array, int pos)
{
  if(a == 0)
  {
    //printf("\n %d\n", increaseCheck(array,pos));
    //if(increaseCheck(array, pos)){ 
      printPartition(array, pos);
      //}  
  return;
  }

  int b;
  int start = pos == 0 ? 1 : array[pos - 1] + 1;
  for(b = start; b <= a; b++)
  {
    array[pos] = b;
    partitionIncreasingHelper(a - b, array, pos + 1);    
  }
}

void partitionDecreasingHelper(int a, int *array, int pos)
{
  if(a == 0)
  {
    //printf("\n %d\n", increaseCheck(array,pos));
    //if(decreaseCheck(array, pos)) { 
      printPartition(array, pos);
      //}  
  return;
  }

  int b;
  int start = pos == 0 ? a : array[pos - 1] - 1;
  for(b = start; b > 0; b--)
  {
    array[pos] = b;
    partitionDecreasingHelper(a - b, array, pos + 1);    
  }
}

void partitionOddHelper(int a, int *array, int pos)
{
  if(a == 0)
  {
    printPartition(array, pos);
    return;
  }

  int b;
  for(b = 1; b <= a; b += 2)
  {
    array[pos] = b;
    partitionOddHelper(a - b, array, pos + 1);
  }
}

void partitionEvenHelper(int a, int *array, int pos)
{
  if(a == 0)
  {
    printPartition(array, pos);
    return;
  }

  int b;
  for(b = 2; b <= a; b += 2)
  {
    array[pos] = b;
    partitionEvenHelper(a - b, array, pos + 1);
  }
}






void partitionAll(int value)
{
  int *array = malloc(sizeof(int) * value);
  partitionAllHelper(value, array, 0);
  free(array);

}

void partitionIncreasing(int value)
{
  int *array = malloc(sizeof(int) * value);
  partitionIncreasingHelper(value, array, 0);
  free(array);
}

void partitionDecreasing(int value)
{
  int *array = malloc(sizeof(int) * value);
  partitionDecreasingHelper(value, array, 0);
  free(array);
}

void partitionOdd(int value)
{
  int *array = malloc(sizeof(int) * value);
  partitionOddHelper(value, array, 0);
  free(array);
}

void partitionEven(int value)
{
  int *array = malloc(sizeof(int) * value);
  partitionEvenHelper(value, array, 0);
  free(array);
}

