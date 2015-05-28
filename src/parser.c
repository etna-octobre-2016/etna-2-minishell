#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lib/my/src/headers/my.h"
#include "headers/bin_caller.h"
#include "headers/path_handler.h"
#include "headers/env.h"
#include "headers/parser.h"
#include "headers/builtins.h"

char**      split_cmd(char* commandLine)
{
  int       i_one;
  int       i_two;
  int       i_three;
  int*      array_count;
  int       nb_args;
  char**    commandSplit;
  int       trigger_first_white_spaces;

  //COUNT NB_ARGS
  for (i_one = 1; commandLine[i_one] == ' '; i_one++);
  for (nb_args = 1; commandLine[i_one] != '\0'; i_one++)
  {
    if (commandLine[i_one] == ' ')
    {
      if (commandLine[i_one + 1] != ' ' && commandLine[i_one + 1] != '\0')
      {
        nb_args++;
      }
    }
  }
  commandSplit = malloc((nb_args + 1) * sizeof(char*)); //FIRST MALLOC WITH NB_ARGS
  array_count = count_char(commandLine, nb_args); //CALL FUNCTION IN ORDER TO GET THE CHAR* SIZE OF DIFFERENT ARGS
  if (commandSplit == NULL)
  {
    return (0);
  }
  for (i_one = 0; i_one < nb_args; i_one++) //MALLOC THE REST OF THE COMMANDSPLIT
  {
    commandSplit[i_one] = malloc(sizeof(char) * array_count[i_one] + 1);
    if (commandSplit[i_one] == NULL)
    {
      return (0);
    }
  }
  trigger_first_white_spaces = 0; //CHANGED ADDING trigger_first_white_spaces
  for (i_one = 0, i_two = 0, i_three = 0; commandLine[i_one] != '\0'; i_one++) //MASTER LOOP, EACH SUB ARRAY GET HIS STRING
  {
    if (commandLine[i_one] != ' ')
    {
      commandSplit[i_two][i_three] = commandLine[i_one];
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

int         parser(char* commandLine)
{
  //Minded : 'nohup' must only be found at the begining of commandLine
  char**    commandSplit;
  int       builtin_ret;

  commandSplit = split_cmd(commandLine); //SPLIT USER COMMAND FOR EXECVE
  builtin_ret = builtin_handle(commandSplit);
  if (builtin_ret == BUILTIN_UNKNOWN)
  {
    bin_caller(commandSplit); //EXECUTE BIN WITH SPLITED COMMAND
  }
  free_array(commandSplit); //FREE MULTIDIM ARRAY
  return (builtin_ret);
}

int*        count_char(char* commandLine, int nb_args) //CHANGED ADDING trigger_first_white_spaces
{
  int       counter;
  int       i;
  int       trigger_first_white_spaces;
  int*      array_count;

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

void        free_array(char** commandSplit)
{
  int       i;

  for (i = 0; commandSplit[i] != NULL; i++)
  {
    free(commandSplit[i]);
  }
  free(commandSplit);
}
