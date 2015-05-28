#ifndef IRONSH_BIN_CALLER_H
#define IRONSH_BIN_CALLER_H


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  char* get_bin(char* bin_name, int opt);
  char* rewrite_command(char* commandLine, char* bin_name_cleaned);
  char* set_path_to_bin(char* bin);
  char* she_banging(char* commandLine);
  int   bin_caller(char* commandSplit[]);


#endif
