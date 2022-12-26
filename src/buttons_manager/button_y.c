#include "../viewer3D.h"

static void rotate_pos(GtkButton *btn, t_viewer *viewer)
{

    double rotate_y;

    rotate_y = 0;
    rotate_y = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_rotate_y))));
//    viewer->info.rad_y = rotate_y;
    rotate(viewer, 1, rotate_y);
}

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
    int move_y;

    move_y = 0;
    move_y = atoi(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->buttons_input.entry_move_y))));
//    viewer->info.move_step = move_y;
    move(viewer, 1, move_y);
}

void  button_y(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *box_move_y;
    GtkWidget *entry_button_move;
    GtkWidget *box_rotate_y;
    GtkWidget *entry_button_rotate;

    box_move_y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_move_y);
    viewer->buttons_input.entry_move_y = gtk_entry_new();
    entry_button_move = gtk_button_new_with_label("Enter move y");
    gtk_box_append(GTK_BOX(box_move_y), viewer->buttons_input.entry_move_y);
    gtk_box_append(GTK_BOX(box_move_y), entry_button_move);
    g_signal_connect(GTK_BUTTON(entry_button_move), "clicked", G_CALLBACK(move_pos), viewer);
    box_rotate_y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_rotate_y);
    viewer->buttons_input.entry_rotate_y = gtk_entry_new();
    entry_button_rotate = gtk_button_new_with_label("Enter rotate y");
    gtk_box_append(GTK_BOX(box_rotate_y), viewer->buttons_input.entry_rotate_y);
    gtk_box_append(GTK_BOX(box_rotate_y), entry_button_rotate);
    g_signal_connect(GTK_BUTTON(entry_button_rotate), "clicked", G_CALLBACK(rotate_pos), viewer);
}