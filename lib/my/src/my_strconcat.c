/*
** my_strcpy.c for  in /Users/stevenleclerc/Documents/Prog-C/Piscine5/lecler_s/my_strcpy
**
** Made by LECLERC Steven
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Fri Oct 25 09:06:06 2013 LECLERC Steven
** Last update Fri Oct 25 11:51:52 2013 LECLERC Steven
*/
#include "headers/my.h"
#include <stdlib.h>

char *my_strconcat(char* first_string, char* second_string)
{
  int i;
  int u;
  int len_first_string;
  int len_total;
  char* final_string;

  len_first_string = my_strlen(first_string);
  len_total = my_strlen(second_string) + len_first_string;
  final_string = malloc(sizeof(char) * (len_total + 1));
  for (i = 0; i <= (len_first_string - 1); i++)
    final_string[i] = first_string[i];
  for (u = 0; i <= (len_total); i++, u++)
    final_string[i] = second_string[u];
  return (final_string);
}
