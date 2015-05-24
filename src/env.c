#include "headers/env.h"

#include <stdio.h> //@todo: remove this

static t_env_variable *g_env_variable = NULL;

bool              env_set_var(char *name, char *value)
{
  bool            is_error;
  bool            is_new;
  t_env_variable  *tmp;
  t_env_variable  *variable;

  is_error = false;
  variable = malloc(sizeof(*variable));
  if (variable == NULL)
  {
    is_error = true;
  }
  if (!is_error)
  {
    variable->name = name;
    variable->value = value;
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
        tmp = tmp->next;
      }
      if (is_new)
      {
        tmp->next = variable;
      }
    }
  }
  return (is_error);
}
void              env_unset_var(char *name)
{
  t_env_variable  *tmp;
  t_env_variable  *variable;

  tmp = g_env_variable;
  while (tmp != NULL)
  {
    if (my_strcmp(tmp->name, name) == 0)
    {
      variable = tmp;
      if (variable == g_env_variable) // first node deletion
      {
        g_env_variable = variable->next;
      }
      else
      {
        tmp--;
        tmp->next = variable->next;
      }
      free(variable);
      return;
    }
    tmp = tmp->next;
  }
}
t_env_variable    *env_get_list()
{
  return (g_env_variable);
}
t_env_variable    *env_get_var(char *name)
{
  t_env_variable  *tmp;
  t_env_variable  *variable;

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
