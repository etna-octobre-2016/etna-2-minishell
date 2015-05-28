#ifndef IRONSH_PARSER_H
#define IRONSH_PARSER_H


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  char**  split_cmd(char* commandLine);
  int     parser(char* commandLine);
  int*    count_char(char* commandLine, int nb_args);
  void    free_array(char** commandSplit);


#endif
