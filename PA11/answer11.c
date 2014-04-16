
#include "answer11.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Prints the puzzle-state as a 2d matrix. 
 * This function is supplied to you.
 */
void printPuzzle(const char * state)
{
    int row, col;
    for(row = 0; row < SIDELENGTH; ++row) {
	for(col = 0; col < SIDELENGTH; ++col) {
	    printf(" %c", state[row*SIDELENGTH + col]);
	}
	printf("\n");
    }
}

/**
 * Print the moves in a move-tree.
 * This function is supplied to you.
 */
void MoveTree_print(MoveTree * node)
{
    if(node == NULL)
	return;
    printf("%s\n", node -> state);
    MoveTree_print(node -> left);
    MoveTree_print(node -> right);
}

int compareArray(const void *a, const void *b)
{
  return(*(char*)a - *(char*)b);
}

int isValidState(const char * state)
{
  if(strlen(state) != 16) return 0;
  char buffer[17];
  strcpy(buffer, state);
  qsort(buffer, 16,sizeof(char),compareArray);
  const char *valid = "-123456789ABCDEF";
  if(strcmp(buffer, valid) == 0) return 1;
  return 0;
}

int isValidMoveList(const char * movelist)
{
  int ind;
  const char *valid = "RLUD";
  int len = strlen(movelist);
  for(ind = 0; ind<len; ind++){
    if(strchr(valid, movelist[ind]) == NULL) return 0;
  }
  return 1;
}
void swap(char *a, char*b)
{
  char tmp = *a;
  *a = *b;
  *b = tmp;
}
int move(char * state, char m)
{
  int pos;
  for(pos = 0; pos < SIDELENGTH * SIDELENGTH; pos++){
    if(state[pos] == '-') break;
  }
  int row = pos/SIDELENGTH;
  int col = pos%SIDELENGTH;
  int new_row = row, new_col = col;
  switch(m){
  case 'U': new_row = row - 1; break;
  case 'D': new_row = row + 1; break;
  case 'L': new_col = col - 1; break;
  case 'R': new_col = col + 1; break;
  }
  if(new_row < 0 || new_row >= SIDELENGTH || new_col < 0 || new_col >= SIDELENGTH) return 0;
  int target_pos = new_row * SIDELENGTH + new_col;
  swap(state + pos, state+target_pos);
  return 1;
}

void processMoveList(char * state, const char * movelist)
{
  int ind;
  int len = strlen(movelist);
  for(ind = 0; ind < len; ind++){
    if(move(state,movelist[ind]) == 0){
      printf("I\n");
      return;
    }
  }
  printf("%s\n", state);
}

MoveTree * MoveTree_create(const char*state, const char*moves)
{
  MoveTree * node = malloc(sizeof(MoveTree));
  node -> state = strdup(state); 
  node -> moves = strdup(moves);
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

void MoveTree_destroy(MoveTree * node)
{
  if(node == NULL) return;
  MoveTree_destroy(node->left);
  MoveTree_destroy(node->right);
  free(node->state);
  free(node->moves);
  free(node);
}
MoveTree * MoveTree_insert(MoveTree * node, const char * state, const char * moves)
{
  if(node == NULL) return MoveTree_create(state, moves);
  int cmp = strcmp(state, node->state);
  if(cmp==0){
    if(strlen(move) < strlen(node -> moves)){
      free(node->moves);
      node->moves = strdup(moves);
    }
  }
  else if(cmp < 0){
    node->left = MoveTree_insert(node->left, state, moves);
  }
  else if(cmp > 0){
    node->right = MoveTree_insert(node->right, state, moves );
  }
  return node;
}

MoveTree * MoveTree_find(MoveTree * node, const char * state)
{
  if(node == NULL) return NULL;
  int cmp = strcmp(state, node->state);
  if (cmp==0) return node;
  else if(cmp<0) return MoveTree_find(node->left, state);
  else if(cmp>0) return MoveTree_find(node->right,state);
}
//movetree_print
void generateAllHelper(MoveTree * root, int n_moves, const char * state, char * movelist, int ind)
{
  
}

MoveTree * generateAll(char * state, int n_moves)
{
}


int main(int argc, char ** argv)
{
  if(argc != 3) return 0;
  char *state = argv[1];
  char *movelist = argv[2];
  if(!isValidState(state)) return 0;
  if(!isValidMoveList(movelist)) return 0;
  processMoveList(state, movelist);
  return 1;
}
