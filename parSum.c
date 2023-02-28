#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "parSum.h"
#include "rtclock.h"
#define N 1000000000
#define NUM_THREADS 16

/**
 * Globals (shared)
 */
long *partial_sums; // pointer to array to store each thread's partial sums

/**
 * Main function
 */
int main(int argc, char *argv[]) {
  double start = rtclock(); // start stopwatch

  /** FORK PHASE **/

  // space to hold partial sums from each thread
  partial_sums = (long*) malloc(NUM_THREADS * sizeof(long));

  // prepare thread arguments
  thread_args *args = (thread_args*) malloc(NUM_THREADS * sizeof(thread_args));
  for (int i = 0; i < NUM_THREADS; i++) {
    args[i].tid = i;
    args[i].begin = i * N / NUM_THREADS + 1;
    args[i].end = (i + 1) * N / NUM_THREADS;
  }

  // allocate space to hold threads
  pthread_t *threads = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, partialSum, &args[i]);
  }

  /** JOIN PHASE **/

  // wait for threads to finish; combine partially computed sum
  long finalSum = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    finalSum += partial_sums[i];
  }

  double end = rtclock(); // end stopwatch

  printf("Final Sum = %ld\n", finalSum);
  printf("Time: %.6f sec\n", ((end - start)));

  // clean up dynamically allocated memory
  free(partial_sums);
  partial_sums = NULL;

  free(threads);
  threads = NULL;

  free(args);
  args = NULL;

  return 0;
}

/**
 * Each thread calls this.
 * Computes a partial sum: begin + begin+1 + ... + end
 * @param *arguments a pointer to a thread_args struct
 */
void *partialSum(void *args) {
  // cast input as struct thread_args
  thread_args *params = (thread_args*) args;

  // sum for "chunk" of numbers (begin + ... + end)
  long local_sum = 0;
  for (long i = params->begin; i <= params->end; i++) {
    local_sum += i;
  }

  // store in global shared array
  partial_sums[params->tid] = local_sum;
  return NULL;
}