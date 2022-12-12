#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <cairo/cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <fcntl.h>

typedef struct s_list {
  void *content;
  struct s_list *next;
} t_list;

typedef struct s_plane
{
  ssize_t *indexes; //ex plane
  size_t size; //ex len
} t_plane;

typedef struct s_rgb {
  int red;
  int green;
  int blue;

} t_rgb;

typedef struct s_dimensions
{
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
} t_dimensions;

typedef struct s_camera
{
  double x;
  double y;
  double z;
} t_camera;
typedef struct	s_info
{
  double *vert;
  t_list *faces;
  t_camera camera;
  size_t count_v;
} t_info;

typedef struct s_viewer {
  t_info info;
  t_list *vertex_list;
  t_dimensions dimensions;
  double *p; // точки
  t_list *f; // плоскости
  GtkWidget *model;
  GtkWidget **entry;
} t_viewer;

int parser(const char *s, t_viewer *viewer);
int parse_value(char **line, t_viewer *viewer);
int parse_vertex(char **split_line, t_viewer *viewer);
int parse_face(char **split_line, t_viewer *viewer);
void clean_massive_2d(char ***m);
void  exit_message(char *s);
char **ft_split(char const *s, char c);
size_t ft_lstsize(t_list *lst);
void ft_lstclear(t_list **lst, void (*del)(void *));
void ft_lstdelone(t_list *lst, void (*del)(void *));
t_list *ft_lstnew(void *content);
void ft_lstadd_back(t_list **alst, t_list *new);
int run_app(int argc, char **argv, t_viewer *viewer);
void  gui_activate(t_viewer *viewer, GtkWidget *win);
void  draw_model(t_viewer *viewer);
void  buttons_manager(t_viewer *viewer, GtkWidget *box);

#endif
