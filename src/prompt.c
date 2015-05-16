#include <stdlib.h>
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

    // prompt_free_cmd_list(cmd_list);
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

t_cmd_list        *prompt_split_cmd(char *cmd)
{
  t_cmd_list      *cmd_list;
  t_symbol_match  *first_special_symbol;

  cmd = cmd; //@note: remove this later

  cmd_list = malloc(sizeof(cmd_list));
  if (cmd_list != NULL)
  {
    first_special_symbol = prompt_find_first_special_symbol(cmd);
    if (first_special_symbol == NULL)
    {
      return (NULL);
    }
    printf("symb.string = %s\n", first_special_symbol->string);
    printf("symb.position = %d\n", first_special_symbol->position);
  }
  return (cmd_list);
}

t_symbol_match    *prompt_find_first_special_symbol(char *cmd)
{
  char            *special_symbols[] = PROMPT_SPECIAL_SYMBOLS;
  int             current_position;
  int             i;
  t_symbol_match  *symbol;

  symbol = malloc(sizeof(symbol));
  if (symbol == NULL)
  {
    return (NULL);
  }
  // @note: setting default values
  symbol->position = -1;
  symbol->string = NULL;
  current_position = -1;
  for (i = 0; special_symbols[i] != NULL; i++)
  {
    current_position = my_strpos(cmd, special_symbols[i]);
    if (current_position > -1 && (symbol->position == -1 || current_position < symbol->position))
    {
      symbol->position = current_position;
      symbol->string = special_symbols[i];
    }
  }
  return (symbol);
}
