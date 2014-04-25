#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include "answer12.h"

int my_isspace(int ch)
{
  return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

uint128 alphaTou128(const char * str)
{
  while (*str && my_isspace(*str)) str++;
  uint128 value = 0;
  while (*str >= '0' && *str <= '9'){
    value *= 10;
    value += (*str - '0');
  }
  return value;
}

char * u128ToString(uint128 value)
{
  char buffer[sizeof(uint128) * 8 + 1];
  int write_index = sizeof(buffer) - 1;
  buffer[write_index] = '\0';
  if(value == 0){
    buffer[--write_index] = '0';
  }
  else{
    while(value > 0 ){
      buffer[--write_index] = (value % 10) + '0';
      value /= 10;
    }
  }
  int len = sizeof(buffer) - write_index;
  char *str = malloc(sizeof(char) * len);
  strcpy(str,buffer+write_index);
  return str;
}
typedef struct{
  uint128 n;
  uint128 start_n;
  uint128 stop_n;
  int *is_prime;
} Task;

void *check_prime(void *arg)
{
  Task *task = (Task *) arg;
  uint128 n = task->n;
  if(task->start_n < 3) task->start_n = 3;
  if(task->start_n % 2 == 0) task->start_n += 1;

  if(n > 2 && task->start_n < n){
    uint128 i;
    for(i = task->start_n;i<=task->stop_n && *(task->is_prime); i+=2){
      if((n%i)==0) *(task->is_prime) = 0;
    }
  }
  pthread_exit(0);
}

int primalityTestParallel(uint128 value, int n_threads)
{
  if (value <= 2) return 1;
  if((value > 2) && (value % 2 == 0)) return 0;
  uint128 max = floor(sqrt(value));
  uint128 task_size = (max + (uint128) n_threads + (uint128) 1) / (uint128) n_threads;
   
  pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);
  long *status = malloc(sizeof(long) * n_threads);
  Task *tasks = malloc(sizeof(Task) * n_threads);
  
  int is_prime = TRUE;
  int i, check;
  
  for(i = 0; i < n_threads; i++){
    tasks[i].n = value;
    tasks[i].start_n = task_size * (uint128) i;
    tasks[i].stop_n = task_size * (uint128)(i+1);
    tasks[i].is_prime = &is_prime;
  }
  
  for(i = 0; i < n_threads; i++){
    check = pthread_create(&(threads[i]), NULL, check_prime, (void*) &(tasks[i]));
    if(check){
      fprintf(stderr, "failed to create thread %d\n", i);
    }
  }

  for(i = 0; i < n_threads; i++){
    pthread_join(threads[i], (void*) &(status[i]));
  }
  
  free(threads);
  free(status);
  free(tasks);
  return is_prime;

}
/*
int genRandomArray(int number)
{
  int *array = malloc(sizeof(int) * number);
  int ind;
  for(ind = 0; ind < number; ind++){
    array[ind] = rand();
  }
  return array;
}
*/

int main(int argc, char * * argv)
{
  /*
  for(!feof(stdin)){
    int val;
    printf("> ");
    scanf("&d" &val);
    int *array = getRandomArray(val);
    qsort(array,val,sizeof(int), intcmp);
  }
  */

  //conversions
    const char * str = "340282366920938463463374607431768211455";
    uint128 w = alphaTou128(str);
    char * w_str = u128ToString(w);
    printf("Biiigggg number: %s\n", w_str);
    if(strcmp(str, w_str) != 0)
       printf("ERROR!, expected %s\n", str);
    free(w_str);
    return EXIT_SUCCESS;
  

    //primes
    if(argc != 3) return EXIT_FAILURE;
    char *num = argv[2];
    int n_threads = atoi(argv[1]);
    uint128 value = alphaTou128(num);
    int is_prime(primalityTestParallel(value, n_threads));
    return EXIT_SUCCESS;
    
    
}
