#include "../viewer3D.h"

static void select_central_proj(GtkButton *btn, t_viewer *viewer)
{
    if (viewer->info.make_screenshot != 0)
        return;
    viewer->settings.func_proj = &central_proj;
    gtk_widget_queue_draw(viewer->model);

}

static void select_parallel_proj(GtkButton *btn, t_viewer *viewer)
{
    if (viewer->info.make_screenshot != 0)
        return;
    viewer->settings.func_proj = &parallel_proj;
    gtk_widget_queue_draw(viewer->model);

}

void    button_proj(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *frame;
    GtkWidget *box_proj;
    GtkWidget *button_central_proj;
    GtkWidget *button_parallel_proj;


    frame = gtk_frame_new("Select projection");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    box_proj = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_frame_set_child(GTK_FRAME(frame), box_proj);

    button_central_proj = gtk_check_button_new_with_label("Central proj");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(button_central_proj), TRUE);
    gtk_box_append(GTK_BOX(box_proj), button_central_proj);
    g_signal_connect(GTK_CHECK_BUTTON(button_central_proj), "toggled", G_CALLBACK(select_central_proj), viewer);
    button_parallel_proj = gtk_check_button_new_with_label("Parallel proj");
    gtk_check_button_set_group (GTK_CHECK_BUTTON(button_parallel_proj),GTK_CHECK_BUTTON(button_central_proj));
    gtk_box_append(GTK_BOX(box_proj), button_parallel_proj);
    g_signal_connect(GTK_CHECK_BUTTON(button_parallel_proj), "toggled", G_CALLBACK(select_parallel_proj), viewer);
}