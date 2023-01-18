#include "../viewer3D.h"

int parse_vertices_type(t_viewer *viewer, char *line) {
  if (strncmp(line, "VERTICES_TYPE", 13) == 0) {
    if (strncmp(line + 14, "0\n", 2) == 0 ||
        strncmp(line + 14, "1\n", 2) == 0 || strncmp(line + 14, "2\n", 2) == 0)
      viewer->settings.vertices_type = atoi(line + 14);
    else {
      printf("Vertices type loading error\n");
      return (0);
    }
    return (1);
  }
  return (0);
}

int parse_vertices_color(t_viewer *viewer, char *line) {
  char **split;
  int i;

  if (strncmp(line, "VERTICES_COLOR", 14) == 0) {
    split = ft_split(line + 15, ':');
    if (!split) exit_message("malloc error\n");
    i = -1;
    while (split[++i]) {
      if (i > 2) {
        clean_massive_2d(&split);
        printf("Vertices color loading error\n");
        return (0);
      }
    }
    return (get_rgb(split, &viewer->settings.vertices_color));
  }
  return (0);
}

int parse_vertices_size(t_viewer *viewer, char *line) {
  if (strncmp(line, "VERTICES_SIZE", 13) == 0) {
    viewer->settings.vertices_size = atof(line + 14);
    if (viewer->settings.vertices_size > MAX_VERTICES_SIZE ||
        viewer->settings.vertices_size < MIN_VERTICES_SIZE) {
      printf("Vertices size loading error\n");
      return (0);
    }
    return (1);
  }
  return (0);
}

int parse_background_color(t_viewer *viewer, char *line) {
  int i;
  char **split;

  if (strncmp(line, "BACKGROUND_COLOR", 16) == 0) {
    split = ft_split(line + 17, ':');
    if (!split) {
      exit_message("malloc error\n");
    }
    i = -1;
    while (split[++i]) {
      if (i > 2) {
        clean_massive_2d(&split);
        printf("Vertices color loading error\n");
        return (0);
      }
    }
    return (get_rgb(split, &viewer->settings.background_color));
  }
  return (1);
}
