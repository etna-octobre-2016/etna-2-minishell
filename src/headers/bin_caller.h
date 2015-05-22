#ifndef IRONSH_FUNCCALLER_H
#define IRONSH_FUNCCALLER_H
#define ENV_ARG_PATH "/bin/"

///////////////////////////////////////////////////////
// PROTOTYPES
///////////////////////////////////////////////////////
  int bin_caller(char* commandSplit[]);
  char* she_banging(char* commandLine);
  char* get_bin(char* bin_name, int opt);
  char* rewrite_command(char* commandLine, char* bin_name_cleaned);
  
#endif
