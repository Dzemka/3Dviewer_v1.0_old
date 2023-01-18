#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{
    double rotate_value;
    GtkEntryBuffer *buf;

    buf = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_y));
    if (gtk_entry_buffer_get_length(buf) > 7 || viewer->info.make_screenshot != 0)
      return;
    rotate_value = 0;
    rotate_value = atof(gtk_entry_buffer_get_text(buf));
    rotate(viewer->info.vertexes3d, viewer->info.count_v * 3, Y_AXES, rotate_value);
    gtk_widget_queue_draw(viewer->model);

}

void input_rotating_y(t_viewer *viewer, GtkWidget *box_rotating) {
    GtkWidget *box_y;
    GtkWidget *button;

    box_y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_rotating), box_y);
    viewer->entry.entry_rotate_y = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_rotate_y), "input degree for rotate y");
    button = gtk_button_new_with_label("Rotate y");
    gtk_box_append(GTK_BOX(box_y), viewer->entry.entry_rotate_y);
    gtk_box_append(GTK_BOX(box_y), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(rotate_pos), viewer);
}