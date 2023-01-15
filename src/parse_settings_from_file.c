#include "viewer3D.h"

// returns: error(0), ok(1)

static int get_setting(t_viewer *viewer, char *line, t_settings *settings,
                       int *number_setting) {
  char **split;
  char *ptr;

  ptr = strchr(line, ',');
  if (ptr)
    ptr[0] = '.';
  if (*number_setting == 0 && strncmp(line, "PROJECTION", 10) == 0) {
    if (strncmp(line + 11, "0\n", 2) == 0)
      settings->func_proj = &central_proj;
    else if (strncmp(line + 11, "1\n", 1) == 0)
      settings->func_proj = &parallel_proj;
    else
      return (0);
  }
  if (*number_setting == 1 && strncmp(line, "EDGE_TYPE", 9) == 0) {
    if (strncmp(line + 10, "0\n", 2) == 0 ||
        strncmp(line + 10, "1\n", 2) == 0) {
      settings->is_dashed = atoi(line + 10);
      printf("dashed %d\n", settings->is_dashed);
    } else {
      return (0);
    }
  }
  if (*number_setting == 2 && strncmp(line, "EDGE_COLOR", 9) == 0) {
    split = ft_split(line + 11, ':');
    if (!split) exit_message("malloc_error");
    settings->vertices_color.red = atof(split[0]);
    settings->vertices_color.green = atof(split[1]);
    settings->vertices_color.blue = atof(split[2]);
    if (settings->vertices_color.red > 255 ||
        settings->vertices_color.green > 255 ||
        settings->vertices_color.blue > 255 ||
        settings->vertices_color.red < 0 ||
        settings->vertices_color.green < 0 || settings->vertices_color.blue < 0)
      return (0);
  }
  if (*number_setting == 3 && strncmp(line, "EDGE_THICKNESS", 14) == 0) {
    settings->edge_thickness = atof(line + 15);
  }
//  if (*number_setting)
  return (1);
  //  printf("sho");
}

// returns: error(-1), read_end(1), reads(0)
static int parse_settings_line(t_viewer *viewer, FILE *file,
                               t_settings *settings, int *number_setting) {
  char *line;
  size_t len;

  line = NULL;
  errno = 0;
  // free line
  if (getline(&line, &len, file) == -1) {
    if (errno) {
      return (-1);
    }
    return (1);
  }
  if (!get_setting(viewer, line, settings, number_setting)) return (-1);
  (*number_setting)++;
  return (0);
}

int parse_settings_file(t_viewer *viewer, FILE *file) {
  int read_end;
  t_settings settings;
  int number_setting;

  number_setting = 0;
  read_end = 0;
  while (!read_end)
    read_end = parse_settings_line(viewer, file, &settings, &number_setting);
  if (read_end == -1) return (0);
  printf("parse settings ok\n");
}