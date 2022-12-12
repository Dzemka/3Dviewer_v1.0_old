#include "../viewer3D.h"

void clean_massive_2d(char ***m)
{
  int i;
  char **s;

  s = *m;
  i = -1;
//  while (s[++i])
//    free(s[i]);
//  free(s);
}

void  exit_message(char *s)
{
  printf("%s\n", s);
  exit(errno);
}