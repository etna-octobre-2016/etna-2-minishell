#include <stdlib.h>
#include <unistd.h>

char* my_readline(int alloc)
{
  ssize_t ret;
  char*buff;

  if ((buff = malloc(sizeof(*buff) * (alloc + 1))) == NULL)
    return (NULL);
  if ((ret = read(0, buff, alloc)) > 1)
    {
      buff[ret - 1] = '\0';
      return (buff);
    }
  buff[0] = '\0';
  return (buff);
}
