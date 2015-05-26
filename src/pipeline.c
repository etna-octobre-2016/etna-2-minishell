#include "../lib/my/src/headers/my.h"
#include "headers/prompt.h"
#include "headers/pipeline.h"
#include "headers/parser.h"
#include "headers/bin_caller.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

t_cmd_list *pipeline(t_cmd_list *cmd, int input)
{
  // last command
  char** commandSplit;
  int pipe_var[2];
  int ret;

  pipe_var[0] = -1;
  pipe_var[1] = -1;
  if (cmd->next != NULL)
  {
    pipe(pipe_var);
  }
  if (fork() == 0)
  { /* child */
    if (input != -1)
    {
      // my_printf("Child : input != -1 : cmd : %s\n",cmd->cmd);
      dup2(input, STDIN_FILENO);
      close(input);
    }
    if (pipe_var[1] != -1)
    {
      // my_printf("Child : pipe_var[1] != -1 : cmd : %s\n",cmd->cmd);
      dup2(pipe_var[1], STDOUT_FILENO);
      close(pipe_var[1]);
    }
    if (pipe_var[0] != -1)
    {
      // my_printf("Child : pipe_var[0] != -1 : cmd : %s\n",cmd->cmd);
      close(pipe_var[0]);
    }
    commandSplit = split_cmd(cmd->cmd);
    ret = 0;
    ret = bin_caller(commandSplit);
    free_array(commandSplit);
    exit(1);
  }
  if (wait(&ret) >= 0)
  { /* parent */
    if (input != -1)
    {
      // my_printf("Parent : input != -1 : cmd : %s\n",cmd->cmd);
      close(input);
    }
    if (pipe_var[1] != -1)
    {
      // my_printf("Parent : pipe_var[1] != -1 : cmd : %s\n",cmd->cmd);
      close(pipe_var[1]);
    }
    if (cmd->next != NULL)
    {
      cmd = cmd->next;
      // my_printf("Parent : Next cmd  : cmd : %s\n",cmd->cmd);
      return(pipeline(cmd, pipe_var[0]));
    }
  }
  // my_printf("Return cmd : %s\n",cmd->cmd);
  return (cmd);
}
