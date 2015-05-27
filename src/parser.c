#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/my/src/headers/my.h"
#include "headers/bin_caller.h"
#include "headers/path_handler.h"
#include "headers/env.h"
#include "headers/parser.h"

int parser(char* commandLine)
{
  //Minded : 'nohup' must only be found at the begining of commandLine
  int catch_error;
  char** commandSplit;
  char* cwd;
  char buff[128];

  cwd = NULL;
  //SPLIT USER COMMAND FOR EXECVE
  commandSplit = split_cmd(commandLine);
  //CHANGED Update my_strstr for my_strcmp
  //handle $PATH
  if (my_strstr(commandSplit[0], "path") != 0)
  {
    path_handler(commandSplit);
    free_array(commandSplit);
    return (0);
  }
  // CHANGE DIRECTORY
  else if (my_strcmp(commandSplit[0], "cd") == 0)
  {
      if (commandSplit[1] != NULL)
      {
        catch_error = chdir(commandSplit[1]);
      }
      else
      {
        catch_error = -1;
      }
      if (catch_error == -1)
      {
        perror(commandSplit[0]);
      }
      free_array(commandSplit);
      return (catch_error);
  }
  else if (my_strcmp(commandSplit[0], "pwd") == 0)
  {
    cwd = getcwd(buff, (sizeof(char) * 128));
    my_printf("%s\n", cwd);
    return (1);
  }
  // ENV VARIABLES SET
  else if (my_strcmp(commandSplit[0], "unsetenv") == 0)
  {
    if (commandSplit[1] != NULL)
    {
      env_unset_var(commandSplit[1]);
      return (1);
    }
    else
    {
      return (-1);
    }
  }
  // ENV VARIABLES SET
  else if (my_strcmp(commandSplit[0], "setenv") == 0)
  {
    if (commandSplit[1] != NULL) //&& commandSplit[2] != NULL)
    {
      env_set_var(commandSplit[1], commandSplit[2]);
      return (1);
    }
    else
    {
      return (-1);
    }
  }
  // ENV VARIABLES PRINT
  else if (my_strcmp(commandSplit[0], "env") == 0)
  {
    if (commandSplit[1] != NULL)
    {
      env_print_var(commandSplit[1]);
    }
    else
    {
      env_print_var(NULL);
    }
    return (1);
  }
  else
  {
    //EXECUTE BIN WITH SPLITED COMMAND
    bin_caller(commandSplit);
    //FREE MULTIDIM ARRAY
    free_array(commandSplit);
    return (1);
  }
}

char** split_cmd(char* commandLine)
{
  int i_one;
  int i_two;
  int i_three;
  int* array_count;
  int nb_args;
  char** commandSplit;
  int trigger_first_white_spaces;

  //COUNT NB_ARGS
  for (i_one = 1; commandLine[i_one] == ' '; i_one++);
  for (nb_args = 1; commandLine[i_one] != '\0'; i_one++)
  {
   if (commandLine[i_one] == ' ')
      if (commandLine[i_one + 1] != ' ' && commandLine[i_one + 1] != '\0')
        nb_args++;
  }
  //FIRST MALLOC WITH NB_ARGS
  commandSplit = malloc((nb_args + 1) * sizeof(char*));
  //CALL FUNCTION IN ORDER TO GET THE CHAR* SIZE OF DIFFERENT ARGS
  array_count = count_char(commandLine, nb_args);
  if (commandSplit == NULL)
    return (0);
  //MALLOC THE REST OF THE COMMANDSPLIT
  for (i_one = 0; i_one < nb_args; i_one++)
  {
    commandSplit[i_one] = malloc(sizeof(char) * array_count[i_one] + 1);
    if (commandSplit[i_one] == NULL)
      return (0);
  }
  //CHANGED ADDING trigger_first_white_spaces
  trigger_first_white_spaces = 0;
  //MASTER LOOP, EACH SUB ARRAY GET HIS STRING
  for (i_one = 0, i_two = 0, i_three = 0; commandLine[i_one] != '\0'; i_one++)
  {
    if (commandLine[i_one] != ' ')
    {
      commandSplit[i_two][i_three] = commandLine[i_one];
      //my_printf(" indicateur ===> commandLine[i_one] = %c split[%d][%d] = %c\n", commandLine[i_one], i_two, i_three, commandSplit[i_two][i_three]);
      i_three++;
      trigger_first_white_spaces = 1;
    }
    else if (commandLine[i_one] == ' ')
    {
      if (trigger_first_white_spaces == 1)
      {
        commandSplit[i_two][i_three] = '\0';
        i_two++;
        i_three = 0;
        trigger_first_white_spaces = 0;
      }
      for (; commandLine[i_one] == ' '; i_one++);
      i_one--;
    }
  }
  if (trigger_first_white_spaces == 1)
  {
    commandSplit[i_two][i_three] = '\0';
    //FUNCTION clean_space
    commandSplit[i_two + 1] = NULL;
  }
  else
  {
    commandSplit[i_two] = NULL;
  }
  free(array_count);
  return (commandSplit);
}
//CHANGED ADDING trigger_first_white_spaces
int* count_char(char* commandLine, int nb_args)
{
  int i;
  int counter;
  int* array_count;
  int trigger_first_white_spaces;

  array_count = malloc(nb_args * sizeof(int));
  trigger_first_white_spaces = 0;
  for (i = 0, counter = 1, nb_args = 0; commandLine[i] != '\0'; i++, counter++)
  {
    if (commandLine[i] == ' ')
    {
      for (; commandLine[i] == ' '; i++);
      i--;
      if (trigger_first_white_spaces == 1)
      {
        array_count[nb_args] = counter;
        counter = 0;
        nb_args++;
      }
      else
      {
        counter = 0;
      }
    }
    else if (commandLine[i + 1] == '\0')
    {
      array_count[nb_args] = counter + 1;
    }
    trigger_first_white_spaces = 1;
  }
  return (array_count);
}

void free_array(char** commandSplit)
{
  int i;

  for (i = 0; commandSplit[i] != NULL; i++)
  {
    free(commandSplit[i]);
  }
  free(commandSplit);
}
