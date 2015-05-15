#include <stdbool.h>
#include "../lib/my/src/headers/my.h"
#include "headers/parser.h"
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
    if (cmd != NULL && my_strlen(cmd) > 0)
    {
      parser(cmd);
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
