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
    bool              is_piped;
    bool              is_redirect_input;
    bool              is_redirect_output;
    char              *cmd;
    struct s_cmd_list *prev;
    struct s_cmd_list *next;
  };
  struct              s_symbol_match
  {
    bool              is_pipe;
    bool              is_redirect_input;
    bool              is_redirect_output;
    int               position;
    char              *string;
  };


  ///////////////////////////////////////////////////////
  // TYPES
  ///////////////////////////////////////////////////////
  typedef struct s_cmd_list     t_cmd_list;
  typedef struct s_symbol_match t_symbol_match;


  ///////////////////////////////////////////////////////
  // PROTOTYPES
  ///////////////////////////////////////////////////////
  bool            prompt_init();
  void            prompt_cmd_set_flags(t_cmd_list *, t_symbol_match *);
  void            prompt_show();

  char            *prompt_cmd_read();
  t_cmd_list      *prompt_cmd_list_add_item(t_cmd_list *, t_cmd_list *);
  t_cmd_list      *prompt_cmd_split(char *);
  t_symbol_match  *prompt_cmd_find_first_symbol(char *);

#endif
