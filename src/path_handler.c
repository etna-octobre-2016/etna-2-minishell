#include <dirent.h>
#include <stdlib.h>
#include "../lib/my/src/headers/my.h"
#include "headers/path_handler.h"

void          path_handler_init()
{
  t_path*     entity;

  g_init_chain = malloc(sizeof(t_list_chain));
  entity = malloc(sizeof(t_path));
  if ((g_init_chain == NULL) || (entity == NULL))
  {
    exit(1);
  }
  entity->path = ENV_ARG_PATH;
  entity->next = NULL;
  g_init_chain->first = entity;
}

int         add_path(char* path)
{
  char*     char_buffer;
  t_path*   entity;

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
  char_buffer = cleaner_path(path);
  if (char_buffer != NULL)
  {
    entity = malloc(sizeof(t_path));
    if (entity == NULL)
    {
      return(-1);
    }
    entity->path = char_buffer;
    entity->next = g_init_chain->first;
    g_init_chain->first = entity;
    my_printf("$PATH Updated with %s.\n", entity->path);
    return (0);
  }
  return (-1);
}

int           del_path(char* path)
{
  char*       cleaned_path;
  int         trigger;
  t_path*     buffEntity;
  t_path*     entity;

  cleaned_path = cleaner_path(path);
  trigger = 0;
  entity = g_init_chain->first;
  while (entity != NULL)
  {
    if (my_strcmp(entity->path, cleaned_path) == 0)
    {
      if (trigger == 0)
      {
        g_init_chain->first = entity->next;
        my_printf("%s removed from $PATH.\n", entity->path);
        free(entity);
        return (0);
      }
      else
      {
        buffEntity->next = entity->next;
        my_printf("%s removed from $PATH.\n", entity->path);
        free(entity);
        free(cleaned_path);
        return (0);
      }
    }
    trigger = 1;
    buffEntity = entity;
    entity = entity->next;
  }
  my_printf("%s not found on $PATH.\n", path);
  free(cleaned_path);
  return (0);
}

int           free_chain_path(t_list_chain* list)
{
  t_path*     entity;

  while (list->first != NULL)
  {
    entity = list->first;
    list->first = entity->next;
    free(entity);
  }
  free(list);
  return (0);
}

int           show_path(char* commandSplit)
{
  t_path*     entity;

  if (commandSplit != NULL)
  {
    if (my_strcmp(commandSplit, "--help") == 0)
    {
      show_path_helper();
      return (0);
    }
  }
  entity = g_init_chain->first;
  my_printf("$PATH=================\n");
  while (entity != NULL)
  {
    my_printf("%s\n", entity->path);
    entity = entity->next;
  }
  my_printf("=====================>\n");
  return (0);
}

int show_path_helper()
{
  my_printf("Utilisation :\nPermet d'ajouter ou de supprimer facilement des chemins dans votre variable d'environnement $PATH.\n-add_path /usr/bin      Permet d'ajouter /usr/bin au $PATH\n-del_path /usr/bin      Permet de supprimer /usr/bin au $PATH\n-path                   Permet d'afficher tous les chemins de votre $PATH\n");
  return (0);
}

t_path*       search_chain(char* valueToSearch)
{
  t_path*     searchEntity;

  searchEntity = g_init_chain->first;
  while (searchEntity != NULL)
  {
    if (my_strcmp(searchEntity->path, valueToSearch) == 0)
    {
      return (searchEntity);
    }
    searchEntity = searchEntity->next;
  }
  return (NULL);
}

char*         cleaner_path(char* path_to_clean)
{
  char*       cleaned_path;
  int         counter;
  int         i;
  int         trigger;

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
