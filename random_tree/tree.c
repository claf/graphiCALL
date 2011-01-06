#include <igraph/igraph.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

int create_tree (igraph_t* graph, int layers, int max_nodes, int min_children, int max_children)
{
  igraph_vector_t edgelist;
  int next_parent = 0, next_child = 1, next_layer = 1, current_layer = 1, i;

  igraph_vector_init(&edgelist, 0);

  while ((next_parent < max_nodes) || (current_layer <= layers)) {
    int num_children = rand() % (max_children - min_children + 1) + min_children;

    if (next_parent >= next_child) {
      /* You may simply break out of the loop here instead of printing an error */
      //IGRAPH_ERROR("ran out of potential parent nodes", IGRAPH_EINVAL);
      break;
    }

    for (i = 0; i < num_children; i++) {
      IGRAPH_CHECK(igraph_vector_push_back(&edgelist, next_parent));
      IGRAPH_CHECK(igraph_vector_push_back(&edgelist, next_child));
      next_child++;
      if (next_child > max_nodes)
      {
        igraph_create(graph, &edgelist, 0, 0);

        return IGRAPH_SUCCESS;
      }
    }

    next_parent++;

    if (next_parent == next_layer) 
    {
      current_layer++;
      next_layer = next_child;
    }
  }

  igraph_create(graph, &edgelist, 0, 0);

  return IGRAPH_SUCCESS;
}




int main(int argc, char** argv)
{
  char* filename, buf[50];
  int max_nodes, max_childs, layers, nb_trees, opt, ret;

  while ((opt = getopt (argc, argv, "k:f:n:c:l:")) != -1)
  {
    switch (opt)
    {
      case 'l': // layers
        layers = atoi(optarg);
        printf ("option l %d\n", layers);
        break;
      case 'k': // number of tree generated
        nb_trees = atoi(optarg);
        printf ("option k %d\n", nb_trees);
        break;
      case 'f': // file
        filename = optarg;
        printf ("option f %s\n", filename);
        break;
      case 'n': // nodes
        max_nodes = atoi(optarg);
        printf ("option n %d\n", max_nodes);
        break;
      case 'c': // childs
        max_childs = atoi(optarg);
        printf ("option c %d\n", max_childs);
        break;
      case '?':
        if ((optopt == 'c')||(optopt == 'f')||(optopt == 'n'))
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
              "Unknown option character `\\x%x'.\n",
              optopt);
        return 1;
      default:
        abort ();
    }
  }

  srand(time(0));

  igraph_t graph;
  FILE *fp;

  // Extrem case 1 :
  // 0

  // Extrem case 2 :
  // nb_trees

  // Random generation :
  for (int i=1; i < nb_trees - 1; i++)
  {
    // Files opening :
    sprintf(buf, "%s_%03d.dot", filename, i); 
    
    if((fp = fopen(buf, "wt")) == NULL)
    {
      printf ("Opening file %s\n", buf);
      exit (0);
    }

    // Graphs creation :
    //ret = igraph_tree( &graph, max_nodes, max_childs, IGRAPH_TREE_OUT);
    create_tree(&graph, layers, max_nodes, 1, max_childs);

    // Write graphs to files :
    igraph_write_graph_dot(&graph, fp);
  
    // Graphs destruction :
    igraph_destroy(&graph);
    
    // Close file :
    fclose (fp);
  }

  return 0;
}
