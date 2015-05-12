/*
** my_put_nbr.c for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
** 
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
** 
** Started on  Wed Apr 23 13:06:46 2014 Steven Leclerc
** Last update Wed Apr 23 13:31:32 2014 Steven Leclerc
*/
void my_putchar(char c);

int my_put_nbr(int nb)
{
  int i;
  int divi;

  if (nb < 0)
    {
      nb *= -1;
      my_putchar('-');
    }
  if ( nb == 0)
    {
      my_putchar('0');
      return (1);
    }
  for (i = 1; i <= nb; i *= 10);
  i /= 10;
  for (; i != 1; i /= 10)
    {
      divi = nb / i;
      my_putchar('0' + divi);
      nb -= (divi * i);
    }
  my_putchar('0' + nb);
  return (0);
}
