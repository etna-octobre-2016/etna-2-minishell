#ifndef IRONSH_BUILTINS_H
#define IRONSH_BUILTINS_H


  ///////////////////////////////////////////////////////
  // CONSTANTS
  ///////////////////////////////////////////////////////
  #define BUILTIN_UNKNOWN 0
  #define BUILTIN_SUCCESS 1
  #define BUILTIN_ERROR   2
  #define BUILTIN_EXIT    3


  ///////////////////////////////////////////////////////
  // CONSTANTS
  ///////////////////////////////////////////////////////
  #define UNUSED(var) var = var


  ///////////////////////////////////////////////////////
  // STRUCTURES
  ///////////////////////////////////////////////////////
  struct    s_builtin
  {
    char*   name;
    int     (*func)(char **commandSplit);
  };


  ///////////////////////////////////////////////////////
  // TYPES
  ///////////////////////////////////////////////////////
  typedef struct s_builtin t_builtin;


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  int builtin_cd(char **commandSplit);
  int builtin_env(char **commandSplit);
  int builtin_exit(char **commandSplit);
  int builtin_handle(char **commandSplit);
  int builtin_path(char **commandSplit);
  int builtin_path_add(char **commandSplit);
  int builtin_path_del(char **commandSplit);
  int builtin_pwd(char **commandSplit);
  int builtin_setenv(char **commandSplit);
  int builtin_unsetenv(char **commandSplit);


#endif
