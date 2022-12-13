#include "../viewer3D.h"

static void zoom_in(GtkButton *btn, t_viewer *viewer)
{
  zoom(viewer, viewer->info.scale);
}

static void zoom_out(GtkButton *btn, t_viewer *viewer)
{
  zoom(viewer, 1 / viewer->info.scale);
}

void button_zoom(t_viewer *viewer, GtkWidget *grid)
{
  GtkWidget *button_zoom_in;
  GtkWidget *button_zoom_out;

  button_zoom_in = gtk_button_new_with_label("zoom in");
  g_signal_connect(button_zoom_in, "clicked", G_CALLBACK(zoom_in), viewer);
  gtk_grid_attach(GTK_GRID(grid), button_zoom_in, 0, 6, 2, 1);
  button_zoom_out = gtk_button_new_with_label("zoom out");
  g_signal_connect(button_zoom_out, "clicked", G_CALLBACK(zoom_out), viewer);
  gtk_grid_attach(GTK_GRID(grid), button_zoom_out, 3, 6, 2, 1);
}