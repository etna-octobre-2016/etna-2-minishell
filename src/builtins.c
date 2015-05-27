#include "headers/builtins.h"

#include <stdio.h> // @todo: remove

int   builtin_cd(char **commandSplit)
{
  int ret;

  ret = 0;
  printf("builtin = cd, cmd = %s\n", commandSplit[0]);
  return (ret);
}
int   builtin_env(char **commandSplit)
{
  int ret;

  ret = 0;
  printf("builtin = env, cmd = %s\n", commandSplit[0]);
  return (ret);
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
  int ret;

  ret = 0;
  printf("builtin = setenv, cmd = %s\n", commandSplit[0]);
  return (ret);
}
int   builtin_unsetenv(char **commandSplit)
{
  int ret;

  ret = 0;
  printf("builtin = unsetenv, cmd = %s\n", commandSplit[0]);
  return (ret);
}
