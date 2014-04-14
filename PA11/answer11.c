
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
  return(*(int*)a - *(int*)b);
}
int sumString(const char * buffer)
{
  int ind;
  int tot=0;
  for(ind = 0;ind < 16;ind++){
    tot += atoi(buffer[ind]);
  }
}
int isValidState(const char * state)
{
  if(strlen(state) != 16) return 0;
  const char * buffer = strdup(state);
  qsort(&buffer, 16,sizeof(int),compareArray);
  if(sumString(buffer) == 927) return 1;
  return 0;
}

int isValidMoveList(const char * movelist)
{
  return 0;
}

int move(char * state, char m);

void processMoveList(char * state, const char * movelist);

MoveTree * MoveTree_create(const char*state, const char*moves);

void MoveTree_destroy(MoveTree * node)
{
  if(node == NULL) return;
  MoveTree_destroy(node->left);
  MoveTree_destroy(node->right);
  free(node);
}
