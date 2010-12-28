#include <igraph/igraph.h>
#include <stdlib.h>
#include <stdio.h>

int create_tree (igraph_t* graph, int desired_number_of_non_leaf_nodes, int min_children, int max_children)
{
  igraph_vector_t edgelist;
  int next_parent = 0, next_child = 1, i;

  igraph_vector_init(&edgelist, 0);

  while (next_parent < desired_number_of_non_leaf_nodes) {
    int num_children = rand() % (max_children - min_children + 1) + min_children;

    if (next_parent >= next_child) {
      /* You may simply break out of the loop here instead of printing an error */
      IGRAPH_ERROR("ran out of potential parent nodes", IGRAPH_EINVAL);
    }

    for (i = 0; i < num_children; i++) {
      IGRAPH_CHECK(igraph_vector_push_back(&edgelist, next_parent));
      IGRAPH_CHECK(igraph_vector_push_back(&edgelist, next_child));
      next_child++;
    }

    next_parent++;
  }

  igraph_create(graph, &edgelist, 0, 0);

  return IGRAPH_SUCCESS;
}




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

  //igraph_write_graph_dot(&graph, fp);

  igraph_destroy(&graph);

  // Usage :
  igraph_t graph2;

  srand(time(0));
  create_tree(&graph2, 10, 0, 4);

  igraph_write_graph_dot(&graph2, fp);

  igraph_destroy(&graph2);

  return 0;
}
