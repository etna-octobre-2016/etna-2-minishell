#include <stdlib.h>
#include "../lib/my/src/headers/my.h"
#include "headers/env.h"

static t_env_variable *g_env_variable = NULL;

bool              env_set_var(char *name, char *value)
{
  bool            is_error;
  bool            is_new;
  t_env_variable* last;
  t_env_variable* tmp;
  t_env_variable* variable;

  is_error = false;
  variable = malloc(sizeof(*variable));
  if (variable == NULL)
  {
    is_error = true;
  }
  if (!is_error)
  {
    variable->name = my_strcpy(name);
    variable->value = my_strcpy(value);
    variable->next = NULL;
    if (g_env_variable == NULL)
    {
      g_env_variable = variable;
    }
    else
    {
      tmp = g_env_variable;
      is_new = true;
      while (tmp != NULL)
      {
        if (my_strcmp(tmp->name, name) == 0)
        {
          is_new = false;
          tmp->value = value;
          free(variable);
          break;
        }
        if (tmp->next == NULL)
        {
          last = tmp;
        }
        tmp = tmp->next;
      }
      if (is_new)
      {
        last->next = variable;
      }
    }
  }
  return (is_error);
}

char**            env_get_array()
{
  char**          array;
  int             i;
  t_env_variable* variable;

  array = malloc(sizeof(*array));
  if (array == NULL)
  {
    return (NULL);
  }
  i = 1;
  variable = g_env_variable;
  while (variable != NULL)
  {
    array[(i - 1)] = my_strconcat(variable->name, "=");
    array[(i - 1)] = my_strconcat(array[(i - 1)], variable->value);
    i++;
    array = realloc(array, (i * sizeof(*array)));
    if (array == NULL)
    {
      return (NULL);
    }
    variable = variable->next;
  }
  array[(i - 1)] = NULL;
  return (array);
}

t_env_variable*   env_get_list()
{
  return (g_env_variable);
}

t_env_variable*   env_get_var(char *name)
{
  t_env_variable* tmp;
  t_env_variable* variable;

  tmp = g_env_variable;
  variable = NULL;
  while (tmp != NULL)
  {
    if (my_strcmp(tmp->name, name) == 0)
    {
      variable = tmp;
      break;
    }
    tmp = tmp->next;
  }
  return (variable);
}

void              env_free_list()
{
  t_env_variable* node;
  t_env_variable* tmp;

  node = g_env_variable;
  while (node != NULL)
  {
    tmp = node;
    node = node->next;
    free(tmp);
  }
  g_env_variable = NULL;
}

void              env_print_var(char *name)
{
  t_env_variable* tmp;
  t_env_variable* variable;

  tmp = g_env_variable;
  variable = NULL;
  while (tmp != NULL)
  {
    if (name != NULL)
    {
      if (my_strcmp(tmp->name, name) == 0)
      {
        variable = tmp;
        break;
      }
    }
    else
    {
      my_printf("%s=%s\n", tmp->name, tmp->value);
    }
    tmp = tmp->next;
  }
  if (name != NULL)
  {
    if (variable != NULL)
    {
      my_printf("%s: %s\n", variable->name, variable->value);
    }
    else
    {
      my_printf("error: '%s' environment variable not found\n", name);
    }
  }
}

void              env_unset_var(char *name)
{
  t_env_variable* prev;
  t_env_variable* variable;

  variable = g_env_variable;
  while (variable != NULL)
  {
    if (my_strcmp(variable->name, name) == 0)
    {
      if (variable == g_env_variable)
      {
        g_env_variable = variable->next;
      }
      else
      {
        prev->next = variable->next;
      }
      free(variable);
      return;
    }
    else
    {
      prev = variable;
      variable = variable->next;
    }
  }
}
