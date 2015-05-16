#ifndef IRONSH_PROMPT_H
#define IRONSH_PROMPT_H

  ///////////////////////////////////////////////////////
  // INCLUDES
  ///////////////////////////////////////////////////////
  #include <stdbool.h>

  ///////////////////////////////////////////////////////
  // CONSTANTS
  ///////////////////////////////////////////////////////
  #define PROMPT_BUFFER_SIZE      1024
  #define PROMPT_DEFAULT_STRING   "$>"
  #define PROMPT_SPECIAL_SYMBOLS  {"|", "<", ">", "&&", "&", NULL}


  ///////////////////////////////////////////////////////
  // STRUCTURES
  ///////////////////////////////////////////////////////
  struct              s_cmd_list
  {
    bool              is_pipe;
    bool              is_redirect_in;
    bool              is_redirect_out;
    char              *cmd;
    struct s_cmd_list *prev;
    struct s_cmd_list *next;
  };

  struct s_symbol_match
  {
    char *string;
    int  position;
  };


  ///////////////////////////////////////////////////////
  // TYPES
  ///////////////////////////////////////////////////////
  typedef struct s_cmd_list     t_cmd_list;
  typedef struct s_symbol_match t_symbol_match;


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  void            prompt_init();
  void            prompt_show();
  char            *prompt_read_cmd();
  t_cmd_list      *prompt_split_cmd(char *);
  t_symbol_match  *prompt_find_first_special_symbol(char *);

#endif
