#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{

    double rotate_z;

    rotate_z = 0;
    rotate_z = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_rotate_z))));
//    viewer->info.rad_x = rotate_z;
    rotate(viewer, 2, rotate_z);
}

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
    int move_z;

    move_z = 0;
    move_z = atoi(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_move_z))));
//    viewer->info.move_step = move_z;
    move(viewer, 2, move_z);
}

void  button_z(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *box_move_z;
    GtkWidget *entry_button_move;
    GtkWidget *box_rotate_z;
    GtkWidget *entry_button_rotate;

    box_move_z = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_move_z);
    viewer->buttons_input.entry_move_z = gtk_entry_new();
    entry_button_move = gtk_button_new_with_label("Enter move z");
    gtk_box_append(GTK_BOX(box_move_z), viewer->buttons_input.entry_move_z);
    gtk_box_append(GTK_BOX(box_move_z), entry_button_move);
    g_signal_connect(GTK_BUTTON(entry_button_move), "clicked", G_CALLBACK(move_pos), viewer);
    box_rotate_z = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_rotate_z);
    viewer->buttons_input.entry_rotate_z = gtk_entry_new();
    entry_button_rotate = gtk_button_new_with_label("Enter rotate z");
    gtk_box_append(GTK_BOX(box_rotate_z), viewer->buttons_input.entry_rotate_z);
    gtk_box_append(GTK_BOX(box_rotate_z), entry_button_rotate);
    g_signal_connect(GTK_BUTTON(entry_button_rotate), "clicked", G_CALLBACK(rotate_pos), viewer);
}