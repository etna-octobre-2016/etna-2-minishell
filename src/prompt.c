#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "headers/string.h"
#include "headers/prompt.h"

void    prompt_init()
{
  bool  is_running;

  is_running = true;
  while (is_running)
  {
    prompt_read_cmd();
    // prompt_show();
  }
}

void prompt_read_cmd()
{
  char cmd_str[PROMPT_BUFFER_SIZE];

  read(STDIN_FILENO, cmd_str, PROMPT_BUFFER_SIZE);
  printf("cmd = %s\n", cmd_str);
}

void prompt_show()
{
  write(STDOUT_FILENO, PROMPT_DEFAULT_STRING, strlen(PROMPT_DEFAULT_STRING));
}
