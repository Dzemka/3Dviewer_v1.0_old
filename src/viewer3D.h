#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <cairo/cairo.h>
#include <fcntl.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_list {
    void *content;
    struct s_list *next;
} t_list;

typedef struct s_plane {
    ssize_t *indexes;
    size_t size;
} t_plane;

typedef struct s_rgb {
    int red;
    int green;
    int blue;

} t_rgb;

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
} t_camera;

typedef struct s_info {
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
} t_info;

typedef struct s_buttons_input {
    GtkWidget *entry_file;
    GtkWidget *entry_move_x;
    GtkWidget *entry_move_y;
    GtkWidget *entry_move_z;
    GtkWidget *entry_rotate_x;
    GtkWidget *entry_rotate_y;
    GtkWidget *entry_rotate_z;
    GtkWidget *entry_zoom;

} t_buttons_input;

typedef struct s_viewer {
    t_info info;
    t_list *vertex_list;
    t_dimensions dimensions;
    double *p;  // точки
    t_list *f;  // плоскости
    GtkWidget *model;
//  GtkWidget *entry;
    t_buttons_input buttons_input;

    void (*func_proj)(struct s_viewer *viewer, int width, int height);
} t_viewer;

int parser(const char *s, t_viewer *viewer);

int parse_value(char **line, t_viewer *viewer);

int parse_vertex(char **split_line, t_viewer *viewer);

int parse_face(char **split_line, t_viewer *viewer);

void set_values(t_viewer *viewer);

void clean_massive_2d(char ***m);

void exit_message(char *s);

char **ft_split(char const *s, char c);

size_t ft_lstsize(t_list *lst);

void ft_lstclear(t_list **lst, void (*del)(void *));

void ft_lstdelone(t_list *lst, void (*del)(void *));

t_list *ft_lstnew(void *content);

void ft_lstadd_back(t_list **alst, t_list *new);

int run_app(int argc, char **argv, t_viewer *viewer);

void gui_activate(t_viewer *viewer, GtkWidget *win);

void draw_model(t_viewer *viewer);

void buttons_manager(t_viewer *viewer, GtkWidget *box);

void button_x(t_viewer *viewer, GtkWidget *box_buttons);

void rotate(t_viewer *viewer, int axes, double rad);

void zoom(t_viewer *viewer, double scale);

void move(t_viewer *viewer, int axes, double move_step);

void button_zoom(t_viewer *viewer, GtkWidget *box_buttons);

void button_y(t_viewer *viewer, GtkWidget *box_buttons);

void button_z(t_viewer *viewer, GtkWidget *box_buttons);

void button_proj(t_viewer *viewer, GtkWidget *box_buttons);

void parallel_proj(t_viewer *viewer, int width, int height);

void central_proj(t_viewer *viewer, int width, int height);

#endif
