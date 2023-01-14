#include "../viewer3D.h"

static void select_solid_type(GtkButton *btn, t_viewer *viewer) {
  if (viewer->info.make_screenshot != 0) return;
  viewer->settings.is_dashed = FALSE;
  gtk_widget_queue_draw(viewer->model);
}

static void select_dashed_type(GtkButton *btn, t_viewer *viewer) {
  if (viewer->info.make_screenshot != 0) return;
  viewer->settings.is_dashed = TRUE;
  gtk_widget_queue_draw(viewer->model);
}

void set_type_edge(t_viewer *viewer, GtkWidget *box_buttons) {
  GtkWidget *frame;
  GtkWidget *box_proj;
  GtkWidget *button_solid;
  GtkWidget *button_dashed;

  frame = gtk_frame_new("Select type edge");
  gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
  gtk_box_append(GTK_BOX(box_buttons), frame);
  box_proj = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_frame_set_child(GTK_FRAME(frame), box_proj);

  button_solid = gtk_check_button_new_with_label("Solid");
  gtk_check_button_set_active(GTK_CHECK_BUTTON(button_solid), TRUE);
  gtk_box_append(GTK_BOX(box_proj), button_solid);
  g_signal_connect(GTK_CHECK_BUTTON(button_solid), "toggled",
                   G_CALLBACK(select_solid_type), viewer);
  button_dashed = gtk_check_button_new_with_label("Dashed");
  gtk_check_button_set_group(GTK_CHECK_BUTTON(button_dashed),
                             GTK_CHECK_BUTTON(button_solid));
  gtk_box_append(GTK_BOX(box_proj), button_dashed);
  g_signal_connect(GTK_CHECK_BUTTON(button_dashed), "toggled",
                   G_CALLBACK(select_dashed_type), viewer);
}