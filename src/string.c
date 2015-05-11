#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int    my_strlen(const char *str)
{
  size_t  len;

  len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  return (len);
}

int    my_strcmp(char *s1, char *s2)
{
  int i;
  int y;
  int result;

  result = 0;
  for (i = 0, y = 0; (s1[i] != '\0' || s2[y] != '\0') && (s1[i] == s2[y]); i++,y++);
  if (s1[i] > s2[y])
    result = 1;
  if (s1[i] < s2[y])
    result = -1;
  if (s1[i] == s2[y])
    result = 0;
  return (result);
}

char    *my_strstr(char *str, char *to_find)
{
  int i;
  int u;
  int f;
  int itemp;
  int warn;

  if (to_find == '\0')
    return (str);
  for (f = 0; to_find[f] != '\0'; f++);
  if (str != NULL)
    for (i = 0; str[i] != '\0'; i++)
      {
	if (str[i] == to_find[0])
	  {
	    for (itemp = i, u = 0, warn = 0; to_find[u] != '\0'; itemp++, u++)
	      {
		if (str[itemp] == to_find[u])
		  warn++;
		else
		  warn = 0;
	      }
	    if (warn == f)
	      return (&str[i]);
	  }
      }
  return (0);
}

int my_strchar(char to_find, char* string)
{
  int i;

  for(i = 0; string[i] != '\0'; i++)
  {
    if (string[i] == to_find)
      return (0);
  }
  return (1);
}
