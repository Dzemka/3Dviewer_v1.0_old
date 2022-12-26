#include "../viewer3D.h"

static void zooming(GtkButton *btn, t_viewer *viewer)
{
    double z;

    z = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_zoom))));
    if (z == 0)
        z = 1;
    zoom(viewer, z);
}

void button_zoom(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *box_zoom;
    GtkWidget *button_zoom;

    box_zoom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_zoom);
    viewer->buttons_input.entry_zoom = gtk_entry_new();
    button_zoom = gtk_button_new_with_label("Enter zoom");
    gtk_box_append(GTK_BOX(box_zoom), viewer->buttons_input.entry_zoom);
    gtk_box_append(GTK_BOX(box_zoom), button_zoom);
    g_signal_connect(GTK_BUTTON(button_zoom), "clicked", G_CALLBACK(zooming), viewer);
}