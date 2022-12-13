#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{
  viewer->info.rad_y = fabs(viewer->info.rad_y);
  rotate(viewer, 1, viewer->info.rad_y);
}

static void rotate_neg(GtkButton *btn, t_viewer *viewer)
{
  viewer->info.rad_y = -fabs(viewer->info.rad_y);
  rotate(viewer, 1, viewer->info.rad_y);
}

void  button_y(t_viewer *viewer, GtkWidget *grid)
{

  GtkWidget *button_rotate_pos;
  GtkWidget *button_rotate_neg;

  button_rotate_pos = gtk_button_new_with_label("y >");
  gtk_grid_attach(GTK_GRID(grid), button_rotate_pos, 0, 4, 2, 1);
  g_signal_connect(GTK_BUTTON(button_rotate_pos), "clicked", G_CALLBACK(rotate_pos), viewer);
  button_rotate_neg = gtk_button_new_with_label("y <");
  gtk_grid_attach(GTK_GRID(grid), button_rotate_neg, 3, 4, 2, 1);
  g_signal_connect(GTK_BUTTON(button_rotate_neg), "clicked", G_CALLBACK(rotate_neg), viewer);
}