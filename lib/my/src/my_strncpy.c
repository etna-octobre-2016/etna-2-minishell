#include "headers/my.h"

char  *my_strncpy(char *dest, char *src, int n)
{
  int i;
  int u;

  for (u = 0; src[u] != '\0'; u++);
  if (n >= u)
  {
    dest = my_strcpy(src);
    return (dest);
  }
  if (n < u)
  {
    for (i = 0; i < n; i++)
    {
      dest[i] = src[i];
    }
    dest[i] = '\0';
  }
  return (dest);
}
