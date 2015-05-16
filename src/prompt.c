#include "../lib/my/src/headers/my.h"
#include "headers/parser.h"
#include "headers/prompt.h"

#include <stdio.h>

void          prompt_init()
{
  bool        is_running;
  char        *cmd;
  t_cmd_list  *cmd_list;

  is_running = true;
  while (is_running)
  {
    prompt_show();
    cmd = prompt_read_cmd();
    cmd_list = prompt_split_cmd(cmd);
    printf("addr cmd_list %p\n", cmd_list);
    // if (cmd != NULL && my_strlen(cmd) > 0)
    // {
    //   parser(cmd);
    // }
  }
}

void prompt_show()
{
  my_putstr(PROMPT_DEFAULT_STRING);
}

char *prompt_read_cmd()
{
  return my_readline(PROMPT_BUFFER_SIZE);
}

t_cmd_list *prompt_split_cmd(char *cmd)
{
  printf("%s\n", cmd);


  return (NULL);
}
