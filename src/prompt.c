#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/my/src/headers/my.h"
#include "headers/builtins.h"
#include "headers/parser.h"
#include "headers/pipeline.h"
#include "headers/redirections.h"
#include "headers/prompt.h"

bool              prompt_init()
{
  bool            is_running;
  bool            is_success;
  char*           cmd;
  int             parser_ret;
  t_cmd_list*     cmd_current;
  t_cmd_list*     cmd_list;

  is_running = true;
  is_success = true;
  parser_ret = 0;
  while (is_running)
  {
    prompt_show();
    cmd = prompt_cmd_read();
    if (cmd == NULL)
    {
      is_success = false;
      break;
    }
    if (my_strlen(cmd) > 0)
    {
      cmd_list = prompt_cmd_split(cmd);
      if (cmd_list == NULL)
      {
        is_success = false;
        break;
      }
      cmd_current = cmd_list;
      while(cmd_current != NULL)
      {
        if (cmd_current->is_piped)
        {
          cmd_current = pipeline(cmd_current, -1);
        }
        else if ((cmd_current->is_redirect_input) || (cmd_current->is_redirect_output))
        {
          cmd_current = redirections(cmd_current);
        }
        else
        {
          parser_ret = parser(cmd_current->cmd);
        }
        cmd_current = cmd_current->next;
      }
    }
    if (parser_ret == BUILTIN_EXIT)
    {
      is_running = false;
    }
    free(cmd);
    prompt_cmd_split_free(cmd_list);
  }
  return (is_success);
}

char*             prompt_cmd_read()
{
  return my_readline(PROMPT_BUFFER_SIZE);
}

t_cmd_list*       prompt_cmd_list_add_item(t_cmd_list *list, t_cmd_list *new_item)
{
  t_cmd_list*     tmp;

  // if the new_item is the first of the list
  if (list == NULL)
  {
    new_item->next = NULL;
    new_item->prev = NULL;
    list = new_item;
  }
  else
  {
    tmp = list;
    while (tmp->next != NULL)
    {
      tmp = tmp->next;
    }
    new_item->prev = tmp;
    new_item->next = NULL;
    tmp->next = new_item;
  }
  return (list);
}

t_cmd_list*       prompt_cmd_split(char *cmd)
{
  bool            is_split_complete;
  char*           tmp;
  t_cmd_list*     cmd_list;
  t_cmd_list*     cmd_list_item;
  t_symbol_match* first_special_symbol;

  tmp = cmd;
  cmd_list = NULL;
  is_split_complete = false;
  while (!is_split_complete)
  {
    first_special_symbol = prompt_cmd_find_first_symbol(tmp);
    cmd_list_item = malloc(sizeof(*cmd_list_item));
    if (first_special_symbol == NULL || cmd_list_item == NULL)
    {
      return (NULL);
    }
    if (first_special_symbol->position == -1)
    {
      is_split_complete = true;
      cmd_list_item->cmd = tmp;
    }
    else
    {
      cmd_list_item->cmd = malloc(sizeof(char) * (first_special_symbol->position + 1));
      if (cmd_list_item->cmd == NULL)
      {
        return (NULL);
      }
      my_strncpy(cmd_list_item->cmd, tmp, (first_special_symbol->position));
      tmp = (tmp + first_special_symbol->position + my_strlen(first_special_symbol->string));
    }
    cmd_list = prompt_cmd_list_add_item(cmd_list, cmd_list_item);
    prompt_cmd_set_flags(cmd_list_item, first_special_symbol);
  }
  return (cmd_list);
}

t_symbol_match*   prompt_cmd_find_first_symbol(char *cmd)
{
  char*           special_symbols[] = PROMPT_SPECIAL_SYMBOLS;
  int             current_position;
  int             i;
  t_symbol_match* symbol;

  symbol = malloc(sizeof(*symbol));
  if (symbol == NULL)
  {
    return (NULL);
  }
  // @note: setting default values
  symbol->is_pipe = false;
  symbol->is_redirect_input = false;
  symbol->is_redirect_output = false;
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
  // Symbol recognition
  if (symbol->string != NULL)
  {
    if (my_strcmp(symbol->string, "|") == 0)
    {
      symbol->is_pipe = true;
    }
    if (my_strcmp(symbol->string, "<") == 0)
    {
      symbol->is_redirect_input = true;
    }
    if (my_strcmp(symbol->string, ">") == 0)
    {
      symbol->is_redirect_output = true;
    }
  }
  return (symbol);
}

void              prompt_cmd_set_flags(t_cmd_list *cmd, t_symbol_match *symbol)
{
  cmd->is_piped = symbol->is_pipe;
  cmd->is_redirect_input = symbol->is_redirect_input;
  cmd->is_redirect_output = symbol->is_redirect_output;
}

void              prompt_cmd_split_free(t_cmd_list* cmd_list)
{
  t_cmd_list*     cmd;
  t_cmd_list*     tmp;

  cmd = cmd_list;
  while (cmd != NULL)
  {
    tmp = cmd;
    cmd = cmd->next;
    free(tmp->cmd);
    free(tmp);
  }
}

void              prompt_show()
{
  my_putstr(PROMPT_DEFAULT_STRING);
}
