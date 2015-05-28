#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../lib/my/src/headers/my.h"
#include "headers/bin_caller.h"
#include "headers/parser.h"
#include "headers/prompt.h"
#include "headers/redirections.h"
#include "headers/pipeline.h"

t_cmd_list*   pipeline(t_cmd_list *cmd, int input)
{
  char**      commandSplit;
  int         pipe_var[2];
  int         ret;

  pipe_var[0] = -1;
  pipe_var[1] = -1;
  if (cmd->next != NULL)
  {
    pipe(pipe_var);
  }
  if (fork() == 0) // child process
  {
    if (input != -1)
    {
      dup2(input, STDIN_FILENO);
      close(input);
    }
    if (pipe_var[1] != -1 && !cmd->is_redirect_output)
    {
      dup2(pipe_var[1], STDOUT_FILENO);
      close(pipe_var[1]);
    }
    if (cmd->is_redirect_output)
    {
      cmd = redirections(cmd);
      exit(0);
    }
    if (pipe_var[0] != -1)
    {
      close(pipe_var[0]);
    }
    commandSplit = split_cmd(cmd->cmd);
    ret = 0;
    ret = bin_caller(commandSplit);
    free_array(commandSplit);
    exit(1);
  }
  if (wait(&ret) >= 0) // parent process
  {
    if (input != -1)
    {
      close(input);
    }
    if (pipe_var[1] != -1)
    {
      close(pipe_var[1]);
    }
    if (cmd->next != NULL && !cmd->is_redirect_output)
    {
      cmd = cmd->next;
      return(pipeline(cmd, pipe_var[0]));
    }
  }
  if (cmd->is_redirect_output)
  {
    cmd = cmd->next;
  }
  return (cmd);
}
