#ifndef IRONSH_PARSER_H
#define IRONSH_PARSER_H

  ///////////////////////////////////////////////////////
  // INCLUDES
  ///////////////////////////////////////////////////////
  #include "prompt.h"

  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  int parser(t_cmd_list *);
  char** split_cmd(char* commandLine);
  int* count_char(char* commandLine, int nb_args);
  void free_array(char** commandSplit);

#endif
