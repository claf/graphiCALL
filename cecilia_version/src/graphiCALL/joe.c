#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <timing.h>

#define my_rand() (int)( (DATA.max_childs + 1.0) * rand() / ( RAND_MAX + 1.0 ) )

DECLARE_DATA {
  int max_childs;
};

#include <cecilia.h>

void METHOD(self, self_work)(void* _this, int childs, int layer)
{
  int i, round;
  static int dummy = 0;
  tick_t t1, t2;

  GET_TICK (t1);

  __sync_fetch_and_add( &dummy, 1);
  round = dummy;

  if ((layer != 0)&&(childs != 0))
  {
    printf ("Layer %d\tRound %d\tChilds %d\n", layer, dummy, childs);

    for (i = 0; i < childs; i++)
    {
      CALLMINE(self, self_work, my_rand (), layer-1);
    }
  }

  GET_TICK (t2);
  printf ("\tTick diff for Round %d(%d) : %.0llu\n", round, dummy ,TICK_DIFF (t1, t2));
}

int METHOD(entry, main)(void *_this, int argc, char** argv)
{
  unsigned int iseed = (unsigned int)time(NULL);

  timing_init();

  srand (iseed);

  if (argc != 3)
  {
    printf ("\tUsage : ./graphiCALL layer max_childs\n");
    printf ("\t\tlayer : number of layers in generated tree\n");
    printf ("\t\tmax_childs : number of max childs in generated tree\n");
    return 1;
  }

  DATA.max_childs = atoi (argv[2]);

  CALLMINE(self, self_work, my_rand (), atoi(argv[1]));

  return 0;
}
