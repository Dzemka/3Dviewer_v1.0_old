#include "../viewer3D.h"

static void enter(GtkButton *btn, t_viewer *viewer) {
    const char *s;

    s = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_file)));
    //подготовить особождение перед открытием нового файла
    parser(s, viewer);
}

static void button_transformation(t_viewer *viewer, GtkWidget *box_buttons) {


    viewer->info.rad_x = 0.5;
    viewer->info.rad_y = 0.5;
    viewer->info.rad_z = 0.5;
    viewer->info.scale = 2.0;
    viewer->info.move_step = 1;

    button_x(viewer, box_buttons);
    button_y(viewer, box_buttons);
    button_z(viewer, box_buttons);
    button_zoom(viewer, box_buttons);

}

void button_entry_file(t_viewer *viewer, GtkWidget *box_buttons) {
    GtkWidget *box_entry;
    GtkWidget *entry;
    GtkWidget *button_entry;

//    viewer->entry = malloc(sizeof(void *));

    box_entry = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    viewer->buttons_input.entry_file = gtk_entry_new();
    button_entry = gtk_button_new_with_label("Enter file");
    gtk_box_append(GTK_BOX(box_buttons), viewer->buttons_input.entry_file);
    gtk_box_append(GTK_BOX(box_buttons), button_entry);
    g_signal_connect(GTK_BUTTON(button_entry), "clicked", G_CALLBACK(enter), viewer);

}

void buttons_manager(t_viewer *viewer, GtkWidget *box_buttons) {
    GtkWidget *view;
    GtkTextBuffer *buffer;

    button_entry_file(viewer, box_buttons);
    button_transformation(viewer, box_buttons);
    button_proj(viewer, box_buttons);
}