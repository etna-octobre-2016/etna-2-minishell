#include "../lib/my/src/headers/my.h"
#include "headers/prompt.h"
#include "headers/parser.h"
#include "headers/bin_caller.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

t_cmd_list* redirections(t_cmd_list* cmd)
{
  char** commandSplit;
  char** commandSplit_Buffer;
  int input;
  int output;
  int ret;
  t_cmd_list* buffer;

  buffer = NULL;
  input = -1;
  output = -1;
  if (cmd->is_redirect_input)
  {
    if (cmd->next != NULL)
      buffer = cmd->next;
    else
      return (cmd);
    commandSplit_Buffer = split_cmd(buffer->cmd);
    //IS FILE ACCESSIBLE ?
    if (access(commandSplit_Buffer[0], F_OK) == 0)
    {
      //FILE HANDLE
      input = open(commandSplit_Buffer[0], O_RDONLY | O_NONBLOCK);
      if (input == -1)
      {
        my_printf("File unreachable.\n");
        return (cmd->next);
      }
      commandSplit = split_cmd(cmd->cmd);
      if (fork() == 0)
      { /* child */
        dup2(input, STDIN_FILENO);
        close(input);
        ret = 0;
        ret = bin_caller(commandSplit);
        free_array(commandSplit);
        exit(1);
      }
      if (wait(&ret) >= 0)
      { /* parent */
          close(input);
          free_array(commandSplit);
          free_array(commandSplit_Buffer);
      }
    }
    else
    {
      my_printf("File unreachable.\n");
    }
  }
  else if (cmd->is_redirect_output)
  {
    if (cmd->next != NULL)
      buffer = cmd->next;
    else
      return (cmd);
    commandSplit_Buffer = split_cmd(buffer->cmd);
    //FILE HANDLE
    output = open(commandSplit_Buffer[0], O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    if (output == -1)
    {
      my_printf("Cannot create/open the file unreachable.\n");
      return (cmd->next);
    }
    commandSplit = split_cmd(cmd->cmd);
    if (fork() == 0)
    { /* child */
      dup2(output, 1);
      close(output);
      ret = 0;
      ret = bin_caller(commandSplit);
      free_array(commandSplit);
      free_array(commandSplit_Buffer);
      exit(1);
    }
    if (wait(&ret) >= 0)
    { /* parent */
        close(output);
        free_array(commandSplit);
        free_array(commandSplit_Buffer);
    }
  }
  return (cmd->next);
}
