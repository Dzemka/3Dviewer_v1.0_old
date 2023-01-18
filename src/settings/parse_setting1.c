#include "../viewer3D.h"

int get_rgb(char **split, GdkRGBA *rgb)
{
  rgb->red = atof(split[0]);
  rgb->green = atof(split[1]);
  rgb->blue = atof(split[2]);
  clean_massive_2d(&split);
  if (rgb->red > 255 ||
      rgb->green > 255 ||
      rgb->blue > 255 ||
      rgb->red < 0 ||
      rgb->green < 0 ||
      rgb->blue < 0) {
    printf("Color loading error\n");
    return (0);
  }
  return (1);
}

int parse_proj(t_viewer *viewer, char *line) {
  if (strncmp(line, "PROJECTION", 10) == 0) {
    if (strncmp(line + 11, "0\n", 2) == 0)
      viewer->settings.func_proj = &central_proj;
    else if (strncmp(line + 11, "1\n", 1) == 0)
      viewer->settings.func_proj = &parallel_proj;
    else {
      printf("projection type loading error\n");
      return (0);
    }
    return (1);
  }
  return (0);
}

int parse_edge_type(t_viewer *viewer, char *line) {
  if (strncmp(line, "EDGE_TYPE", 9) == 0) {
    if (strncmp(line + 10, "0\n", 2) == 0 ||
        strncmp(line + 10, "1\n", 2) == 0) {
      viewer->settings.is_dashed = atoi(line + 10);
    } else {
      printf("Edge type loading error\n");
      return (0);
    }
    return (1);
  }
  return (0);
}

int parse_edge_color(t_viewer *viewer, char *line) {
  char **split;
  int i;

  if (strncmp(line, "EDGE_COLOR", 9) == 0) {
    split = ft_split(line + 11, ':');
    if (!split) exit_message("malloc_error");
    i = -1;
    while (split[++i]) {
      if (i > 2) {
        clean_massive_2d(&split);
        printf("Edge color loading error\n");
        return (0);
      }
    }
    return (get_rgb(split, &viewer->settings.edge_color));
  }
  return (0);
}

int parse_edge_thickness(t_viewer *viewer, char *line)
{
  if (strncmp(line, "EDGE_THICKNESS", 14) == 0) {
    viewer->settings.edge_thickness = atof(line + 15);
    if (viewer->settings.edge_thickness < MIN_EDGE_THICKNESS ||
        viewer->settings.edge_thickness > MAX_EDGE_THICKNESS) {
      printf("Edge thickness loading error\n");
      return (0);
    }
    return (1);
  }
  return (0);
}