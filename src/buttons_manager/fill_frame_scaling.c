#include "../viewer3D.h"

static void zooming(GtkButton *btn, t_viewer *viewer)
{
    double z;

    if (viewer->info.make_screenshot != 0)
        return;
    z = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_zoom))));
    if (z == 0)
        z = 1;
    zoom(viewer, z);
    gtk_widget_queue_draw(viewer->model);
}

void fill_frame_scaling(t_viewer *viewer, GtkWidget *box_buttons){
    GtkWidget *frame;
    GtkWidget *box_scaling;
    GtkWidget *button_zoom;

    frame = gtk_frame_new("Scaling model");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    box_scaling = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_scaling);
    viewer->entry.entry_zoom = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_zoom), "input size for scaling");
    button_zoom = gtk_button_new_with_label("Zoom");
    gtk_box_append(GTK_BOX(box_scaling), viewer->entry.entry_zoom);
    gtk_box_append(GTK_BOX(box_scaling), button_zoom);
    g_signal_connect(GTK_BUTTON(button_zoom), "clicked", G_CALLBACK(zooming), viewer);
}