#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX_CHILDS 4

DECLARE_DATA {
};

#include <cecilia.h>

int my_rand ()
{
  int childs = 0;

  childs = (int)( (MAX_CHILDS + 1.0) * rand() / ( RAND_MAX + 1.0 ) );

  return childs;
}

void METHOD(self, self_work)(void* _this, int childs, int layer)
{
  int i;
  static int dummy = 0;

  if (layer != 0)
  {
    dummy++;
    printf ("Layer %d\tRound %d\tChilds %d\n", layer, dummy, childs);

    for (i = 0; i < childs; i++)
    {
      CALLMINE(self, self_work, my_rand (), layer-1);
    }
  }
}

int METHOD(entry, main)(void *_this, int argc, char** argv)
{
  unsigned int iseed = (unsigned int)time(NULL);
  srand (iseed);

  if (argc != 2)
  {
    printf ("\tUsage : ./graphiCALL layer\n\t\tlayer : number of layers in generated tree\n");
    return 1;
  }

  CALLMINE(self, self_work, my_rand (), atoi(argv[1]));

  return 0;
}
