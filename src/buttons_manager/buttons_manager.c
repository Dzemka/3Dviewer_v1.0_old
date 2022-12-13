#include "../viewer3D.h"

static void enter(GtkButton *btn, t_viewer *viewer) {
  const char *s;

  s = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(*viewer->entry)));
  //подготовить особождение перед открытием нового файла
  parser(s, viewer);
}

static void button_transformation(t_viewer *viewer, GtkWidget *grid)
{


  viewer->info.rad_x = 0.5;
  viewer->info.rad_y = 0.5;
  viewer->info.rad_z = 0.5;
  viewer->info.scale = 2.0;
  viewer->info.move_step = 1;

  button_x(viewer, grid);
  button_y(viewer, grid);
  button_z(viewer, grid);
  button_zoom(viewer, grid);

}

void buttons_manager(t_viewer *viewer, GtkWidget *grid)
{
  GtkWidget *button;
  viewer->entry = malloc(sizeof (void *));

  button_transformation(viewer, grid);

  *viewer->entry = gtk_entry_new();
  button = gtk_button_new_with_label("Enter");
  gtk_grid_attach(GTK_GRID(grid), *viewer->entry, 0, 0, 6, 1);
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 6, 1);
  g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(enter), viewer);
}