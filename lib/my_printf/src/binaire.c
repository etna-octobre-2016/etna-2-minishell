/*
** binaire.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
**
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Wed Apr 23 11:37:20 2014 Steven Leclerc
** Last update Wed Apr 23 13:25:09 2014 Steven Leclerc
*/
#include <math.h>
void readBin(int tabEmpty[]);

void binA(int input)
{
  int tabB[29] = {1};
  int tabEmpty[29] = {0};
  int i;
  int u;
  int recup;

  recup = input;
  for (u = 1,i = 2; i < pow(2,30); i *= 2, u++)
    tabB[u] = i;
  for (i = 28; i >= 0; i--)
    {
      if (recup >= tabB[i])
  {
    recup -= tabB[i];
    tabEmpty[i] = 1;
  }
    }
  readBin(tabEmpty);
}
