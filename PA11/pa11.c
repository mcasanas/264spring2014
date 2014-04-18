#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"answer11.h"


int main(int argc, char **argv)
{
  if(argc < 2) return EXIT_FAILURE;
  int stage = atoi(argv[1]);
  char *state = argv[2];
  if(!isValidState(state)) return EXIT_FAILURE;
  
  if(stage == 1){
    //char *state = argv[2];
    char *movelist = argv[3];
    //if(!isValidState(state)) return EXIT_FAILURE;
    if(!isValidMoveList(movelist)) return EXIT_FAILURE;
    //printf("processing...\n");
    processMoveList(state, movelist);
  }
  else if(stage == 2){
    int n_moves = atoi(argv[3]);
    if(n_moves < 0 || n_moves > 9) return EXIT_FAILURE;
    MoveTree *generate = generateAll(state, n_moves);
    MoveTree_print(generate);
    free(generate);
  }
  else if(stage == 3){
    char *solution = solve(state);
    printf("%s\n", solution);
    free(solution);
  }
  return EXIT_SUCCESS;
}
