#include "../lib/my/src/headers/my.h"
#include <errno.h>

void error_handler(char* commandName)
{
  const char* errlist[] = {
    [EPERM]  = "Operation not permitted",
    [ENOENT] = "No such file or directory",
    [ESRCH]  = "No such process",
    [EINTR]  = "Interrupted system call",
    [EIO]    = "I/O error",
    [ENXIO]  = "No such device or address",
    [E2BIG]  = "Argument list too long",
  };
  int i;

  for (i = 0; i != errno ; i++);
  my_printf("%s : %s\n", commandName, errlist[i--]);
}
