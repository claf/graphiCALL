#include <stdio.h>

DECLARE_DATA {
};

#include <cecilia.h>

void METHOD(self, self_work)(void* _this, int start, int end)
{
  int i;
  int dummy = 0;

  for (i = start; i < end; i++)
  {
    dummy += i;
    printf ("%d\n", i);
    //dummy_work();
  }
}

int METHOD(entry, main)(void *_this, int argc, char** argv)
{
  CALLMINE(self, self_work, 1, 2000);

  return 0;
}
