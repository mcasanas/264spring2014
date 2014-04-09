#include<stdlib.h>
#include "answer10.h"

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

/*
INPUTS ARRAY, START OF ADDRESS, LAST ADDRESS
RETURNS LARGEST VALUE
 */
int findMax(int * array, int start, int end)
{
  int ind;
  int val = array[start];
  for(ind = start + 1; ind <= end; ind++){
    if(array[ind]>val) val = array[ind];
  }
  return val;
}

int findMin(int * array, int start, int end)
{
  int ind;
  int val = array[start];
  for(ind = start + 1; ind <= end; ind++){
    if(array[ind]<val) val = array[ind];
  }
  return val;
}
/*
 INPUTS ARRAY, VALUE TO FIND, LENGTH OF ARRAY
 RETURNS VALUE ADDRESS
 */
int findIndex(int * array, int value, int len)
{
  int ind;
  for(ind = 0; ind < len; ind++){
    if(array[ind] == value) return ind;
  }
  return -1;
}
/*
 INPUTS ARRAY, ADDRESSES, FULL SIZE
 */
int sortHelper(int * array, int start, int mid, int end, int size)
{ 
  int len = end - start + 1;
  if(len < 3) return 1;
  
  int lMax;
  int rMin;
  int lMax_p;
  int rMin_p;
  
  if(mid == end){
    lMax = findMax(array, start, end - 1);
    lMax_p = findIndex(array, lMax ,size);
    return sortHelper(array, start, lMax_p, end - 1, size);
  }
  else if(mid == start){
    lMax = findMax(array, start + 1, end);
    lMax_p = findIndex(array, lMax ,size);
    return sortHelper(array, start + 1, lMax_p, end, size);
  }

  lMax = findMax(array, start, mid - 1);
  lMax_p = findIndex(array, lMax ,size);
  rMin = findMax(array, mid + 1, end);
  rMin_p = findIndex(array, lMax ,size);
  
  if(lMax > rMin) return 0;

  if(sortHelper(array,start,lMax_p,mid-1,size)){
    return sortHelper(array,mid+1,rMin_p,end,size);
  }
  
  return 0;
}

int isstackSortable(int * array, int len)
{
  if(len < 3) return 1;
  int max = findMax(array, 0, len - 1);
  int max_p = findIndex(array, max, len);
  return sortHelper(array, 0, max_p,len - 1, len);
} 
