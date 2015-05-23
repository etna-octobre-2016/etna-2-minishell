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

int pipe_trigger = 0;

t_cmd_list *pipeline(t_cmd_list *cmd, int input_fd[2])
{
  // last command
  int   childpid;
  char** commandSplit;
  int ret;

  commandSplit = split_cmd(cmd->cmd);

  my_printf("cmd->cmd = %s\n", cmd->cmd);
  my_printf("commandSplit[0] = %s\n", commandSplit[0]);
  my_printf("commandSplit[1] = %s\n", commandSplit[1]);
  if (pipe_trigger == 0)
  {
    if (pipe(input_fd) == -1)
    {
      exit(1);
    }
    pipe_trigger++;
    my_printf("PIPE_TRIGGER = %d", pipe_trigger);
  }
  if (!cmd->is_piped)
  {
    if((childpid = fork()) == -1)
    {
            perror("fork");
            exit(1);
    }
    if(childpid == 0)
    {
            /* Child process closes up input side of pipe */
            dup2(input_fd[0], 0);

            ret = bin_caller(commandSplit);
            exit(0);
    }
    if (wait(&ret) >= 0)
    {
            /* Parent process closes up output side of pipe */
            close(input_fd[0]);
            close(input_fd[1]);
    }
    free_array(commandSplit);
    pipe_trigger = 0;
    input_fd = NULL;
    return (cmd);
  }
  else
  {
    if((childpid = fork()) == -1)
    {
            perror("fork");
            exit(1);
    }
    if(childpid == 0)
    {
            /* Child process closes up input side of pipe */
            //if (pipe_trigger == 2)
            //{
              my_printf("CHILD DUPING: input[0],0\n");
              dup2(input_fd[0], 0);
            //}
            my_printf("CHILD avant dup : input[1],1\n");
            dup2(input_fd[1], 1);
            my_printf("CHILD apres dup : input[1],1\n");
            /* Send "string" through the output side of pipe */
            ret = bin_caller(commandSplit);
            my_printf("CHILD apres bin_caller\n");
            exit(0);
    }
    if (wait(&ret) >= 0)
    {
            /* Parent process closes up output side of pipe */
            //if (pipe_trigger == 2)
            //{
              my_printf("close input[0],0\n");
              //close(input_fd[0]);
            //}
            my_printf("PARENT avant close : input[1]\n");
            //close(input_fd[0]);
            close(input_fd[1]);
            my_printf("PARENT apres close : input[1]\n");
            return pipeline(cmd->next, input_fd);
    }
    free_array(commandSplit);
    pipe_trigger = 2;
    return pipeline(cmd->next, input_fd);
  }
  return (cmd);
}
