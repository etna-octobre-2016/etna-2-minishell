/*
** readHexa.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
** 
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
** 
** Started on  Wed Apr 23 11:45:50 2014 Steven Leclerc
** Last update Wed Apr 23 13:33:37 2014 Steven Leclerc
*/
void my_putchar(char c);

void readHexa(int recupHexa[],int maj)
{
  char listHexa[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
  char listHexaM[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  int i;
  int v;
  int u;

  i = 29;
  v = 0;
  while (i >= 0)
    {
      if (recupHexa[i] != 0 || v == 1)
	{
	  for (u = 0; u <= recupHexa[i]; u++);
	  if (maj == 0)
	    my_putchar(listHexa[u-1]);
	  else
	    my_putchar(listHexaM[u-1]);
	  v = 1;
	}
      i--;
    }
}
