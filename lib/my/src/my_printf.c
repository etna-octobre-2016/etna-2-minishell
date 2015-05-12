/*
** my_printf.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
**
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Wed Apr 23 11:35:12 2014 Steven Leclerc
** Last update Wed Apr 23 13:12:30 2014 Steven Leclerc
*/
#include <stdarg.h>
#include "headers/my.h"

void my_printf(char *fstring, ...)
{
  arg_letter letter[] =
    {
      {'b', binA},
      {'u', unsignedU},
      {'d', my_put_nbr},
      {'c', my_putchar},
      {'i', my_put_nbr},
      {'s', my_putstr},
      {'x', hexaMin},
      {'X', hexaMaj},
      {'o', convOctal},
      {'0', 0}
    };
  va_list arguments;
  int i;
  int u;
  va_start(arguments, fstring);

  for (i = 0; fstring[i] != '\0'; i++)
    {
      if ( fstring[i] == '%' && checkChar(fstring[i+1], &i) == 1)
        {
    for (u = 0; letter[u].letter != '0'; u++)
            {
        if (letter[u].letter == fstring[i+1])
    {
      letter[u].function(va_arg(arguments, void*));
    }
            }
    i++;
        }
      else
  my_putchar( fstring[i] );
    }
  va_end(arguments);
}
