#include "../lib/my/src/headers/my.h"
#include "headers/prompt.h"
#include "headers/pipeline.h"

t_cmd_list *pipeline(t_cmd_list *cmd, int input_fd)
{
  // last command
  if (!cmd->is_piped)
  {
    my_printf("last cmd in pipeline = %s\n", cmd->cmd);
    return (cmd);
  }
  else
  {
    my_printf("pipelined cmd = %s\n", cmd->cmd);
    return pipeline(cmd->next, input_fd);
  }
}
