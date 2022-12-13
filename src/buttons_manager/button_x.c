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

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
  printf("%f\n", viewer->info.move_step);
  move(viewer, 0, -viewer->info.move_step);
}

static void move_neg(GtkButton *btn, t_viewer *viewer)
{

  move(viewer, 0, viewer->info.move_step);
}

void  button_x(t_viewer *viewer, GtkWidget *grid)
{

  GtkWidget *button_rotate_pos;
  GtkWidget *button_rotate_neg;
  GtkWidget *button_move_pos;
  GtkWidget *button_move_neg;

  button_rotate_pos = gtk_button_new_with_label("x >");
  gtk_grid_attach(GTK_GRID(grid), button_rotate_pos, 0, 3, 2, 1);
  g_signal_connect(GTK_BUTTON(button_rotate_pos), "clicked", G_CALLBACK(rotate_pos), viewer);

  button_rotate_neg = gtk_button_new_with_label("x <");
  gtk_grid_attach(GTK_GRID(grid), button_rotate_neg, 3, 3, 2, 1);
  g_signal_connect(GTK_BUTTON(button_rotate_neg), "clicked", G_CALLBACK(rotate_neg), viewer);

  button_move_pos = gtk_button_new_with_label("move x pos");
  gtk_grid_attach(GTK_GRID(grid), button_move_pos, 0, 7, 6, 1);
  g_signal_connect(GTK_BUTTON(button_move_pos), "clicked", G_CALLBACK(move_pos), viewer);

  button_move_neg = gtk_button_new_with_label("move x neg");
  gtk_grid_attach(GTK_GRID(grid), button_move_neg, 0, 8, 6, 1);
  g_signal_connect(GTK_BUTTON(button_move_neg), "clicked", G_CALLBACK(move_neg), viewer);
}