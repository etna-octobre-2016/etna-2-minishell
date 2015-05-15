#include "../lib/my/src/headers/my.h"
#include "headers/parser.h"
#include "headers/bin_caller.h"
#include <stdio.h>

int main(int argc, char** argv)
{
  my_printf("Hello world\n%d\n%s\n",argc, argv[0]);
  char* commandLine_one = "ls -l -a -t -h";
  // char* commandLine_two = "cat test.txt | grep test";
  // char* commandLine_three = "cat test.txt > output.txt";
  // char* commandLine_four = "cat test.txt < source.txt";
  // char* commandLine_five = "cat test.txt &";
  //char* commandSplit[] = {"ls", "-l", NULL};
  // Testing arg :
  parser(commandLine_one);
  // parser(commandLine_two);
  // parser(commandLine_three);
  // parser(commandLine_four);
  // parser(commandLine_five);

  //bin_caller(commandSplit);
  return (0);
}
