#include <stdlib.h>

#include "answer10.h"
#include "tree.h"

int max_index(int * array, int start, int end)
{
  int maxNum = array[start];
  int maxInd = start;
  int ind;
  for(ind = start; ind <= end; ind++){
    if(array[ind] > maxNum){
      maxNum = array[ind];
      maxInd = ind;
    }
  }
  return maxInd; 
}
int min_index(int * array, int start, int end)
{
  int minNum = array[start];
  int minInd = start;
  int ind;
  for(ind = start; ind <= end; ind++){
    if(array[ind] < minNum){
      minNum = array[ind];
      minInd = ind;
    }
  }
  return minInd; 
}


int stackHelper(int * array, int start, int mid, int end)
{
  if((end - start) < 3) return 1;
  if(start == mid){
    return stackHelper(array, start+1, max_index(array, start+1, end),end);
  }
  else if(end == mid){
    return stackHelper(array,start, max_index(array,start, end-1),end-1);
  }

  int Lmax_ind = max_index(array,start, mid-1);
  int Rmin_ind = min_index(array,mid+1,end);
  if(array[Lmax_ind] < array[Rmin_ind]) return 1;
  else return 0;
  int Rmax_ind = max_index(array,mid+1,end);
  return (stackHelper(array,start,Lmax_ind,mid-1) && stackHelper(array,mid+1,Rmax_ind,end));
}

int isStackSortable(int * array, int len)
{
  if (len < 3) return 1;
  int max_ind = max_index(array, 0, len-1);
  return stackHelper(array, 0, max_ind, len - 1);
}

void mySwap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void shapeHelper(int*array, int pos, int n)
{
  if(pos == n){
    if(isStackSortable(array,n)){
      TreeNode *tree = Tree_build(array, n);
      Tree_printShape(tree);
      Tree_destroy(tree);
    }
  }
  else{
    int ind;
    for(ind = pos; ind < n;ind++){
      mySwap(&array[pos], &array[ind]);
      shapeHelper(array,pos+1,n);
      mySwap(&array[pos], &array[ind]);
    }
  }
}

void genShapes(int n)
{
  int *array = malloc(sizeof(int)*n);
  int ind;
  for(ind=0;ind<n;ind++){
    array[ind] = ind;
  }
  shapeHelper(array,0,n);
  free(array);
}
