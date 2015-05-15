#include "headers/bin_caller.h"
#include "../lib/my/src/headers/my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int    bin_caller(char* commandSplit[])
{
  int ret;
  int pid;
  char* env[] = {NULL};
  char* bin_to_exec;

  bin_to_exec = my_strconcat(ENV_ARG_PATH, commandSplit[0]);
  //FORK INIT
  pid = fork();
  //RETURN TEST OF FORK()
  if (pid == -1)
  {
    perror("fork()");
    return (-1);
  }
  if (pid ==  0)
  {
    ret = execve(bin_to_exec, commandSplit, env);
    return (ret); // ONLY HAPPENS WHEN EXECVE FAIL !
   }
  if (wait(&ret) >= 0 ) {
    free(bin_to_exec);
    return (ret);
  }

  return (ret);
}
