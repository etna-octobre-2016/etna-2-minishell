#ifndef IRONSH_PATH_HANDLER_H
#define IRONSH_PATH_HANDLER_H
#define ENV_ARG_PATH "/bin/"

  ///////////////////////////////////////////////////////
  // structure
  ///////////////////////////////////////////////////////
  typedef struct s_path s_path;
  struct s_path
  {
    char* path;
    s_path *next;
  };

  typedef struct s_listChain
  {
    s_path *first;
  }s_listChain;

  typedef struct structFunction
  {
    char *action;
    int (*ptr)(char*);
  }t_listFunc;
  ///////////////////////////////////////////////////////
  // CONSTANTS
  ///////////////////////////////////////////////////////
  s_listChain* s_initChain;


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  void path_handler(char** commandSplit);
  void path_handler_init();
  int add_path(char* path);
  int del_path(char* path);
  int show_path();
  int show_path_helper();
  s_path* search_chain(char* valueToSearch);
  char* cleaner_path(char* path_to_clean);
  int free_chain_path(s_listChain* list);

#endif
