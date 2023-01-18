#include "../viewer3D.h"

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
    int move_value;
    GtkEntryBuffer *buf;

    buf = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_z));
    if (gtk_entry_buffer_get_length(buf) > 8 || viewer->info.make_screenshot != 0)
      return;
    if (viewer->info.make_screenshot != 0)
        return;
    move_value = 0;
    move_value = atoi(gtk_entry_buffer_get_text(buf));
    if (move_value > 0)
    {
        if (viewer->dimensions.z_max + move_value > 1000000)
          return ;
        viewer->dimensions.z_max += move_value;
    }
    if (move_value < 0)
    {
        if (viewer->dimensions.z_min + move_value < -1000000)
          return ;
        viewer->dimensions.z_min += move_value;
    }
    move(viewer->info.vertexes3d, viewer->info.count_v * 3, Z_AXES, move_value);
    gtk_widget_queue_draw(viewer->model);
}

void input_moving_z(t_viewer *viewer, GtkWidget *box_moving)
{
    GtkWidget *box_z;
    GtkWidget *button;

    box_z = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_moving), box_z);
    viewer->entry.entry_move_z = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_move_z), "input step for move z");
    button = gtk_button_new_with_label("Move z");
    gtk_box_append(GTK_BOX(box_z), viewer->entry.entry_move_z);
    gtk_box_append(GTK_BOX(box_z), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(move_pos), viewer);
}