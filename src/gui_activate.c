#include "viewer3D.h"

void  gui_activate(t_viewer *viewer, GtkWidget *win)
{
  GtkWidget *box_main;
  GtkWidget *grid;
  GtkWidget *box_model;

  box_main = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  grid = gtk_grid_new();
  gtk_widget_set_size_request(grid, 250, 100);
  box_model = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  viewer->model = gtk_drawing_area_new();
  gtk_window_set_child(GTK_WINDOW(win), box_main);
  gtk_box_append(GTK_BOX(box_main), grid);
  gtk_box_append(GTK_BOX(box_main), box_model);
  gtk_box_append(GTK_BOX(box_model), viewer->model);
  buttons_manager(viewer, grid);
  draw_model(viewer);
}