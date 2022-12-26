#include "../viewer3D.h"

static void select_central_proj(GtkButton *btn, t_viewer *viewer)
{
    viewer->func_proj = &central_proj;
    gtk_widget_queue_draw(viewer->model);

}

static void select_parallel_proj(GtkButton *btn, t_viewer *viewer)
{
    viewer->func_proj = &parallel_proj;
    gtk_widget_queue_draw(viewer->model);

}

void    button_proj(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *box_proj;
    GtkWidget *button_central_proj;
    GtkWidget *button_parallel_proj;

    box_proj = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(box_buttons), box_proj);

    button_central_proj = gtk_button_new_with_label("Central proj");
    gtk_box_append(GTK_BOX(box_proj), button_central_proj);
    g_signal_connect(GTK_BUTTON(button_central_proj), "clicked", G_CALLBACK(select_central_proj), viewer);

    button_parallel_proj = gtk_button_new_with_label("Parallel proj");
    gtk_box_append(GTK_BOX(box_proj), button_parallel_proj);
    g_signal_connect(GTK_BUTTON(button_parallel_proj), "clicked", G_CALLBACK(select_parallel_proj), viewer);
}