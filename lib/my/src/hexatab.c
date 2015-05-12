/*
** hexatab.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
** 
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
** 
** Started on  Wed Apr 23 11:42:34 2014 Steven Leclerc
** Last update Wed Apr 23 11:42:58 2014 Steven Leclerc
*/

void nibblesIT(int tabEmptyBin[], int recupHexa[])
{
  int i;
  int u;
  int v;
  int result;
  int hexa[4] = {1,2,4,8};

  result = 0;
  for (i = 0, u = 0, v = 0; i <= 29; i++, u++)
    {
      if (u == 4)
        {
	  u = 0;
	  recupHexa[v] = result;
	  result = 0;
	  v++;
        }
      if (tabEmptyBin[i] == 1)
	result = result + hexa[u];
    }
}
