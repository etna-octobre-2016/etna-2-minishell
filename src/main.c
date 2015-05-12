#include "../lib/my/src/headers/my_printf.h"
#include "headers/main.h"

int main(int argc, char** argv)
{
  my_printf("Hello world\n%d\n%s\n%c",argc, argv[0], 'c');
  return (0);
}
