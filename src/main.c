#include <stdlib.h>
#include "headers/env.h"
#include "headers/prompt.h"
#include "headers/path_handler.h"
#include "headers/main.h"

int   main()
{
  int ret;

  ret = EXIT_SUCCESS;
  path_handler_init();
  if (prompt_init() == false)
  {
    ret = EXIT_FAILURE;
  }
  free_chain_path(s_initChain);
  env_free_list();
  return (ret);
}
