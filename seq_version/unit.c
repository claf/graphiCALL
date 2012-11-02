#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <timing.h>
#include <math.h>

#define _GRAPHICALL_TIMING 1
//#define _GRAPHICALL_DEBUG 1
unsigned int** children;
unsigned int* weights;
unsigned int* sons;

void work(int aow)
{
  int i, foo, bar;
  for (i=0; i < aow * 10; i++)
  {
    foo = sqrt (aow);
    bar = pow (foo, i);
  } 
}

int main(int argc, char** argv)
{
  unsigned int iseed = (unsigned int)time(NULL);
  int i;

  timing_init();

  /* First CALL : */
#ifdef _GRAPHICALL_TIMING
  tick_t t1, t2;

  GET_TICK (t1);
#endif
  work (2000);

#ifdef _GRAPHICALL_TIMING
  GET_TICK (t2);
  printf ("Time : %f \n", TIMING_DELAY (t1, t2));
#endif
  return 1;
}
