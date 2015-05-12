/*
** my_putchar.c for  in /Users/stevenleclerc/Documents/Prog-C/Lib à integrer
**
** Made by LECLERC Steven
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Sat Oct 26 16:48:12 2013 LECLERC Steven
** Last update Wed Apr 23 13:11:14 2014 Steven Leclerc
*/
#include <unistd.h>

void my_putchar(int c)
{
  write(1, &c, 1);
}
