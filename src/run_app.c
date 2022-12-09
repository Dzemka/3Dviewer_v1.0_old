#include "viewer3D.h"
#include <math.h>

typedef struct s_point_2d {
  double x;
  double y;
} t_point_2d;

typedef struct s_point_3d {
  double x;
  double y;
  double z;
} t_point_3d;

static void central_proj(int k, int dist, double **xyz, double **p) {
  int i;

  i = -1;
  while (++i < 8) {
    p[i][0] = k * xyz[i][0] / (xyz[i][2] + dist + k);
    p[i][1] = k * xyz[i][1] / (xyz[i][2] + dist + k);
  }
}

static void scale(double **p, int scale) {
  int i = -1;
  while (++i < 8) {
    p[i][0] *= scale;
    p[i][1] *= scale;
  }
}

static void rotate_z(double **xyz, double angle)
{
  int i = -1;
  double x;
  double y;

  while (++i < 8)
  {
    x = xyz[i][0] * cos(angle) - xyz[i][1] * sin(angle);
    y = xyz[i][0] * sin(angle) + xyz[i][1] * cos(angle);
    xyz[i][0] = x;
    xyz[i][1] = y;
  }
}

static void rotate_x(double **xyz, double angle)
{
  int i = -1;

  double y;
  double z;
  while (++i < 8)
  {
    y = xyz[i][1] * cos(angle) + xyz[i][2] * sin(angle);
    z = xyz[i][1] * - 1 * sin(angle) + xyz[i][2] * cos(angle);
    xyz[i][1] = y;
    xyz[i][2] = z;
  }

}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer user_data) {
  int k;
  double **xyz;
  double **p;
  int i;
  int dist;

  k = 15;
  dist = 20;
  xyz = malloc(sizeof(double *) * 8);
  i = -1;
  while (++i < 8) xyz[i] = malloc(sizeof(double) * 3);
  p = malloc(sizeof(double *) * 8);
  i = -1;
  while (++i < 8) p[i] = malloc(sizeof(double) * 2);
  xyz[0][0] = -1;
  xyz[0][1] = 1;
  xyz[0][2] = 1;

  xyz[1][0] = -1;
  xyz[1][1] = 1;
  xyz[1][2] = -1;

  xyz[2][0] = 1;
  xyz[2][1] = 1;
  xyz[2][2] = -1;

  xyz[3][0] = 1;
  xyz[3][1] = 1;
  xyz[3][2] = 1;

  xyz[4][0] = -1;
  xyz[4][1] = -1;
  xyz[4][2] = 1;

  xyz[5][0] = -1;
  xyz[5][1] = -1;
  xyz[5][2] = -1;

  xyz[6][0] = 1;
  xyz[6][1] = -1;
  xyz[6][2] = -1;

  xyz[7][0] = 1;
  xyz[7][1] = -1;
  xyz[7][2] = 1;

//  rotate_z(xyz, 0.5);
//  rotate_x(xyz, 0.5);
//  rotate_y(xyz, 0.5);
  central_proj(k, dist, xyz, p);
  scale(p, 500);
  int cx = width / 2;
  int cy = height / 2;

  int pos[12][2] = {
      {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},

      {0, 4},
      {1, 5},
      {2, 6},
      {3, 7},

      {4, 5},
      {5,6},
      {6, 7},
      {7, 4}
  };
  int f_point;
  int s_point;
  i = -1;

  while (++i < 12) {
    if (i < 4)
      cairo_set_source_rgb(cr, 255,0,0);
    else if (i < 6)
      cairo_set_source_rgb(cr, 0,255,0);
    else if (i < 8)
      cairo_set_source_rgb(cr, 255,0,255);
    else
      cairo_set_source_rgb(cr, 0,0,255);
    f_point = pos[i][0];
    s_point = pos[i][1];
    cairo_move_to(cr, cx + p[f_point][0], cy + p[f_point][1]);
    cairo_line_to(cr, cx + p[s_point][0], cy + p[s_point][1]);
      cairo_stroke(cr);
  }
}

static void ft_click1(GtkButton *btn, gpointer userdata) {
  g_print("signal 1\n");
}

static void ft_click2(GtkButton *btn, gpointer userdata) {
  g_print("SIGNAL 2\n");
}

static void app_activate(GApplication *app, gpointer user_data) {
  GtkWidget *win;
  GtkWidget *box;
  GtkWidget *btn1;
  GtkWidget *btn2;

  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(win), "Dzemka");
  gtk_window_set_default_size(GTK_WINDOW(win), 1920, 1080);

  GtkWidget *area = gtk_drawing_area_new();
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw_function, NULL,
                                 NULL);
  gtk_window_set_child(GTK_WINDOW(win), area);

  gtk_widget_show(win);
}

static void app_open(GApplication *app, GFile **files, gint n_files,
                     gchar *hint, gpointer user_data) {
  int i;

  i = -1;
  //  while (files[++i])
  //    printf("%s\n", g_file_get_basename (files[0]));
  //    g_print(g_file_get_basename (files[0]));
  write(1, "sdf", 3);
}

int run_app(int argc, char **argv) {
  GtkApplication *app;
  int status;
  gtk_init();
  app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
  g_signal_connect(app, "open", G_CALLBACK(app_open), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return (status);
}