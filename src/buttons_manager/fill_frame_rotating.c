#include "../viewer3D.h"

static void rotate_all(GtkButton *btn, t_viewer *viewer)
{

    double rotate_value;

    if (viewer->info.make_screenshot != 0)
        return;
    rotate_value = 0;
    rotate_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_x))));
    rotate(viewer, 0, rotate_value);
    rotate_value = 0;
    rotate_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_y))));
    rotate(viewer, 1, rotate_value);
    rotate_value = 0;
    rotate_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_z))));
    rotate(viewer, 2, rotate_value);
    gtk_widget_queue_draw(viewer->model);

}

void fill_frame_rotating(t_viewer *viewer, GtkWidget *box_buttons) {
    GtkWidget *frame;
    GtkWidget *box_rotating;
    GtkWidget *button_rotate_all;

    frame = gtk_frame_new("Rotating model");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    box_rotating = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_rotating);
    input_rotating_x(viewer, box_rotating);
    input_rotating_y(viewer, box_rotating);
    input_rotating_z(viewer, box_rotating);
    button_rotate_all = gtk_button_new_with_label("Rotate all");
    gtk_box_append(GTK_BOX(box_rotating), button_rotate_all);
    g_signal_connect(GTK_BUTTON(button_rotate_all), "clicked", G_CALLBACK(rotate_all), viewer);
}