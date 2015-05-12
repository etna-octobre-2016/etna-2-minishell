#include <stdbool.h>
#include "../lib/my/src/headers/my.h"
#include "headers/prompt.h"

#include <stdio.h>

void    prompt_init()
{
  bool  is_running;

  is_running = true;
  while (is_running)
  {
    prompt_read_cmd();
  }
}

void prompt_read_cmd()
{
  // @note: add implementation
}

void prompt_show()
{
  // @note: add implementation
}
