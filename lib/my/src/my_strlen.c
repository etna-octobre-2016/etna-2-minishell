#include <stddef.h>

int       my_strlen(const char *str)
{
  size_t  len;

  len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  return (len);
}
