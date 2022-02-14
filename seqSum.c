#include "rtclock.h"
#include <stdlib.h>
#include <stdio.h>

#define N 1000000000

/**
 * Main function
 */
int main()
{
  double start = rtclock(); // start stopwatch

  long i;
  long finalSum = 0;
  for (i = 0; i <= N; i++)
  {
    finalSum += i;
  }

  double end = rtclock(); // stop stopwatch

  printf("Final Sum = %ld\n", finalSum);
  printf("Time: %.6f sec\n", ((end - start)));

  return 0;
}