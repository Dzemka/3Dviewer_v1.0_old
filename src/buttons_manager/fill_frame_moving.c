#include "../viewer3D.h"

static void move_all(GtkWidget *btn, t_viewer *viewer)
{
    double move_value;

    if (viewer->info.make_screenshot != 0)
        return;
    move_value = 0;
    move_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_x))));
    move(viewer->info.vertexes3d, viewer->info.count_v * 3, X_AXES, move_value);
    move_value = 0;
    move_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_y))));
    move(viewer->info.vertexes3d, viewer->info.count_v * 3, Y_AXES, move_value);
    move_value = 0;
    move_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_z))));
    move(viewer->info.vertexes3d, viewer->info.count_v * 3, Z_AXES, move_value);
    gtk_widget_queue_draw(viewer->model);

}

void fill_frame_moving(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *frame;
    GtkWidget *box_moving;
    GtkWidget *button_move_all;


    frame = gtk_frame_new("Moving model");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    box_moving = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_moving);
    input_moving_x(viewer, box_moving);
    input_moving_y(viewer, box_moving);
    input_moving_z(viewer, box_moving);
    button_move_all = gtk_button_new_with_label("Move all");
    g_signal_connect(GTK_BUTTON(button_move_all), "clicked", G_CALLBACK(move_all), viewer);
    gtk_box_append(GTK_BOX(box_moving), button_move_all);
}