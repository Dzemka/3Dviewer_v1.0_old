#include "../viewer3D.h"

static void resize(GtkWidget *btn, t_viewer *viewer)
{
    GtkEntryBuffer *buf_width;
    GtkEntryBuffer *buf_height;
    double old_width;
    double old_height;
    double k;

    if (viewer->info.make_screenshot != 0)
        return;
    old_width = viewer->info.width;
    old_height = viewer->info.height;
    buf_width = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_width));
    viewer->info.width = atoi(gtk_entry_buffer_get_text(buf_width));
    buf_height = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_height));
    viewer->info.height = atoi(gtk_entry_buffer_get_text(buf_height));
    if (gtk_entry_buffer_get_length(buf_width) == 0 && gtk_entry_buffer_get_length(buf_height) == 0)
        return;
    if (viewer->info.width < 640)
    {
        viewer->info.width = 640;
        gtk_entry_buffer_set_text(buf_width, "640", 3);
    }
    if (viewer->info.width > 1360) {
        viewer->info.width = 1360;
        gtk_entry_buffer_set_text(buf_width, "1920", 4);
    }
    if (viewer->info.height < 480)
    {
        viewer->info.height = 480;
        gtk_entry_buffer_set_text(buf_height, "480", 3);
    }
    if (viewer->info.height > 1000)
    {
        viewer->info.height = 1000;
        gtk_entry_buffer_set_text(buf_height, "1000", 4);
    }
    k = viewer->info.width / old_width;
    zoom(viewer->info.vertexes3d, viewer->info.count_v * 3, k);
    gtk_widget_set_size_request(viewer->model, viewer->info.width, viewer->info.height);
    gtk_widget_queue_draw(viewer->model);
}

void set_resize_frame(t_viewer *viewer, GtkWidget *box)
{
    GtkWidget *frame;
    GtkWidget *box_resize;
    GtkWidget *button;

    frame = gtk_frame_new("Resize");
    gtk_box_append(GTK_BOX(box), frame);
    box_resize = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_resize);
    viewer->entry.entry_width = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_width), "Enter width");
    viewer->entry.entry_height = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_height), "Enter height");
    button = gtk_button_new_with_label("Resize");
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(resize), viewer);
    gtk_box_append(GTK_BOX(box_resize), viewer->entry.entry_width);
    gtk_box_append(GTK_BOX(box_resize), viewer->entry.entry_height);
    gtk_box_append(GTK_BOX(box_resize), button);
}