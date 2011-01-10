#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

DECLARE_DATA {
};

#include <cecilia.h>

#define BUFSIZE 50
#define MAXNOD 500

void METHOD(self, self_work)(void* _this, int childs, int depth)
{
  int i;
  static int dummy = 0;

  if (depth != 0)
  {
    __sync_fetch_and_add( &dummy, 1);
    printf ("Layer %d\tRound %d\tChilds %d\n", depth, dummy, childs);

    for (i = 0; i < childs; i++)
    {
      CALLMINE(self, self_work, , depth-1);
    }
  }
}

int METHOD(entry, main)(void *_this, int argc, char** argv)
{
  unsigned int iseed = (unsigned int)time(NULL);

  srand (iseed);

  if (argc != 2)
  {
    printf ("\tUsage : ./graphiCALL filename\n");
    printf ("\t\tfilename : filename of the generated .dot file\n");
    return 1;
  }

  /* DOT file parsing : */
  const char* filename = argv[1];
  FILE* file = fopen (filename, "r");

  // Consum first line (containing "graph {") :
  fgets (line, sizeof(line), file)
  printf("First line consumed : %s", line);
  
  if (file) {
    char line[BUFSIZ];
    int children[MAXNOD];
    int work[MAXNOD];
    int node = 0;

    while ( fgets (line, sizeof(line), file) )
    {
      //children[node] == ...
      char** test = strsep (&line, " -- ");
      printf("Test valeur de children[node] : %s  valeur de line : %s", test, line);
    }
  } else {
    perror (filename);
  }


  /* First CALL : */
  CALLMINE(self, self_work, , atoi(argv[1]));

  return 0;
}
