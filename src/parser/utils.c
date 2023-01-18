#include "../viewer3D.h"

char *ft_strjoin(char const *s1, char const *s2) {
  size_t len_new_str;
  char *str;

  if (s1 == NULL || s2 == NULL) return (NULL);
  str = NULL;
  len_new_str = strlen(s1) + strlen(s2) + 1;
  str = (char *)malloc(sizeof(char) * (len_new_str));
  if (str == NULL) return (NULL);
  strncpy(str, s1, len_new_str);
  strncat(str, s2, len_new_str);
  return (str);
}

void clean_massive_2d(char ***m) {
  int i;
  char **s;

  s = *m;
  i = -1;
  while (s[++i]) free(s[i]);
  free(s);
}

void exit_message(char *s) {
  printf("%s\n", s);
  exit(errno);
}

void clean_info(t_viewer *viewer) {
  t_list *tmp;
  t_plane *plane;

  if (viewer->info.vertexes3d) free(viewer->info.vertexes3d);
  viewer->info.vertexes3d = NULL;
  if (viewer->info.vertexes2d) free(viewer->info.vertexes2d);
  viewer->info.vertexes2d = NULL;
  ft_lstclear(&viewer->vertex_list, free);
  viewer->vertex_list = NULL;
  viewer->info.count_v = 0;
  tmp = viewer->info.faces;
  while (viewer->info.faces) {
    plane = viewer->info.faces->content;
    tmp = viewer->info.faces->next;
    free(plane->indexes);
    free(plane);
    free(viewer->info.faces);
    viewer->info.faces = tmp;
  }
  viewer->info.faces = NULL;
  viewer->info.count_v = 0;
}