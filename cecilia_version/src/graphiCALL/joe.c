#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <timing.h>
#include <math.h>

DECLARE_DATA {
};

#include <cecilia.h>

#define _GRAPHICALL_TIMING 1
//#define _GRAPHICALL_DEBUG 1
unsigned int** children;
unsigned int* weights;
unsigned int* sons;

void work(int aow)
{
  int i, foo, bar;
  for (i=0; i < aow * 10000; i++)
  {
    foo = sqrt (aow);
    bar = pow (foo, i);
  } 
}

void METHOD(self, self_work)(void* _this, int node)
{
  int i;

  /* Do your amount of work : */
  work (weights[node]);

  /* Then call your sons : */
  for (i = 0; i < sons[node]; i++)
  {
#ifdef _GRAPHICALL_DEBUG
    printf ("CALLING %d, son of %d\n", children[node][i], node);
#endif
    CALLMINE(self, self_work, children[node][i]);
  }

}

int METHOD(entry, main)(void *_this, int argc, char** argv)
{
  unsigned int iseed = (unsigned int)time(NULL);
  int i;

  timing_init();

  srand (iseed);

  if (argc != 2)
  {
    printf ("\tUsage : ./graphiCALL filename\n");
    printf ("\t\tfilename : filename of the generated .dot file\n");
    exit (1);
  }

  /* DOT file parsing : */
  const char* filename = argv[1];
  FILE* file = fopen (filename, "r");

  //read total node number
  unsigned int nodes_number;
  fscanf(file, "%d", &nodes_number);
  children = (unsigned int**) malloc(sizeof(unsigned int*) * nodes_number);
  weights = (unsigned int*) malloc(sizeof(unsigned int*) * nodes_number);
  sons = (unsigned int*) malloc(sizeof(unsigned int*) * nodes_number); 

  unsigned int current_node;
  unsigned int weight;
  unsigned int number_of_children;


  while (fscanf(file, "%d : %d / %d", &current_node, &weight, &number_of_children) != EOF)
  {
    weights[current_node] = weight;
    sons[current_node] = number_of_children;
#ifdef _GRAPHICALL_DEBUG
    printf ("Sons for %d : %d\n", current_node, sons[current_node]);
    printf ("Work for %d : %d\n", current_node, weights[current_node]);
#endif

    if (number_of_children != 0)
    {
      children[current_node] = (unsigned int*) malloc(sizeof(unsigned int) * number_of_children);
      for (i=0; i<number_of_children;i++)
      {
        int next;
        fscanf(file, "%d,", &next);
        children[current_node][i] = next;
#ifdef _GRAPHICALL_DEBUG
        printf ("Children [%d][%d] : %d\n", current_node, i, children[current_node][i]);
#endif
      }
    } else { // current_node is a leaf.
      children[current_node] = NULL;
    }
  }

  /* First CALL : */
#ifdef _GRAPHICALL_TIMING
  tick_t t1, t2;

  GET_TICK (t1);
#endif
  CALLMINE(self, self_work, 0);
#ifdef _GRAPHICALL_TIMING
  GET_TICK (t2);
  printf ("Time : %f \n", TIMING_DELAY (t1, t2));
#endif
}
