#include <stdbool.h>
#include "../lib/my/src/headers/my.h"
#include "headers/prompt.h"

void    prompt_init()
{
  bool  is_running;
  char  *cmd;

  is_running = true;
  while (is_running)
  {
    prompt_show();
    cmd = prompt_read_cmd();
    if (cmd != NULL)
    {
      my_putstr("dans le IF\n");
      my_printf("cmd = %s\n", cmd);
    }
    else
    {
      my_putstr("dans le ELSE\n");
      my_printf("cmd = %s\n", cmd);
    }
  }
}

void prompt_show()
{
  my_printf("%s", PROMPT_DEFAULT_STRING);
}

char *prompt_read_cmd()
{
  return my_readline(PROMPT_BUFFER_SIZE);
}
