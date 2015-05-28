#ifndef IRONSH_PATH_HANDLER_H
#define IRONSH_PATH_HANDLER_H


  ///////////////////////////////////////////////////////
  // CONSTANTS
  ///////////////////////////////////////////////////////
  #define ENV_ARG_PATH "/bin/"


  ///////////////////////////////////////////////////////
  // STRUCTURES
  ///////////////////////////////////////////////////////
  struct            s_path
  {
    char*           path;
    struct s_path*  next;
  };
  struct            s_listChain
  {
    struct s_path*  first;
  };
  struct            s_function
  {
    char*           action;
    int             (*ptr)(char*);
  };


  ///////////////////////////////////////////////////////
  // STRUCTURES
  ///////////////////////////////////////////////////////
  typedef struct s_path t_path;
  typedef struct s_listChain t_list_chain;
  typedef struct s_function t_list_func;


  ///////////////////////////////////////////////////////
  // GLOBALS
  ///////////////////////////////////////////////////////
  t_list_chain* g_init_chain;


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  char*     cleaner_path(char* path_to_clean);
  int       add_path(char* path);
  int       del_path(char* path);
  int       free_chain_path(t_list_chain* list);
  int       show_path();
  int       show_path_helper();
  t_path*   search_chain(char* valueToSearch);
  void      path_handler_init();


#endif
