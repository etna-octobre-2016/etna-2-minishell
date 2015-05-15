#include "headers/bin_caller.h"
#include "../lib/my/src/headers/my.h"
#include <unistd.h>
#include <stdlib.h>


int    bin_caller(char* commandSplit[])
{
  int ret;
  char* env[] = {NULL};
  char* bin_to_exec;

  bin_to_exec = my_strconcat(ENV_ARG_PATH, commandSplit[0]);
  ret = execve(bin_to_exec, commandSplit, env);
  free(bin_to_exec);
  return (ret);
}
