#ifndef IRONSH_STRING_H
#define IRONSH_STRING_H
#include <stddef.h>

  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  size_t my_strlen(const char *);
  int my_strcmp(char *s1, char *s2);
  char *my_strstr(char *str, char *to_find);
  int my_strchar(char to_find, char* string);

#endif
