#include "viewer3D.h"

static void enter(GtkButton *btn, t_viewer *viewer) {
  const char *s;

  s = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(*viewer->entry)));
//  parser(s, viewer);
}

void buttons_manager(t_viewer *viewer, GtkWidget *box)
{
  GtkWidget *button;
  viewer->entry = malloc(sizeof (void *));

  *viewer->entry = gtk_entry_new();
  button = gtk_button_new_with_label("Enter");
  gtk_box_append(GTK_BOX(box), *viewer->entry);
  gtk_box_append(GTK_BOX(box), button);
  g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(enter), viewer);
}