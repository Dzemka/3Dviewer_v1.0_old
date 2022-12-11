#include "viewer3D.h"

typedef struct s_point_2d {
  double x;
  double y;
} t_point_2d;

typedef struct s_point_3d {
  double x;
  double y;
  double z;
} t_point_3d;

static void central_proj(int k, int dist, double *xyz, double **p, int count) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (i < count) {
//    printf("%d\n", j);
    p[j][0] = k * xyz[i + 0] / (xyz[i + 2] + dist + k);
    p[j][1] = k * xyz[i + 1] / (xyz[i + 2] + dist + k);
    i += 3;
    j++;
  }
}

static void scale(double **p, int scale, int count) {
  int i = -1;
  while (++i < count) {
    p[i][0] *= scale;
    p[i][1] *= scale;
  }
}

static void rotate_z(double *xyz, double angle, int count) {
  int i = 0;
  double x;
  double y;

  while (i < count) {
    x = xyz[i + 0] * cos(angle) - xyz[i + 1] * sin(angle);
    y = xyz[i + 0] * sin(angle) + xyz[i + 1] * cos(angle);
    xyz[i + 0] = x;
    xyz[i + 1] = y;
    i += 3;
  }
}

static void rotate_x(double *xyz, double angle, int count) {
  int i = -1;

  double y;
  double z;
  while (++i < count) {
    y = xyz[i + 1] * cos(angle) + xyz[i + 2] * sin(angle);
    z = xyz[i + 1] * -1 * sin(angle) + xyz[i + 2] * cos(angle);
    xyz[i + 1] = y;
    xyz[i + 2] = z;
    i += 3;
  }
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer pointer ) {
  int k;
  double **xyz;
  double **p;
  int i;
  int dist;
  t_viewer *viewer;

  viewer = pointer;

  k = 15;
  dist = 20;
//  xyz = malloc(sizeof(double *) * 8);
//  i = -1;
//  while (++i < 8) xyz[i] = malloc(sizeof(double) * 3);
  p = malloc(sizeof(double *) * viewer->count_point);
  i = -1;
  while (++i < viewer->count_point) p[i] = malloc(sizeof(double) * 2);
//  xyz[0][0] = -1;
//  xyz[0][1] = 1;
//  xyz[0][2] = 1;
//
//  xyz[1][0] = -1;
//  xyz[1][1] = 1;
//  xyz[1][2] = -1;
//
//  xyz[2][0] = 1;
//  xyz[2][1] = 1;
//  xyz[2][2] = -1;
//
//  xyz[3][0] = 1;
//  xyz[3][1] = 1;
//  xyz[3][2] = 1;
//
//  xyz[4][0] = -1;
//  xyz[4][1] = -1;
//  xyz[4][2] = 1;
//
//  xyz[5][0] = -1;
//  xyz[5][1] = -1;
//  xyz[5][2] = -1;
//
//  xyz[6][0] = 1;
//  xyz[6][1] = -1;
//  xyz[6][2] = -1;
//
//  xyz[7][0] = 1;
//  xyz[7][1] = -1;
//  xyz[7][2] = 1;

//  double angle;

//  angle = 0.5;

  //    rotate_y(xyz, 0.5);
//  rotate_x(viewer->p, 0.5, viewer->count_point);
//  rotate_z(viewer->p, 0.5, viewer->count_point);
  central_proj(k, dist, viewer->p, p, viewer->count_point);

  scale(p, 40, viewer->count_point);
  int cx = width / 2;
  int cy = height / 2;
//
//  int pos[12][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0},
//
//                    {0, 4}, {1, 5}, {2, 6}, {3, 7},
//
//                    {4, 5}, {5, 6}, {6, 7}, {7, 4}};

  int p1;
  int p2;
  int p3;
  int p4;
  t_list *list;

  list = viewer->f;
//    cairo_set_source_rgb(cr, 255, 255, 255);
//    cairo_rectangle(cr, 0, 0, width, height);
//    cairo_fill(cr);
  i = -1;

  int r_color = 0;
  int g_color = 128;
  int b_color = 256;
  cairo_set_source_rgb(cr, 128, 5, 60);

  while (++i < viewer->count_point && list) {

//    printf("%d\n", i);
//    if (i < 4)
//      cairo_set_source_rgb(cr, 255, 0, 0);
//    else if (i < 6)
//      cairo_set_source_rgb(cr, 0, 255, 0);
//    else if (i < 8)
//      cairo_set_source_rgb(cr, 255, 0, 255);
//    else
//      cairo_set_source_rgb(cr, 0, 0, 255);

    p1 = ((int *)list->content)[0];
    p2 = ((int *)list->content)[1];
    p3 = ((int *)list->content)[2];
    p4 = ((int *)list->content)[3];
    cairo_move_to(cr, cx + p[p1][0], cy + p[p1][1]);
    cairo_line_to(cr, cx + p[p2][0], cy + p[p2][1]);
    cairo_line_to(cr, cx + p[p3][0], cy + p[p3][1]);
    if (p4)
      cairo_line_to(cr, cx + p[p4][0], cy + p[p4][1]);
    cairo_line_to(cr, cx + p[p1][0], cy + p[p1][1]);

    list = list->next;
//    cairo_fill(cr);
    cairo_stroke(cr);
  }
}

void  draw_model(t_viewer *viewer)
{
  gtk_widget_set_size_request(viewer->model, 1000, 1000);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(viewer->model), draw_function, viewer,
                                 NULL);
}