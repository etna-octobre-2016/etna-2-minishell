#include <stdlib.h>
#include "headers/my.h"

int     my_strpos(char *haystack, char *needle)
{
  int   position;
  char  *match;

  position = -1;
  match = my_strstr(haystack, needle);
  if (match != NULL)
  {
    position = (match - haystack);
  }
  return (position);
}
