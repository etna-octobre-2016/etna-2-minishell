#include "headers/prompt.h"
#include "headers/pipeline.h"

#include <stdio.h>

t_cmd_list *pipeline(t_cmd_list *cmd, int input_fd)
{
  // last command
  if (!cmd->is_piped)
  {
    printf("last cmd in pipeline = %s\n", cmd->cmd);
    return (cmd);
  }
  else
  {
    printf("pipelined cmd = %s\n", cmd->cmd);
    return pipeline(cmd->next, input_fd);
  }
}
