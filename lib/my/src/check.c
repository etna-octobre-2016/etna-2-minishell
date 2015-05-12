/*
** check.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
** 
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
** 
** Started on  Wed Apr 23 11:38:08 2014 Steven Leclerc
** Last update Wed Apr 23 11:38:34 2014 Steven Leclerc
*/

int checkChar(char input, int *iPoint)
{
  char list[10] = {'d','c','i','s','x','X','b','o','u','b'};
  int i;
  for (i = 0; i < 10; i++)
    {
      if (list[i] == input)
	return (1);
    }
  *iPoint += 1;
  return (0);
}
