#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

SparseNode * SparseArray_insert(SparseNode * array, int index, int value)
{
  if(value == 0) return array;
  if(array == NULL) return SparseNode_create(index, value);
  if(array -> index == index){
    array -> value = value;
  }
  else if(array -> index > index){
    printf("left\n");
    array -> left = SparseArray_insert(array -> left, index, value);
  }
  else if(array -> index < index){
    printf("right\n");
    array -> right = SparseArray_insert(array -> right, index, value);
  }
  return array;
}

SparseNode * SparseArray_build(int * indices, int * values, int length)
{
  int ind;
  SparseNode *array = NULL;
  for(ind = 0; ind < length; ind++){
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
  
  if(array -> index == index){
    if((array -> left == NULL) && (array -> right == NULL)){
      free(array);
      return array;
    }
    else if((array -> left == NULL) && (array -> right != NULL)){
      array = array -> right;
      free(array -> right);
      return array;
    }
    else if((array -> left != NULL) && (array -> right == NULL)){
      array = array -> left;
      free(array -> left);
      return array;
    }
    /* else if((array -> left != NULL) && (array -> right != NULL)){
      //array = array -> right;
      SparseNode *temp = array -> right;
      while(temp -> left != NULL){
	temp = array -> left;
	if(temp -> left == NULL){
	  free(array);
	}
      }
      array = temp;
      free(temp);*/
    
  
  }
  
  if((array -> index) > index){
    return SparseArray_remove(array -> left, index);
  }
  else if(array -> index < index){
    return SparseArray_remove(array -> right, index);
  }
}

SparseNode * SparseArray_copy(SparseNode * array)
{
  if(array == NULL) return NULL;
  //SparseNode * newarray = NULL;
  //newarray = malloc()
  
  //SparseArray_copy(array -> left);
  //SparseArray_copy(array -> right);
  //newarray = array;
  return array;
}
