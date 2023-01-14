#include "../viewer3D.h"

static void set_thickness(GtkWidget *btn, t_viewer *viewer) {
  if (viewer->info.make_screenshot != 0) return;
  viewer->settings.edge_thickness = gtk_range_get_value(GTK_RANGE(btn));
  gtk_widget_queue_draw(viewer->model);
}

void set_thickness_edge(t_viewer *viewer, GtkWidget *box_buttons) {
  GtkWidget *frame;
  GtkWidget *thickness_box;
  GtkWidget *thickness_scale;

  frame = gtk_frame_new("Select thickness of edge");
  gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
  gtk_box_append(GTK_BOX(box_buttons), frame);
  thickness_scale = gtk_scale_new_with_range(
      GTK_ORIENTATION_HORIZONTAL, MIN_EDGE_THICKNESS, MAX_EDGE_THICKNESS, 0.5);
  gtk_frame_set_child(GTK_FRAME(frame), thickness_scale);
  g_signal_connect_after(GTK_SCALE(thickness_scale), "value-changed",
                         G_CALLBACK(set_thickness), viewer);
}