#include <stdlib.h>
#include "headers/parser.h"
#include "headers/bin_caller.h"
#include "../lib/my/src/headers/my.h"

int parser(char* commandLine)
{
  //Minded : 'nohup' must only be found at the begining of commandLine
  int i;
  //int catch_error;
  char specials_char[] = SPECIALS_CHAR;
  char** commandSplit;

  for(i = 0; specials_char[i] != '0'; i++)
  {
    if (my_strchar(specials_char[i], commandLine) == 0)
      {
        my_printf("Argument found : %c\n", specials_char[i]);
        return (0);
      }
  }
  //SPLIT USER COMMAND FOR EXECVE
  commandSplit = split_cmd(commandLine);
  //EXECUTE BIN WITH SPLITED COMMAND
  bin_caller(commandSplit);
  //FREE MULTIDIM ARRAY
  free_array(commandSplit);
  //catch_error = bin_caller(commandSplit);
  return (1);
}

char** split_cmd(char* commandLine)
{
  int i_one;
  int i_two;
  int i_three;
  int* array_count;
  int nb_args;
  char** commandSplit;

  //COUNT NB_ARGS
  for (i_one = 0, nb_args = 1; commandLine[i_one] != '\0'; i_one++)
    if (commandLine[i_one] == ' ')
      nb_args++;
  //FIRST MALLOC WITH NB_ARGS
  commandSplit = malloc(nb_args * sizeof(char*));
  //CALL FUNCTION IN ORDER TO GET THE CHAR* SIZE OF DIFFERENT ARGS
  array_count = count_char(commandLine, nb_args);
  if (commandSplit == NULL)
    return (0);
  //MALLOC THE REST OF THE COMMANDSPLIT
  for (i_one = 0; i_one < nb_args; i_one++)
  {
    commandSplit[i_one] = malloc(sizeof(char) * array_count[i_one]);
    if (commandSplit[i_one] == NULL)
      return (0);
  }
  //MASTER LOOP, EACH SUB ARRAY GET HIS STRING
  for (i_one = 0, i_two = 0, i_three = 0; commandLine[i_one] != '\0'; i_one++)
  {
    if (commandLine[i_one] != ' ')
    {
      commandSplit[i_two][i_three] = commandLine[i_one];
      i_three++;
    }
    else
    {
      commandSplit[i_two][i_three] = '\0';
      i_two++;
      i_three = 0;
    }
    commandSplit[i_two][i_three] = '\0';
  }
  return (commandSplit);
}

int* count_char(char* commandLine, int nb_args)
{
  int i;
  int counter;
  int* array_count;

  array_count = malloc(nb_args * sizeof(int));
  for (i = 0, counter = 0, nb_args = 0; commandLine[i] != '\0'; i++, counter++)
  {
        if (commandLine[i] == ' ' || commandLine[i + 1] == '\0')
        {
          array_count[nb_args] = counter + 1;
          counter = 0;
          nb_args++;
        }
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
