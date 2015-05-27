#include "headers/builtins.h"

#include <stdio.h> // @todo: remove

int   builtin_cd(char **commandSplit)
{
  int ret;

  ret = BUILTIN_SUCCESS;
  if (commandSplit[1] != NULL || chdir(commandSplit[1]) == -1)
  {
    ret = BUILTIN_ERROR;
  }
  if (ret == BUILTIN_ERROR)
  {
    perror(commandSplit[0]);
  }
  return (ret);
}
int   builtin_env(char **commandSplit)
{
  if (commandSplit[1] != NULL)
  {
    env_print_var(commandSplit[1]);
  }
  else
  {
    env_print_var(NULL);
  }
  return (BUILTIN_SUCCESS);
}
int         builtin_handle(char **commandSplit)
{
  int       i;
  int       ret;
  t_builtin builtins[] = {
    {"cd", builtin_cd},
    {"env", builtin_env},
    {"path", builtin_path},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {NULL,NULL}
  };

  ret = BUILTIN_UNKNOWN;
  for (i = 0; builtins[i].name != NULL; i++)
  {
    if (my_strcmp(builtins[i].name, commandSplit[0]) == 0)
    {
      ret = builtins[i].func(commandSplit);
      break;
    }
  }
  return (ret);
}
int   builtin_path(char **commandSplit)
{
  int ret;

  ret = 0;
  printf("builtin = path, cmd = %s\n", commandSplit[0]);
  return (ret);
}
int   builtin_setenv(char **commandSplit)
{
  if (commandSplit[1] != NULL && commandSplit[2] != NULL)
  {
    env_set_var(commandSplit[1], commandSplit[2]);
    return (BUILTIN_SUCCESS);
  }
  return (BUILTIN_ERROR);
}
int   builtin_unsetenv(char **commandSplit)
{
  if (commandSplit[1] != NULL)
  {
    env_unset_var(commandSplit[1]);
    return (BUILTIN_SUCCESS);
  }
  return (BUILTIN_ERROR);
}
