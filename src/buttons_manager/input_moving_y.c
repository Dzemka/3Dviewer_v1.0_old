#include "../viewer3D.h"

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
    int move_value;
    GtkEntryBuffer *buf;

    buf = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_y));
    if (gtk_entry_buffer_get_length(buf) > 7 || viewer->info.make_screenshot != 0)
        return;
    move_value = 0;
    move_value = atoi(gtk_entry_buffer_get_text(buf));
    if (move_value > 0)
    {
        if (viewer->dimensions.y_max + move_value > 1000000)
          return ;
        viewer->dimensions.y_max += move_value;
    }
    if (move_value < 0)
    {
        if (viewer->dimensions.y_min + move_value < -1000000)
          return ;
        viewer->dimensions.y_min += move_value;
    }
    move(viewer->info.vertexes3d, viewer->info.count_v * 3, Y_AXES, move_value);
    gtk_widget_queue_draw(viewer->model);

}

void input_moving_y(t_viewer *viewer, GtkWidget *box_moving)
{
    GtkWidget *box_y;
    GtkWidget *button;

    box_y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_moving), box_y);
    viewer->entry.entry_move_y = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_move_y), "input step for move y");
    button = gtk_button_new_with_label("Move y");
    gtk_box_append(GTK_BOX(box_y), viewer->entry.entry_move_y);
    gtk_box_append(GTK_BOX(box_y), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(move_pos), viewer);
}