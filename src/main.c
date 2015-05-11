#include "headers/main.h"
#include <stdio.h>
#include "headers/my_printf.h"

int main(int argc, char** argv)
{
  my_printf("Hello world\n%d\n%s\n",argc, argv[0]);
  return (0);
}
