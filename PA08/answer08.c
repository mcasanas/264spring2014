#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "answer08.h"

SparseNode * SparseNode_create(int index, int value)
{
  SparseNode *node = malloc(sizeof(SparseNode));
  node->index = index;
  node -> value = value;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

int SparseNode_check(SparseNode * node)
{
  if(node -> value != 0)
  {
    return 1;
  }
  else if((node -> left -> index) < (node -> index)) 
  {
    return 1;
  }
  else if((node -> right -> index) > (node -> index)) 
  {
    return 1;
  }
  return 0;
}

SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
  if(value == 0) return array;
  if(array == NULL) return SparseNode_create(index, value);
  if(array -> index == index){
    array -> value = value;
  }
  else if(array -> index > index){
    //printf("left\n");
    array -> left = SparseArray_insert(array -> left, index, value);
  }
  else if(array -> index < index){
    //printf("right\n");
    array -> right = SparseArray_insert(array -> right, index, value);
  }
  return array;
}

SparseNode * SparseArray_build(int * indices, int * values, int length)
{
  int ind;
  SparseNode *array = NULL;
  for(ind = 0; ind < length; ind++){
    //printf("%d\n", indices[ind]);
    array = SparseArray_insert(array, indices[ind], values[ind]);
    //printf("1\n");
  }

  return array;
}

void SparseArray_destroy(SparseNode * array)
{
  if(array == NULL) return;
  SparseArray_destroy(array -> left);
  SparseArray_destroy(array -> right);
  free(array);
}

int SparseArray_getMin(SparseNode * array)
{
  if(array -> left == NULL) return (array -> index);
  return SparseArray_getMin(array -> left);
}

int SparseArray_getMax(SparseNode * array)
{
  if(array -> right == NULL) return (array -> index);
  return SparseArray_getMax(array -> right);
}

SparseNode * SparseArray_getNode(SparseNode * array, int index)
{
  if(array == NULL) return NULL;
  if(array -> index == index) return array;
  if(array -> index > index){
    return SparseArray_getNode(array -> left, index);
  }
  else{
    return SparseArray_getNode(array -> right, index);
  }
}

SparseNode * SparseArray_remove(SparseNode * array, int index)
{
  if(array == NULL) return NULL;

  if(array -> index > index){
    //printf("left\n");
    array -> left = SparseArray_remove(array -> left, index);
  }
  else if(array -> index < index){
    //printf("right\n");
    array -> right = SparseArray_remove(array -> right, index);
  }

  // printf("%d %d\n", array -> index, index);
  if(array -> index == index){
    if((array -> left == NULL) && (array -> right == NULL)){
      free(array);
      return NULL;
    }
    else if((array -> left != NULL) && (array -> right == NULL)){
      //printf("lefta\n");
      array = array -> left;
      return array;
    }
    else if((array -> left == NULL) && (array -> right != NULL)){
      //printf("rightb\n");
      array = array -> right;
      return array;
    }
    else if((array -> left != NULL) && (array -> right != NULL)){
      SparseNode * temp = NULL;
      temp = SparseArray_getNode(array -> right, SparseArray_getMin(array -> right));
      // printf("%d\n",array -> left  -> index);
      
      temp -> left = array -> left;
      //if(temp -> right == NULL)
      //printf("%d\n",temp -> index);
      //array = SparseArray_remove(array, temp -> index);
      return temp;
    }  
  }

  return array;
}



SparseNode * SparseArray_copy(SparseNode * array)
{
  if(array == NULL) return NULL;
  SparseNode *tempy = NULL;
  //SparseNode * newarray = NULL;
  //newarray = malloc()
  
  SparseArray_copy(array -> left);
  tempy = array;
  SparseArray_copy(array -> right);
  //newarray = array;
  return tempy;
}


int sames(SparseNode *a, SparseNode *b)
{
  if(SparseArray_getNode(a, b -> index) == NULL){
    return 0;
  }
  else if((SparseArray_getNode(a, b -> index) -> index) == (b -> index)){
    return 1;
  }
  
  return 0;
}

SparseNode * mergeHelper(SparseNode *array1, SparseNode * array2)
{
  if(array2 == NULL) return array1;
  
  array1 = mergeHelper(array1, array2 -> left);
  array1 = mergeHelper(array1, array2 -> right);

  int same = sames(array1, array2);
  //printf("%d\n", same);

  if (same == 0){
    array1 = SparseArray_insert(array1, array2 -> index, array2 -> value);
  }
  else if(same == 1){
    //printf("%d %d\n", SparseArray_getNode(array1, array2 -> index) -> value, (array2 -> value));
    int sum = SparseArray_getNode(array1, array2 -> index) -> value + (array2 -> value);
    //printf("%d\n", sum);
    if(sum == 0){
      //printf("%d\n", array2 -> index);
      array1 = SparseArray_remove(array1, array2 -> index);
    }
    else{
      array1 = SparseArray_insert(array1, array2 -> index, sum);
    }
  }   
  /*
  if(same == 0){
    array1 = SparseArray_insert(array1, array2 -> index, array2 -> value);
  }
  else if(same == 1){
    array1 = SparseArray_insert(array1, array2 -> index, (SparseArray_getNode(array1, array2 -> index) -> value + (array2 -> value)));
  }
  */

  return array1;
}
SparseNode * SparseArray_merge(SparseNode * array_1, SparseNode * array_2)
{
  if(array_1 == NULL) return array_1;
  SparseNode *copya = NULL;
  copya = SparseArray_copy(array_1);
  copya = mergeHelper(copya, array_2);
  /*if(array_1 -> index != array_2 -> index){
    copya = SparseArray_insert(copya, array_2 -> index, array_2 -> value);
  }
  if(array_1 -> index == array_2 -> index){
    copya = SparseArray_insert(copya, array_1 -> index, (array_1 -> value) + (array_2 -> value));
  }
  */
  return copya;
  
}
