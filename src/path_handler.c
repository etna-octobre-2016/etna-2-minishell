#include "headers/path_handler.h"
#include "../lib/my/src/headers/my.h"
#include <stdlib.h>
#include <dirent.h>

void path_handler(char** commandSplit)
{
  t_listFunc tabFunc[] =
    {
      {"add_path", add_path},
      {"del_path", del_path},
      {"path", show_path},
      {0,0}
    };
  int i;

  //MASTER LOOP CALL FUNCTION
  for (i = 0; tabFunc[i].action != 0; i++)
  {
    if (my_strcmp(commandSplit[0], tabFunc[i].action) == 0)
	    {
	       tabFunc[i].ptr(commandSplit[1]);
	    }
  }
}

void path_handler_init()
{
  s_path* entity;

  s_initChain = malloc(sizeof(s_listChain));
  entity  = malloc(sizeof(s_path));
  if ((s_initChain == NULL) || (entity == NULL))
    exit(1);
  entity->path = ENV_ARG_PATH;
  entity->next = NULL;
  s_initChain->first = entity;
}

int add_path(char* path)
{
  s_path* entity;
  char* char_buffer;

  if (path == NULL)
  {
    my_printf("You must enter a value after add_path.\n Example : add_path /usr/bin/\n");
    return (-1);
  }
  else if (search_chain(path) != NULL)
  {
    my_printf("path: %s already exists\n", path);
    return (-1);
  }
  if ((char_buffer = cleaner_path(path)) != NULL)
  {
    entity = malloc(sizeof(s_path));
    if (entity == NULL)
      return(-1);
    entity->path = char_buffer;
    entity->next = s_initChain->first;
    s_initChain->first = entity;
    my_printf("$PATH Updated with %s.\n", entity->path);
    return (0);
  }
  return (-1);
}

int del_path(char* path)
{
  s_path* entity;
  s_path* buffEntity;
  int trigger;

  trigger = 0;
  entity = s_initChain->first;
  while (entity != NULL)
  {
    if (my_strcmp(entity->path, path) == 0)
    {
      if (trigger == 0)
      {
        s_initChain->first = entity->next;
        my_printf("%s removed from $PATH.\n", entity->path);
        free(entity);
        return (0);
      }
      else
      {
        buffEntity->next = entity->next;
        my_printf("%s removed from $PATH.\n", entity->path);
        free(entity);
        return (0);
      }
    }
    trigger = 1;
    buffEntity = entity;
    entity = entity->next;
  }
  my_printf("%s not found on $PATH.\n", path);
  return (0);
}

int free_chain_path(s_listChain* list)
{
  s_path* entity;

  while (list->first != NULL)
    {
      entity = list->first;
      list->first = entity->next;
      free(entity);
    }
  free(list);
  return (0);
}

int show_path()
{
  s_path* entity;

  entity = s_initChain->first;
  my_printf("$PATH=================\n");
  while (entity != NULL)
    {
      my_printf("%s\n", entity->path);
      entity = entity->next;
    }
    my_printf("=====================>\n");
    return (0);
}

s_path* search_chain(char* valueToSearch)
{
  s_path* searchEntity;

  searchEntity = s_initChain->first;
  while (searchEntity != NULL)
    {
      if (my_strcmp(searchEntity->path, valueToSearch) == 0)
	return (searchEntity);
      else
	searchEntity = searchEntity->next;
    }
  return (NULL);
}

char* cleaner_path(char* path_to_clean)
{
  int i;
  int counter;
  int trigger;
  char* cleaned_path;

  if (opendir(path_to_clean) != NULL)
  {
    //ANALYSE '/' FOR DELETING TWINS
    for (i = 0, counter = 0, trigger = 0; path_to_clean[i] != '\0'; i++, counter++)
    {
      if (path_to_clean[i] == '/' && path_to_clean[i + 1] == '/')
      {
        trigger = 1;
        i++;
      }
    }
    if (path_to_clean[i - 1] == '/' && trigger == 0)
    {
      cleaned_path = my_strcpy(path_to_clean);
      return (cleaned_path);
    }
    else
    {
      // counter + 2 = 1 char for the last '/' and one for '\0'
      if (path_to_clean[i - 1] == '/')
      {
        counter--;
      }
      cleaned_path = malloc(sizeof(char) * counter + 2);
    }
    for (i = 0, counter = 0; path_to_clean[i] != '\0'; i++, counter++)
    {
      if (path_to_clean[i] == '/' && path_to_clean[i + 1] == '/')
      {
        cleaned_path[counter] = path_to_clean[i];
        i++;
      }
      else
      {
        cleaned_path[counter] = path_to_clean[i];
      }
    }
    if (cleaned_path[counter - 1] != '/')
    {
      cleaned_path[counter] = '/';
      cleaned_path[counter + 1] = '\0';
      return (cleaned_path);
    }
    else
    {
      cleaned_path[counter] = '\0';
      return (cleaned_path);
    }
  }
  my_printf("Path: %s unreachable.\n", path_to_clean);
  return (NULL);
}
