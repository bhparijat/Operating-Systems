#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int
main(int argc, char *argv[])
{
  int i;
  int max = 5;
  int pid = 0;
  char *exec_args[] = {"mult", '\0'};

  if (argc > 1) {
    max = atoi(argv[1]);
  }
  printf(1, "forking %d processes\n", max);

  for (i = 0; i < max; i++) {
    pid = fork();
    if (pid == 0) {
      exec(exec_args[0], exec_args);
      printf(1, "fork failed for process %d\n", i);
      exit();
    }
  }

  // This process does not wait for the forked programs
  // to complete. It leaves them as orphans.

  // in xv6, exit() does not take a parameter.
  exit();
}
