#include <stdio.h>
#include <unistd.h>
#include "../lib/my/src/headers/my.h"
#include "headers/env.h"
#include "headers/path_handler.h"
#include "headers/builtins.h"
#include "headers/error_handler.h"

int         builtin_cd(char **commandSplit)
{
  int       ret;

  ret = BUILTIN_SUCCESS;
  if (commandSplit[1] == NULL || chdir(commandSplit[1]) == -1)
  {
    ret = BUILTIN_ERROR;
  }
  if (ret == BUILTIN_ERROR)
  {
    error_handler(commandSplit[0]);
  }
  return (ret);
}

int         builtin_env(char **commandSplit)
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

int         builtin_exit(char **commandSplit)
{
  UNUSED(commandSplit);
  return (BUILTIN_EXIT);
}

int         builtin_handle(char **commandSplit)
{
  int       i;
  int       ret;
  t_builtin builtins[] = {
    {"add_path", builtin_path_add},
    {"cd", builtin_cd},
    {"del_path", builtin_path_del},
    {"env", builtin_env},
    {"exit", builtin_exit},
    {"path", builtin_path},
    {"pwd", builtin_pwd},
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

int         builtin_path(char **commandSplit)
{
  int       i;
  int       ret;

  ret = BUILTIN_SUCCESS;
  for (i = 0; commandSplit[i] != NULL; i++)
  {
    if (my_strcmp(commandSplit[i], "--help") == 0)
    {
      show_path_helper();
      return (ret);
    }
  }
  if (show_path() != 0)
  {
    ret = BUILTIN_ERROR;
  }
  return (ret);
}

int         builtin_path_add(char **commandSplit)
{
  int       ret;

  ret = BUILTIN_SUCCESS;
  if (commandSplit[1] == NULL || add_path(commandSplit[1]) != 0)
  {
    ret = BUILTIN_ERROR;
  }
  return (ret);
}

int         builtin_path_del(char **commandSplit)
{
  int       ret;

  ret = BUILTIN_SUCCESS;
  if (commandSplit[1] == NULL || del_path(commandSplit[1]) != 0)
  {
    ret = BUILTIN_ERROR;
  }
  return (ret);
}

int         builtin_pwd(char **commandSplit)
{
  char      buff[128];
  char*     cwd;
  int       ret;

  UNUSED(commandSplit);
  ret = BUILTIN_SUCCESS;
  cwd = getcwd(buff, (sizeof(char) * 128));
  if (cwd != NULL)
  {
    my_printf("%s\n", cwd);
  }
  else
  {
    ret = BUILTIN_ERROR;
    error_handler("pwd");
  }
  return (ret);
}

int         builtin_setenv(char **commandSplit)
{
  if (commandSplit[1] != NULL && commandSplit[2] != NULL)
  {
    env_set_var(commandSplit[1], commandSplit[2]);
    return (BUILTIN_SUCCESS);
  }
  return (BUILTIN_ERROR);
}

int         builtin_unsetenv(char **commandSplit)
{
  if (commandSplit[1] != NULL)
  {
    env_unset_var(commandSplit[1]);
    return (BUILTIN_SUCCESS);
  }
  return (BUILTIN_ERROR);
}
