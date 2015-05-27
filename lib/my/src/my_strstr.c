#include <unistd.h>

char  *my_strstr(char *str, char *to_find)
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
