#include "../viewer3D.h"

static void select_none_vertices(GtkWidget *btn, t_viewer *viewer) {
    if (viewer->info.make_screenshot != 0)
        return;
    viewer->settings.vertices_type = NONE_VERTICES;
    gtk_widget_queue_draw(viewer->model);
}

static void select_circle_vertices(GtkWidget *btn, t_viewer *viewer) {
    if (viewer->info.make_screenshot != 0)
        return;
    viewer->settings.vertices_type = CIRCLE_VERTICES;
    gtk_widget_queue_draw(viewer->model);
}

static void select_square_vertices(GtkWidget *btn, t_viewer *viewer) {
    if (viewer->info.make_screenshot != 0)
        return;
    viewer->settings.vertices_type = SQUARE_VERTICES;
    gtk_widget_queue_draw(viewer->model);
}

void set_type_vertices(t_viewer *viewer, GtkWidget *box_buttons) {
    GtkWidget *frame;
    GtkWidget *box_types;
    GtkWidget *button_none;
    GtkWidget *button_circle;
    GtkWidget *button_square;

    frame = gtk_frame_new("Select type of vertices");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    box_types = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_frame_set_child(GTK_FRAME(frame), box_types);
    button_none = gtk_check_button_new_with_label("None");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(button_none), TRUE);
    gtk_box_append(GTK_BOX(box_types), button_none);
    g_signal_connect(GTK_CHECK_BUTTON(button_none), "toggled", G_CALLBACK(select_none_vertices), viewer);
    button_circle = gtk_check_button_new_with_label("Circle");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(button_none), GTK_CHECK_BUTTON(button_circle));
    gtk_box_append(GTK_BOX(box_types), button_circle);
    g_signal_connect(GTK_CHECK_BUTTON(button_circle), "toggled", G_CALLBACK(select_circle_vertices), viewer);
    button_square = gtk_check_button_new_with_label("Square");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(button_none), GTK_CHECK_BUTTON(button_square));
    gtk_check_button_set_group(GTK_CHECK_BUTTON(button_circle), GTK_CHECK_BUTTON(button_square));
    gtk_box_append(GTK_BOX(box_types), button_square);
    g_signal_connect(GTK_CHECK_BUTTON(button_square), "toggled", G_CALLBACK(select_square_vertices), viewer);
}