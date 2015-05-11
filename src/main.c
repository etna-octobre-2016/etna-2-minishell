#include "headers/main.h"
#include <stdio.h>
#include "headers/my_printf.h"

int main(int argc, char** argv)
{
  my_printf("Hello world\n%d\n%s\n%c",argc, argv[0], 'c');
  return (0);
}
