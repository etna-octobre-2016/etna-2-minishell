#include "headers/prompt.h"
#include "headers/path_handler.h"
#include "headers/main.h"

int main()
{
  //INIT LIST PATH
  path_handler_init();
  prompt_init();
  //delete and frees before close shell
  free_chain_path(s_initChain);
  return (0);
}
