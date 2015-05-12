int   my_strchar(char to_find, char* string)
{
  int i;

  for (i = 0; string[i] != '\0'; i++)
  {
    if (string[i] == to_find)
    {
      return (0);
    }
  }
  return (1);
}
