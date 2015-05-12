#include "headers/parser.h"

int parser(char* commandLine)
{
  char specialsChar[] = {'|', '<', '>', '&', '0'};
  //Minded : nohup must only be found at the begining of commandLine
  int i;

  for(i = 0; specialsChar[i] != '0'; i++)
  {
    if (my_strchar(specialsChar[i], commandLine) == 0)
      {
        my_printf("Argument found : %c\n", specialsChar[i]);
        return (0);
      }
  }
  my_printf("Argument not found...\n");
  return (1);
}
