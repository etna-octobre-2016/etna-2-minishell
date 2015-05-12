/*
** octal.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
**
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Wed Apr 23 11:44:17 2014 Steven Leclerc
** Last update Wed Apr 23 13:32:16 2014 Steven Leclerc
*/
int my_put_nbr(int nb);

void convOctal(int input)
{
  int i;
  int modulo;
  int tab[32] = {0};

  if (input < 8)
    my_put_nbr(input);
  else
    for (i = 0; input >= 8; i++)
      {
        modulo = input % 8;
        tab[i] = modulo;
        input /= 8;
        if (input <= 8)
	  tab[i+1] = input;
      }
  for (i = 31, modulo = 0; i >= 0; i--)
    {
      if (tab[i] != 0)
	modulo = 1;
      if (modulo == 1)
        my_put_nbr(tab[i]);
    }
}
