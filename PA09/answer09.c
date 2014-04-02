#include<stdio.h>
#include<stdlib.h>

#include"answer09.h"

HuffNode * HuffNode_create(int value)
{
  HuffNode *node = malloc(sizeof(HuffNode));
  node -> value - value;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

void HuffNode_destroy(HuffNode * tree)
{
  if(tree == NULL) return;
  
  HuffNode_destroy(tree -> left);
  //free(tree);
  HuffNode_destroy(tree -> right);
  free(tree);
}


Stack * Stack_create()
{
  Stack *stack = malloc(sizeof(Stack));
  stack -> head = NULL;
  free(stack);
}

void Stack_destroy(Stack * stack)
{
  if(stack ==NULL) return;
  StackNode *node = stack -> head;
  while(node != NULL){
    StackNode * tmp = node;
    node = node -> next;
    HuffNode_destroy(tmp -> tree);
    free(tmp);
  }
		      
}

int Stack_isEmpty(Stack * stack)
{
  return stack->head == NULL;
}

HuffNode * Stack_popFront(Stack * stack)
{
  if(Stack_isEmpty(stack)) return NULL;
  HuffNode *tree = stack -> head-> tree;
  StackNode *tmp = stack -> head;
  stack -> head = tmp -> next;
  free(tmp);
  return tree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
  if(stack == NULL) return;
  StackNode *node = malloc(sizeof(StackNode));
  node -> tree = tree;
  node -> next = stack -> head;
  stack -> head = node;
}

void Stack_popPopCombinePush(Stack * stack)
{
  HuffNode * first = Stack_popFront(stack);
  HuffNode * second = Stack_popFront(stack);
  HuffNode *new_node = HuffNode_create(0);
  
  new_node -> right = first;
  new_node -> left = second;
  Stack_pushFront(stack, new_node);
}

size_t Stack_size(Stack *stack)
{
  if(stack == NULL) return 0;
  size_t count = 0;
  StackNode *node = stack -> head;
  while(node != NULL){
    count++;
    node = node -> next;
  }
  return count;
}

HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  Stack * stack = Stack_create();
  int value;
  while((value = fgetc(fp)) != EOF){
    if(value == '1'){
      value = fgetc(fp);
      Stack_pushFront(stack, HuffNode_create(value));
    }
    else if(value = '0'){
      if(Stack_size(stack) == 1) break;
      Stack_popPopCombinePush(stack);
    }
  }
  HuffNode *tree = Stack_popFront(stack);
  Stack_destroy(stack);
  return tree;
}

typedef struct{
  FILE * fp;
  unsigned char byte;
  int pos;
} BitFile;

BitFile *BitFile_create(FILE *fp)
{
  BitFile *bitfile = malloc(sizeof(BitFile));
  bitfile -> fp = fp;
  bitfile -> byte = 0;
  bitfile -> pos = 8;
  return bitfile;
}

void BitFile_destroy(BitFile *bitfile)
{
  free(bitfile);
}

int BitFile_nextBit(BitFile *bitfile)
{
  if(bitfile -> pos == 8){
    bitfile -> pos = 0;
    if(fread(&(bitfile->byte), sizeof(unsigned char), 1,
	     bitfile->fp != 1){
	 return -1;
       }
  }
    int val = bitfile -> byte | (1 << pos);
    pos++;
    return val;
}

HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
  
  return NULL;
}
