#include "../viewer3D.h"

static void move_pos(GtkButton *btn, t_viewer *viewer)
{
    double move_value;

    if (viewer->info.make_screenshot != 0)
        return;
    move_value = 0;
    move_value = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_x))));
    printf("%f\n", move_value);
    move(viewer, 0, move_value);
    gtk_widget_queue_draw(viewer->model);

}

void input_moving_x(t_viewer *viewer, GtkWidget *box_moving)
{
    GtkWidget *box_x;
    GtkWidget *button;

    box_x = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_moving), box_x);
    viewer->entry.entry_move_x = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_move_x), "input step for move x");
    button = gtk_button_new_with_label("Move x");
    gtk_box_append(GTK_BOX(box_x), viewer->entry.entry_move_x);
    gtk_box_append(GTK_BOX(box_x), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(move_pos), viewer);
}