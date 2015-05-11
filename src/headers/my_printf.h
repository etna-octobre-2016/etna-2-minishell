/*
** Header.h for  in /Users/stevenleclerc/Documents/Projets/myPrintf/my_printf/my_printf/emacs
**
** Made by Steven Leclerc
** Login   <lecler_s@etna-alternance.net>
**
** Started on  Wed Apr 23 11:39:49 2014 Steven Leclerc
** Last update Thu May  1 10:06:34 2014 Steven Leclerc
*/

#ifndef my_printf_Header_h
#define my_printf_Header_h
#include "string.h"

  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////

  void my_printf(char *fstring, ...);
  void my_put_nbr(int nb);
  void my_putchar(int c);
  void my_putstr(char *str);
  void convertHex (int input, int maj);
  void nibblesIT(int tabEmptyBin[], int recupHexa[]);
  void readHexa(int recupHexa[]);
  void hexaMaj(int input);
  void hexaMin(int input);
  void convOctal(int input);
  int checkChar(char input, int *iPoint);
  void unsignedU(int input);
  void binA(int input);
  void readBin(int tabEmpty[]);

  typedef struct arg_l
  {
    char letter;
    void (*function)();
  }arg_letter;

#endif
