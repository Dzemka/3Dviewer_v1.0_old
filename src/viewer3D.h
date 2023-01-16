#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <cairo/cairo.h>
#include <ctype.h>
#include <fcntl.h>
#include <gd.h>
#include <gtk/gtk.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DO_NOTHING 0
#define SCREENSHOT_CREATE 1
#define GIF_CREATE 2
#define NONE_VERTICES 0
#define CIRCLE_VERTICES 1
#define SQUARE_VERTICES 2
#define MIN_EDGE_THICKNESS 0.06
#define MAX_EDGE_THICKNESS 5
#define MIN_VERTICES_SIZE 1
#define MAX_VERTICES_SIZE 10

typedef struct s_list {
  void *content;
  struct s_list *next;
} t_list;

typedef struct s_plane {
  size_t *indexes;
  size_t size;
} t_plane;

typedef struct s_dimensions {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
} t_dimensions;

typedef struct s_camera {
  double x;
  double y;
  double z;
  double screen_z;  // поменять на coefficient_scaling
} t_camera;

typedef struct s_info {
  double width;
  double height;
  double *vertexes2d;
  double *vertexes3d;
  t_list *faces;
  t_camera camera;
  size_t count_v;
  double rad_x;
  double rad_y;
  double rad_z;
  double scale;
  double move_step;
  char *screenshot_format;
  char *screenshot_file_name;
  int make_screenshot;
} t_info;

typedef struct s_settings {
  void (*func_proj)(void *viewer, int width, int height);
  int is_dashed;
  GdkRGBA edge_color;
  double edge_thickness;
  int vertices_type;
  GdkRGBA vertices_color;
  double vertices_size;
  GdkRGBA background_color;
} t_settings;

typedef struct s_entry {
  GtkWidget *entry_file;
  GtkWidget *entry_move_x;
  GtkWidget *entry_move_y;
  GtkWidget *entry_move_z;
  GtkWidget *entry_rotate_x;
  GtkWidget *entry_rotate_y;
  GtkWidget *entry_rotate_z;
  GtkWidget *entry_zoom;
  GtkWidget *entry_screenshot;
  GtkWidget *entry_gif;
  GtkWidget *entry_width;
  GtkWidget *entry_height;
} t_entry;

typedef struct s_viewer {
  char *filename;
  t_settings settings;
  t_info info;
  t_list *vertex_list;
  t_dimensions dimensions;
  GtkWidget *model;
  t_entry entry;
  int png_pause;
  GtkWidget *label_filename;
  t_list *tmp;
  t_list *tmp2;
} t_viewer;

typedef struct s_matrix {
  double x[3];
  double y[3];
  double z[3];
} t_matrix;

int parser(const char *s, t_viewer *viewer);

int parse_values(int *max_point, char **line, t_viewer *viewer);

int parse_vertex(char **split_line, t_viewer *viewer);

int parse_face(int *max_point, char **split_line, t_viewer *viewer);

void  create_stringlabel(char *text, t_viewer *viewer);

void  free_all(t_viewer *viewer);

void set_values(t_viewer *viewer);

char *ft_strjoin(char const *s1, char const *s2);

void clean_massive_2d(char ***m);

void exit_message(char *s);

char **ft_split(char const *s, char c);

size_t ft_lstsize(t_list *lst);

void ft_lstclear(t_list **lst, void (*del)(void *));

void ft_lstdelone(t_list *lst, void (*del)(void *));

t_list *ft_lstnew(void *content);

void ft_lstadd_back(t_list **alst, t_list *

                    new);

int run_app(int argc, char **argv, t_viewer *viewer);

void gui_activate(t_viewer *viewer, GtkWidget *win);

void draw_model(t_viewer *viewer);

void buttons_manager(t_viewer *viewer, GtkWidget *box_left,
                     GtkWidget *box_right);

void rotate(t_viewer *viewer, int axes, double rad);

void zoom(t_viewer *viewer, double scale);

void move(t_viewer *viewer, int axes, double move_step);

void fill_frame_moving(t_viewer *viewer, GtkWidget *box_buttons);

void fill_frame_rotating(t_viewer *viewer, GtkWidget *box_buttons);

void fill_frame_scaling(t_viewer *viewer, GtkWidget *box_buttons);

void input_moving_x(t_viewer *viewer, GtkWidget *box_moving);

void input_moving_y(t_viewer *viewer, GtkWidget *box_moving);

void input_moving_z(t_viewer *viewer, GtkWidget *box_moving);

void input_rotating_x(t_viewer *viewer, GtkWidget *box_rotating);

void input_rotating_y(t_viewer *viewer, GtkWidget *box_rotating);

void input_rotating_z(t_viewer *viewer, GtkWidget *box_rotating);

void button_proj(t_viewer *viewer, GtkWidget *box_buttons);

void set_type_edge(t_viewer *viewer, GtkWidget *box_buttons);

void parallel_proj(void *viewer, int width, int height);

void central_proj(void *viewer, int width, int height);

void set_background_color(t_viewer *viewer, GtkWidget *box_buttons);

void set_color_edge(t_viewer *viewer, GtkWidget *box_buttons);

void set_thickness_edge(t_viewer *viewer, GtkWidget *box_buttons);

void set_type_vertices(t_viewer *viewer, GtkWidget *btn);

void set_color_vertices(t_viewer *viewer, GtkWidget *box_buttons);

void set_size_vertices(t_viewer *viewer, GtkWidget *box_buttons);

void draw_settings(t_viewer *viewer, cairo_t *cr);

void get_screenshot(t_viewer *viewer, cairo_surface_t *surface);

void set_screenshot_frame(t_viewer *viewer, GtkWidget *box);

void set_gif_frame(t_viewer *viewer, GtkWidget *box);

void set_resize_frame(t_viewer *viewer, GtkWidget *box);

void matrix_multiply(double **m1, double **m2);

void matrix_addition(double **m1, double **m2);

void get_matrix_rotate(double **matrix, int axes, double rad);

void get_matrix_scale(double **matrix, double scale);

void get_matrix_move(double **matrix, int axes, double move_step);

void matrix_apply_multiply(double *m1, double **m2, size_t count);

void matrix_apply_addition(double *m1, double **m2, size_t count);

char *ft_itoa(int n);

void *build_gif(t_viewer *viewer);

void  save_settings(t_viewer *viewer);

void get_settings(t_viewer *viewer);

int parse_settings_file(t_viewer *viewer, FILE *file);

#endif
