#include "../viewer3D.h"

static int relevant_file(const char *s) {
  int i;

  i = strlen(s) - 4;
  return (s[i] == '.' && s[i + 1] == 'o' && s[i + 2] == 'b' &&
          s[i + 3] == 'j');
}

static FILE *get_file(const char *s) {
  FILE *file;

  if (!relevant_file(s)) {
    printf("file is not in obj format\n");
    return (NULL);
  }
  file = fopen(s, "r");
  if (!file) {
    printf("cannot open file\n");
    return (NULL);
  }
  return (file);
}

int parse_values(char **line, t_viewer *viewer) {
  char **split_line;
  int status;

  split_line = ft_split((*line) + 2, ' ');
  if ((*line)[0] == 'v')
    status = parse_vertex(split_line, viewer);
  else
    status = parse_face(split_line, viewer);
  free(*line);
  clean_massive_2d(&split_line);
  return (status);
}

// returns : error(-1), read_end(1), reads(0)
static int parse_file(FILE *file, t_viewer *viewer) {
  char *line;
  size_t len;

  line = NULL;
  errno = 0;
  if (getline(&line, &len, file) == -1) {
    if (errno) {
      return (-1);
    }
    return (1);
  }
  if (len > 2) {
    if ((line[0] == 'v' || line[0] == 'f') && line[1] == ' ')
      return (parse_values(&line, viewer));
  }
  return (0);
}

int parser(const char *s, t_viewer *viewer) {
  FILE *file;
  int read_end;

  file = get_file(s);
  if (!file) return (1);
  read_end = 0;
  while (!read_end) read_end = parse_file(file, viewer);
  fclose(file);
  if (read_end == -1) return (1);
  // куда-нибудь засунуть
  viewer->info.vertexes3d = malloc(sizeof(double) * viewer->info.count_v * 3);
  viewer->info.vertexes2d = malloc(sizeof(double) * viewer->info.count_v * 2);
  // всё что между комментариями
  set_values(viewer);
  return (0);
}