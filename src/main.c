#include <stdlib.h>
#include "headers/prompt.h"
#include "headers/main.h"

int main()
{
  if (prompt_init() == false)
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
