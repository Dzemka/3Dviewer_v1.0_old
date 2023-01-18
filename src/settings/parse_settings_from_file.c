#include "../viewer3D.h"

static void fix_comma(char *line)
{
  char *ptr;

  ptr = strchr(line, ',');
  if (ptr) ptr[0] = '.';
  while (ptr)
  {
    ptr = strchr(line, ',');
    if (ptr) ptr[0] = '.';
  }
}

static int get_setting(t_viewer *viewer, char *line,
                       int number_setting) {
  fix_comma(line);
  if (number_setting == 0)
    return(parse_proj(viewer, line));
  if (number_setting == 1)
    return (parse_edge_type(viewer, line));
  if (number_setting == 2)
    return (parse_edge_color(viewer, line));
  if (number_setting == 3)
    return (parse_edge_thickness(viewer, line));
  if (number_setting == 4)
    return (parse_vertices_type(viewer, line));
  if (number_setting == 5)
    return (parse_vertices_color(viewer, line));
  if (number_setting == 6)
    return (parse_vertices_size(viewer, line));
  if (number_setting == 7)
    return (parse_background_color(viewer, line));
  return (1);
}

static int parse_settings_line(t_viewer *viewer, FILE *file, int *number_setting) {
  char *line;
  size_t len;

  line = NULL;
  errno = 0;
  if (getline(&line, &len, file) == -1) {
    free(line);
    if (errno) {
      return (-1);
    }
    return (1);
  }
  if (!get_setting(viewer, line, *number_setting)) {
    return (-1);
  }
  free(line);
  (*number_setting)++;
  return (0);
}

int parse_settings_file(t_viewer *viewer, FILE *file) {
  int read_end;
  int number_setting;

  number_setting = 0;
  read_end = 0;
  while (!read_end)
    read_end = parse_settings_line(viewer, file, &number_setting);
  if (read_end == -1) return (0);
  return (1);
}