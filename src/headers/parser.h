#ifndef IRONSH_PARSER_H
#define IRONSH_PARSER_H

#define SPECIALS_CHAR {'|', '<', '>', '&', '0'};
///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
  int parser(char* commandLine);
  char** split_cmd(char* commandLine);
  int* count_char(char* commandLine, int nb_args);
  void free_array(char** commandSplit);

#endif
