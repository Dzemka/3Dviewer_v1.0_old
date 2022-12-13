#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{
  viewer->info.rad_x = fabs(viewer->info.rad_x);
  rotate(viewer, 0, viewer->info.rad_x);
}

static void rotate_neg(GtkButton *btn, t_viewer *viewer)
{
  viewer->info.rad_x = -fabs(viewer->info.rad_x);
  rotate(viewer, 0, viewer->info.rad_x);
}

void  button_x(t_viewer *viewer, GtkWidget *grid)
{

  GtkWidget *button_rotate_pos;
  GtkWidget *button_rotate_neg;

  button_rotate_pos = gtk_button_new_with_label("x >");
  gtk_grid_attach(GTK_GRID(grid), button_rotate_pos, 0, 3, 2, 1);
  g_signal_connect(GTK_BUTTON(button_rotate_pos), "clicked", G_CALLBACK(rotate_pos), viewer);
  button_rotate_neg = gtk_button_new_with_label("x <");
  gtk_grid_attach(GTK_GRID(grid), button_rotate_neg, 3, 3, 2, 1);
  g_signal_connect(GTK_BUTTON(button_rotate_neg), "clicked", G_CALLBACK(rotate_neg), viewer);
}