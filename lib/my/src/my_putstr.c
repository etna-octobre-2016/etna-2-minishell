/*
** my_putstr.c for  in /Users/stevenleclerc/Documents/Prog-C/Piscine/lecler_s/my_putstr
**
** Made by LECLERC Steven
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Wed Oct 23 09:48:42 2013 LECLERC Steven
** Last update Wed Apr 23 13:31:41 2014 Steven Leclerc
*/
void my_putchar(char c);

void my_putstr(char *str)
{
  int i;

  for (i = 0; str[i] != '\0'; i++)
    {
      my_putchar(str[i]);
    }
}
