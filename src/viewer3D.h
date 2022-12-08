#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <cairo/cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <graphene.h>

typedef struct s_planes {
//  t_point
} t_plane;

typedef struct s_rgb {
  int red;
  int green;
  int blue;

} t_rgb;

typedef struct s_viewer {
  double line_height;
  t_rgb color;
} t_viewer;

int run_app(int argc, char **argv);

#endif