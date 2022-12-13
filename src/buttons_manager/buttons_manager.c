#include "../viewer3D.h"

static void enter(GtkButton *btn, t_viewer *viewer) {
  const char *s;

  s = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(*viewer->entry)));
  //подготовить особождение перед открытием нового файла
  parser(s, viewer);
}

static void button_transformation(t_viewer *viewer, GtkWidget *grid)
{
  GtkWidget *button_scale;

  viewer->info.rad_x = 0.5;
  viewer->info.rad_y = 0.5;
  viewer->info.rad_z = 0.5;
  viewer->info.scale = 2;

  button_x(viewer, grid);
  button_y(viewer, grid);
  button_z(viewer, grid);
  button_scale = gtk_button_new_with_label("zoom in");
  gtk_grid_attach(GTK_GRID(grid), button_scale, 0, 6, 2, 1);
  g_signal_connect(button_scale, "clicked", G_CALLBACK(scale), viewer);
  button_scale = gtk_button_new_with_label("zoom out");

}

void buttons_manager(t_viewer *viewer, GtkWidget *grid)
{
  GtkWidget *button;
  viewer->entry = malloc(sizeof (void *));

  *viewer->entry = gtk_entry_new();
  button = gtk_button_new_with_label("Enter");
  button_transformation(viewer, grid);
  gtk_grid_attach(GTK_GRID(grid), *viewer->entry, 0, 0, 6, 1);
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 6, 1);
  g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(enter), viewer);
}