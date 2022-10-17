#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if (argc != 2) {
      printf("sleep should has 1 param");
      exit(1);
  }

  int ticks = atoi(argv[1]);
  if (sleep(ticks) != 0) {
      printf("sleep %d fail", ticks);
      exit(1);
  }
  exit(0);
}
