#include<stdlib.h>
#include<stdio.h>
#include "answer10.h"
#include "tree.h"

Stack * Stack_create()
{
  Stack* stack = malloc(sizeof(Stack));
  stack -> list = NULL;
  return stack;
}

void Stack_destroy(Stack * stack)
{
  if(stack == NULL) return;
  ListNode *head = stack -> list;
  while (head != NULL){
    ListNode *tmp = head;
    head = head->next;
    free(tmp);
  }
  //Stack_destroy(stack -> list);
  free(stack);
}

int Stack_isEmpty(Stack * stack)
{
  //if(stack != NULL) return 1;
  //return 0;
  return stack == NULL || stack->list == NULL;
}

int Stack_popFront(Stack * stack)
{
  int val = stack -> list -> value;
  ListNode *tmp = stack -> list;
  stack->list = stack->list->next;
  free(tmp);
  return val;
}

void Stack_pushFront(Stack * stack, int value)
{
  ListNode*node = malloc(sizeof(ListNode));
  node->value = value;
  node->next = stack->list;
  stack->list = node;
}

int Stack_peek(Stack *stack)
{
  return stack->list->value;
}

void stackSort(int * array, int len)
{
  int wind = 0;
  Stack *stack = Stack_create();
  int ind;
  for(ind = 0; ind < len; ind++){
    int x = array[ind];
    while(!Stack_isEmpty(stack) && x > Stack_peek(stack)){
      int value = Stack_popFront(stack);
      array[wind++] = value;
    }
    Stack_pushFront(stack, x);
  }
  while(!Stack_isEmpty(stack)){
    array[wind++] = Stack_popFront(stack);
  }
  Stack_destroy(stack);
}

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
