/*
** readBin.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
** 
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
** 
** Started on  Wed Apr 23 11:45:04 2014 Steven Leclerc
** Last update Wed Apr 23 13:33:00 2014 Steven Leclerc
*/
int my_put_nbr(int nb);

void readBin(int tabEmpty[])
{
  int trigger;
  int i;

  for (i = 28, trigger = 0; i >= 0; i--)
    {
      if (tabEmpty[i] == 1)
        trigger = 1;
      if (trigger == 1)
	my_put_nbr(tabEmpty[i]);
    }
}
