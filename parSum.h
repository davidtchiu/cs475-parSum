// /** globals (shared) */
// extern long *partial_sums; // to hold outputs from threads

/** struct to hold parameters to partialSum() **/
typedef struct thread_args
{
  int tid;    // the given thread id (0, 1, ...)
  long begin; // where to begin summation
  long end;   // where to end summation
} thread_args;

/** Functiun delcarations */
void *partialSum(void *args);
