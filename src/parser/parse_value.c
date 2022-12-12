#include "../viewer3D.h"

static void set_start_value(double value, int axes, t_viewer *viewer) {
  if (axes == 0) {
    viewer->dimensions.x_max = value;
    viewer->dimensions.x_min = value;
  } else if (axes == 1) {
    viewer->dimensions.y_max = value;
    viewer->dimensions.y_min = value;
  } else if (axes == 2) {
    viewer->dimensions.z_max = value;
    viewer->dimensions.z_min = value;
  }
}

static void set_dimensions(double value, t_viewer *viewer, int axes) {
  if (viewer->info.count_v == 1)
    set_start_value(value, axes, viewer);
  else if (axes == 0) {
    if (value > viewer->dimensions.x_max)
      viewer->dimensions.x_max = value;
    else if (value < viewer->dimensions.x_min)
      viewer->dimensions.x_min = value;
  } else if (axes == 1) {
    if (value > viewer->dimensions.x_max)
      viewer->dimensions.y_max = value;
    else if (value < viewer->dimensions.x_min)
      viewer->dimensions.y_min = value;
  } else if (axes == 2) {
    if (value > viewer->dimensions.x_max)
      viewer->dimensions.z_max = value;
    else if (value < viewer->dimensions.x_min)
      viewer->dimensions.z_min = value;
  }
}

static int fill_vertex(char **split_line, t_viewer *viewer) {
  double *vertex;
  t_list *list;
  int i;

  vertex = malloc(sizeof(double) * 3);
  if (!vertex) exit_message("Malloc error");
  viewer->info.count_v++;
  i = -1;
  while (++i < 3) {
    vertex[i] = atof(split_line[i]);
    set_dimensions(vertex[i], viewer, i);
  }
  list = ft_lstnew(vertex);
  ft_lstadd_back(&viewer->vertex_list, list);
}

int parse_vertex(char **split_line, t_viewer *viewer) {
  int i;

  i = -1;
  while (split_line[++i])
    ;
  if (i != 3) {
    printf("Incorrect number of points");
    return (1);
  }
  fill_vertex(split_line, viewer);
  return (0);
}

int parse_face(char **split_line, t_viewer *viewer) {
  int i;
  t_plane *plane;
  t_list *list;
  t_list *tmp;

  i = -1;
  while (split_line[++i])
    ;
  if (i < 3) {
    printf("not enough plane points");
    return (1);
  }
  plane = malloc(sizeof(t_plane));
  if (!plane) exit_message("Malloc error");
  plane->indexes = malloc((sizeof(size_t) * i));
  if (!plane->indexes) exit_message("Malloc error");
  plane->size = i;
  i = -1;
  while (++i < plane->size) plane->indexes[i] = atoi(split_line[i]);
  list = ft_lstnew(plane);
  ft_lstadd_back(&viewer->info.faces, list);
  return (0);
}
