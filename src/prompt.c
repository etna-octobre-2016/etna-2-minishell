#include <stdlib.h>
#include <signal.h>
#include "../lib/my/src/headers/my.h"
#include "headers/parser.h"
#include "headers/prompt.h"

#include <stdio.h>

void              prompt_cmd_list_add_item(t_cmd_list *list, t_cmd_list *new_item)
{
  t_cmd_list      *tmp;

  if (list->cmd == NULL)
  {
    list->cmd = new_item->cmd;
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
}

bool              prompt_init()
{
  bool            is_success;
  char            *cmd;
  t_cmd_list      *cmd_current;
  t_cmd_list      *cmd_list;

  is_success = true;
  while (1)
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
        printf("cmd_current->cmd = %s\n", cmd_current->cmd);
        cmd_current = cmd_current->next;
      }
    }
  }
  return (is_success);
}

void              prompt_show()
{
  my_putstr(PROMPT_DEFAULT_STRING);
}

char              *prompt_cmd_read()
{
  return my_readline(PROMPT_BUFFER_SIZE);
}

t_cmd_list        *prompt_cmd_list_init()
{
  t_cmd_list      *cmd_list;

  cmd_list = malloc(sizeof(cmd_list));
  if (cmd_list != NULL)
  {
    cmd_list->cmd = NULL;
    cmd_list->prev = NULL;
    cmd_list->next = NULL;
  }
  return (cmd_list);
}

t_cmd_list        *prompt_cmd_split(char *cmd)
{
  bool            is_split_complete;
  char            *tmp;
  t_cmd_list      *cmd_list;
  t_cmd_list      *cmd_list_item;
  t_symbol_match  *first_special_symbol;

  cmd_list = prompt_cmd_list_init();
  if (cmd_list == NULL)
  {
    return (NULL);
  }
  tmp = cmd;
  is_split_complete = false;
  while (!is_split_complete)
  {
    first_special_symbol = prompt_cmd_find_first_symbol(tmp);
    cmd_list_item = malloc(sizeof(cmd_list_item));
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
      my_strncpy(cmd_list_item->cmd, tmp, first_special_symbol->position);
      prompt_cmd_list_add_item(cmd_list, cmd_list_item);
      cmd_list_item = malloc(sizeof(cmd_list_item));
      if (cmd_list_item == NULL)
      {
        return (NULL);
      }
      cmd_list_item->cmd = first_special_symbol->string;
      tmp = (tmp + first_special_symbol->position + my_strlen(first_special_symbol->string));
    }
    prompt_cmd_list_add_item(cmd_list, cmd_list_item);
  }
  return (cmd_list);
}

t_symbol_match    *prompt_cmd_find_first_symbol(char *cmd)
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
