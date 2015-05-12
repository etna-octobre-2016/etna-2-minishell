int   my_strcmp(char *s1, char *s2)
{
  int i;
  int y;
  int result;

  result = 0;
  for (i = 0, y = 0; (s1[i] != '\0' || s2[y] != '\0') && (s1[i] == s2[y]); i++,y++);
  if (s1[i] > s2[y])
    result = 1;
  if (s1[i] < s2[y])
    result = -1;
  if (s1[i] == s2[y])
    result = 0;
  return (result);
}
