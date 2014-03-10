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
    array -> left = SparseArray_insert(array -> left, index, value);
  }
  else if(array -> index < index){
    array -> right = SparseArray_insert(array -> right, index, value);
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
