#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{

    double rotate_x;

    rotate_x = 0;
    rotate_x = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_rotate_x))));
    viewer->info.rad_x = rotate_x;
    rotate(viewer, 0, rotate_x);
}

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
    int move_x;

    move_x = 0;
    move_x = atoi(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_move_x))));
//    viewer->info.move_step = move_x;
    move(viewer, 0, move_x);
}

void  button_x(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *box_move_x;
    GtkWidget *entry_button_move;
    GtkWidget *box_rotate_x;
    GtkWidget *entry_button_rotate;

    box_move_x = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_move_x);
    viewer->buttons_input.entry_move_x = gtk_entry_new();
    entry_button_move = gtk_button_new_with_label("Enter move x");
    gtk_box_append(GTK_BOX(box_move_x), viewer->buttons_input.entry_move_x);
    gtk_box_append(GTK_BOX(box_move_x), entry_button_move);
    g_signal_connect(GTK_BUTTON(entry_button_move), "clicked", G_CALLBACK(move_pos), viewer);
    box_rotate_x = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_rotate_x);
    viewer->buttons_input.entry_rotate_x = gtk_entry_new();
    entry_button_rotate = gtk_button_new_with_label("Enter rotate x");
    gtk_box_append(GTK_BOX(box_rotate_x), viewer->buttons_input.entry_rotate_x);
    gtk_box_append(GTK_BOX(box_rotate_x), entry_button_rotate);
    g_signal_connect(GTK_BUTTON(entry_button_rotate), "clicked", G_CALLBACK(rotate_pos), viewer);
}