#include <stdlib.h>
#include "headers/my.h"

char* my_strcpy(char* str_source)
{
  int i;
  int len;
  char* str_cpy;

  for (len = 0; str_source[len] != '\0'; len++);
  str_cpy = malloc(sizeof(char) * len + 1);
  for (i = 0; str_source[i] != '\0'; i++)
  {
    str_cpy[i] = str_source[i];
  }
  str_cpy[i] = '\0';
  return (str_cpy);
}
