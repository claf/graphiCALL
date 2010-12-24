#include <igraph/igraph.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
  int ret;
  igraph_t graph;
  FILE *fp;

  if (argc != 2)
    printf ("\tUsage : ./tree file.dot\n");

  if((fp = fopen(argv[1], "wt")) == NULL) {
    printf("Cannot open file.\n");
    exit (0);
  }

  ret = igraph_tree( &graph, 13, 3, IGRAPH_TREE_OUT);

  if (ret == IGRAPH_EINVAL)
    printf ("ERROR : invalid number of vertices\n");
  else
    printf ("Tree created!\n");

  igraph_write_graph_dot(&graph, fp);

  igraph_destroy(&graph);
  
  return 0;
}
