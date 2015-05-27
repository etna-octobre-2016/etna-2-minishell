#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../lib/my/src/headers/my.h"
#include "headers/env.h"
#include "headers/path_handler.h"
#include "headers/parser.h"
#include "headers/bin_caller.h"

int    bin_caller(char *commandSplit[])
{
  int ret;
  int pid;
  char **env;
  char* bin_to_exec;

  env = env_get_array();
  if (my_strstr(commandSplit[0], "./") == 0)
  {
    if (commandSplit[0][0] == '/')
      bin_to_exec = commandSplit[0];
    else
      //SEARCH AND ADD PATH BEFORE EXEC BIN
      bin_to_exec = set_path_to_bin(commandSplit[0]);
  }
  else
    bin_to_exec = commandSplit[0];
  //FORK INIT
  pid = fork();
  //RETURN TEST OF FORK()
  if (pid == -1)
  {
    perror("forking");
    ret = -1;
  }
  if (pid == 0)
  {
    ret = execve(bin_to_exec, commandSplit, env);// CHILD
    perror(commandSplit[0]); // ONLY HAPPENS WHEN EXECVE FAIL ! // PARENT
    if (my_strlen(bin_to_exec) != my_strlen(commandSplit[0]))
      free(bin_to_exec);
    return (ret); // PARENT
  }
  if (wait(&ret) >= 0)
  {
    if (my_strlen(bin_to_exec) != my_strlen(commandSplit[0]))
      free(bin_to_exec);
  }
  return (ret);
}

char* set_path_to_bin(char* bin)
{
  s_path* entity;
  char* path_to_try;

  path_to_try = NULL;
  entity = s_initChain->first;
  //BROWSE LIST
  while (entity != NULL)
  {
    //FREE IF ALREADY CONCAT BY MY_STRCONCAT
    if (path_to_try != NULL)
    {
      free(path_to_try);
    }
    path_to_try = my_strconcat(entity->path, bin);
    // TRY ACCESS TO BIN
    if (access(path_to_try, F_OK) == 0)
    {
      return (path_to_try);
    }
    else
    {
      entity = entity->next;
    }
  }
  return (path_to_try);
}

char* she_banging(char* commandLine)
{
  int i_one;
  int i_two;
  int trigger;
  int arg_size;
  char* bin_name;
  char* bin_name_cleaned;

  //REPARSE COMMANDSPLIT
  for (arg_size = 0, trigger = 0, i_one = 2, i_two = 0; trigger == 0; i_one++, arg_size++)
  {
    if (commandLine[i_one] == ' ' || commandLine[i_one] == '\0')
      trigger = 1;
  }
  bin_name = malloc(sizeof(char) * arg_size);
  //ELIMINATE "./"
  for (trigger = 0, i_one = 2, i_two = 0; trigger == 0; i_one++, i_two++)
  {
    if (commandLine[i_one] == ' ' || commandLine[i_one] == '\0')
      trigger = 1;
    bin_name[i_two] = commandLine[i_one];
  }
  bin_name_cleaned = get_bin(bin_name, 0);
  if (bin_name_cleaned == NULL)
    return (NULL);
  //REWRITE COMMANDLINE
  commandLine = rewrite_command(commandLine, bin_name_cleaned);
  free(bin_name);
  return (commandLine);
}

char* get_bin(char* bin_name, int opt)
{
  int file;
  int i_one;
  int trigger;
  char* buffer;
  char* bin_name_cleaned;

  file = open(bin_name, O_RDONLY | O_NONBLOCK);
  if (file == -1)
    return (NULL);
  buffer = malloc(sizeof(char));
  if (opt != 0)
    bin_name_cleaned = malloc(sizeof(char) * (opt + 1));
  read(file, buffer, 1);
  trigger = 0;
  while (buffer[0] != '\n')
  {
    if (buffer[0] == '/')
    {
      trigger = 1;
      i_one = 0;
    }
    else if (trigger == 1)
    {
      if (opt == 0)
        i_one++;
      else if (buffer[0] != '\n')
      {
        bin_name_cleaned[i_one] = buffer[0];
        i_one++;
      }
    }
    free(buffer);
    buffer = malloc(sizeof(char));
    read(file, buffer, 1);
  }
  free(buffer);
  close(file);
  if (opt == 0)
    return (get_bin(bin_name, i_one));
  else
  {
    bin_name_cleaned[i_one] = '\0';
    return (bin_name_cleaned);
  }
}

char* rewrite_command(char* commandLine, char* bin_name_cleaned)
{
  int i_one;
  int i_two;
  int len_total;
  int len_bin;
  int len_bin_cleaned;
  char* new_commandLine;

  len_total = my_strlen(commandLine);
  len_bin = my_strlen("./");
  len_bin_cleaned = my_strlen(bin_name_cleaned);
  //CALCULATING NEW COMMANDLINE SIZE FOR MALLOC
  len_total = (len_total - (len_bin - len_bin_cleaned)) + 2;
  //MALLOC SIZE OF LEN_TOTAL
  new_commandLine = malloc(sizeof(char) * len_total);
  //BEGIN LOOP CREATION NEW COMMANDLINE
    //FIRST ADDIND BIN NAME CLEANED
  for (i_one = 0, i_two = 0; bin_name_cleaned[i_two] != '\0'; i_one++, i_two++)
    new_commandLine[i_one] = bin_name_cleaned[i_two];
  new_commandLine[i_one] = ' ';
    //ADDING THE REST OF ARG
  for (i_one += 1, i_two = 2; commandLine[i_two] != '\0'; i_one++, i_two++)
    new_commandLine[i_one] = commandLine[i_two];
  new_commandLine[i_one] = '\0';
  return (new_commandLine);
}
