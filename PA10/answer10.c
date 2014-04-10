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
  rMin = findMin(array, mid + 1, end);
  rMin_p = findIndex(array, rMin ,size);
  
  if(lMax > rMin) return 0;

  //RIGHT WILL UPDATE TO MAX INSTEAD OF MIN
  rMin = findMax(array, mid + 1, end);
  rMin_p = findIndex(array, rMin ,size);

  //RETURNS 1 IF LEFT AND RIGHT ARE TRUE
  return (sortHelper(array,start,lMax_p,mid-1,size)&&(sortHelper(array, mid+1, rMin_p, end, size)));
}

int isStackSortable(int * array, int len)
{
  if(len < 3) return 1;
  int max = findMax(array, 0, len - 1);
  int max_p = findIndex(array, max, len);
  return sortHelper(array, 0, max_p,len - 1, len);
} 
/*
  1.CREATE ARRAYS
  2.CHECK IF ARRAY IS SORTABLE
  3.CREATE AND PRINT TREE
  4.DON'T DUPLICATE TREES
 */
int arraySum(int *array, int len)
{
  int ind;
  int tot = 0;
  for(ind = 0; ind < len; ind++){
    tot += array[ind];
  }
  return tot;
}

int actualSum(int n)
{
  int sum = 0;
  int x = n +1;
  while(x > 0){
    sum += x--;
  }
  return sum;
}

int isDif(int * array, int n)
{
  int ind;
  int v1;
  int value;
  for(v1 = 0; v1 < n; v1++){
    value = array[v1];
    for(ind = 0; ind<n; ind++){
      if((value == array[ind]) && (v1 != ind)) return 0;
    }
  }
  return 1;
}

int createArray(int * array, int place ,int n)
{
  int ind;
  //printf("%d\n", place);
  for(ind = 0; ind < n; ind++) {
    array[place] = ind;
    if(place < n) *array = createArray(array, place+1, n);
    else if(place == n) {
      //printf("aSum = %d\ntSum = %d\nisDif = %d\n", actualSum(n),arraySum(array,n),isDif(array,n));
      if((isDif(array,n)) && (isStackSortable(array, n))){
	/*
	TreeNode *tree = malloc(sizeof(TreeNode));
	tree = Tree_build(array,n);
	Tree_printShape(tree);
	Tree_destroy(tree);
	*/
        
	for(ind = 0; ind < n; ind++){
	printf("%d ", array[ind]);
	}
	printf("\n");
	
      }
      
      return *array;
    }
  }
  return *array;
}

void genShapes(int n)
{
  //int ind;
  printf("aSum = %d\n", actualSum(n));
  int *array = malloc(sizeof(int) * n);
  /*for(ind = 0; ind < n; ind++){
    printf("%d ", array[ind]);
  }
  printf("\n\n");
  */
 *array = createArray(array, 0,n);
  /*printf("\n");
  for(ind = 0; ind < n; ind++){
    printf("%d ", array[ind]);
  }
  printf("\n");
  */
}
