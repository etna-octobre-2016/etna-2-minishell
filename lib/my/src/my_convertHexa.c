/*
** my_convertHexa.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
** 
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
** 
** Started on  Wed Apr 23 11:43:24 2014 Steven Leclerc
** Last update Wed Apr 23 13:30:43 2014 Steven Leclerc
*/

#include <math.h>
void readHexa(int recupHexa[],int maj);
void nibblesIT(int tabEmptyBin[], int recupHexa[]);

void convertHex (int input, int maj)
{
  int recup;
  int tabBin[29] = {1};
  int tabEmptyBin[29] = {0};
  int recupHexa[29] = {0};
  int i;
  int u;

  recup = input;
  for (u = 1,i = 2; i < pow(2,30); i *= 2, u++)
    tabBin[u] = i;
  for (i = 29; i >= 0; i--)
    {
      if (recup >= tabBin[i])
        {
	  recup = recup - tabBin[i];
	  tabEmptyBin[i] = 1;
        }
    }
  nibblesIT(tabEmptyBin,recupHexa);
  readHexa(recupHexa,maj);
}
