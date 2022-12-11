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

typedef struct s_planes {
//  t_point
} t_plane;

typedef struct s_rgb {
  int red;
  int green;
  int blue;

} t_rgb;

typedef struct s_viewer {
  double *p; // точки
  t_list *f; // плоскости
  int count_point;
  GtkWidget *model;
  GtkWidget **entry;
} t_viewer;

void  parser(char *s, t_viewer *viewer);
int run_app(int argc, char **argv, t_viewer *viewer);
void  gui_activate(t_viewer *viewer, GtkWidget *win);
void  draw_model(t_viewer *viewer);
void  buttons_manager(t_viewer *viewer, GtkWidget *box);

#endif
