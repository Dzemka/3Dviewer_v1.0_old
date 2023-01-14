#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{

    double rotate_value;

    if (viewer->info.make_screenshot != 0)
        return;
    rotate_value = 0;
    rotate_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_z)))) * M_PI / 180;
    viewer->info.rad_x = rotate_value;
    rotate(viewer, 2, rotate_value);
    gtk_widget_queue_draw(viewer->model);

}

void input_rotating_z(t_viewer *viewer, GtkWidget *box_rotating) {
    GtkWidget *box_z;
    GtkWidget *button;

    box_z = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_rotating), box_z);
    viewer->entry.entry_rotate_z = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_rotate_z), "input degree for rotate z");
    button = gtk_button_new_with_label("Rotate z");
    gtk_box_append(GTK_BOX(box_z), viewer->entry.entry_rotate_z);
    gtk_box_append(GTK_BOX(box_z), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(rotate_pos), viewer);
}