/*
** unsignedU.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
**
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Wed Apr 23 11:47:13 2014 Steven Leclerc
** Last update Wed Apr 23 13:34:00 2014 Steven Leclerc
*/
#include <math.h>
int my_put_nbr(int nb);

void unsignedU(int input)
{
  int totalBitOne;
  int totalBitTwo;
  int trigger;
  int i;

  totalBitOne = 4;
  totalBitTwo  = 294967296;
  if (input < 0)
    {
      input *= -1;
      for (trigger = 0;trigger == 0 ;)
        {
	  if (input > totalBitTwo)
	    {
	      input -= totalBitTwo;
	      totalBitOne--;
	    }
	  else
	    {
	      trigger = 1;
	      totalBitTwo -= input;
	    }
        }
      my_put_nbr(totalBitOne);
      for (i = 1; i < 10000000; i*= 10)
	if ((totalBitTwo / i) < 1)
	  my_put_nbr(0);
      my_put_nbr(totalBitTwo);
    }
  else
    my_put_nbr(input);
}
