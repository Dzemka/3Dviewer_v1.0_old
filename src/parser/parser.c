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

int parse_values(int *max_point, char **line, t_viewer *viewer) {
  char **split_line;
  int status;

  split_line = ft_split((*line) + 2, ' ');
  if ((*line)[0] == 'v')
    status = parse_vertex(split_line, viewer);
  else
    status = parse_face(max_point, split_line, viewer);
  free(*line);
  clean_massive_2d(&split_line);
  return (status);
  // return (0);
}

// returns : error(-1), read_end(1), reads(0)
static int parse_file(int *max_point, FILE *file, t_viewer *viewer) {
  char *line;
  size_t len;

  line = NULL;
  len = 0;//добавил
  errno = 0;
  if (getline(&line, &len, file) == -1) {
    free(line);//добавить!!!
    if (errno) {
      return (-1);
    }
    return (1);
  }
  // printf("%ld %s", len, line);
  if (len > 2) {
    if ((line[0] == 'v' || line[0] == 'f') && line[1] == ' ')
      return (parse_values(max_point, &line, viewer));
  }
  free(line);//добавить
  return (0);
}

int parser(const char *s, t_viewer *viewer) {
  FILE *file;
  int read_end;
  int max_point;

  file = get_file(s);
  if (!file) return (1);
  read_end = 0;
  max_point = 0;
  while (!read_end) read_end = parse_file(&max_point, file, viewer);
  fclose(file);
  if (read_end == -1) return (1);
  // printf("%d %ld\n", max_point, viewer->info.count_v);
  if (max_point > viewer->info.count_v) return (1);
  // if (read_end == 2) return (2);//доделать условие???

  // // куда-нибудь засунуть
  // viewer->info.vertexes3d = malloc(sizeof(double) * viewer->info.count_v * 3);
  // viewer->info.vertexes2d = malloc(sizeof(double) * viewer->info.count_v * 2);
  // // всё что между комментариями
  // set_values(viewer);
  return (0);
}