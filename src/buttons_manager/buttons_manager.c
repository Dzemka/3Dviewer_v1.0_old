#include "../viewer3D.h"

static void enter(GtkButton *btn, t_viewer *viewer) {
    const char *s;
    int i;

    viewer->filename = strdup(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_file))));
    //подготовить особождение перед открытием нового файла
//    viewer->filename = strdup("Camera.obj");
//    i = -1;
//    printf("1- %ld\n", viewer->info.count_v);
    free(viewer->info.vertexes3d);
    free(viewer->info.vertexes2d);
    ft_lstclear(&viewer->vertex_list, free);
    viewer->vertex_list = NULL;
////    ft_lstclear(&viewer->info.faces, free);
    t_list *tmp;

    tmp = viewer->info.faces;
    t_plane *plane;
    while(viewer->info.faces)
    {
        plane = viewer->info.faces->content;
        tmp = viewer->info.faces->next;
        free(plane->indexes);
        free(plane);
        free(viewer->info.faces);
        viewer->info.faces = tmp;
    }
    viewer->info.faces = NULL;
    free(viewer->p);
    viewer->p = NULL;
    ft_lstclear(&viewer->f, free);
    viewer->f = NULL;
    printf("2- %ld\n", viewer->info.count_v);
//    viewer->reparse = 1;
    parser(viewer->filename, viewer);

    char *markup;
    markup = g_markup_printf_escaped ("<span style=\"italic\" background=\"#000000\" foreground=\"#FFFFFF\" font-size=\"25pt\">\%s</span>", viewer->filename);
    gtk_label_set_markup(GTK_LABEL(viewer->label_filename), markup);
    g_free (markup);
    gtk_widget_queue_draw(viewer->model);
}

static void button_transformation(t_viewer *viewer, GtkWidget *box_buttons) {
    fill_frame_moving(viewer, box_buttons);
    fill_frame_rotating(viewer, box_buttons);
    fill_frame_scaling(viewer, box_buttons);
}

void button_entry_file(t_viewer *viewer, GtkWidget *box_buttons) {
    GtkWidget *frame;
    GtkWidget *box_entry_file;
    GtkWidget *button;

    frame = gtk_frame_new("Select file");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    box_entry_file = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_entry_file);
    viewer->entry.entry_file = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_file), "input file");
    button = gtk_button_new_with_label("Enter file");
    gtk_box_append(GTK_BOX(box_entry_file), viewer->entry.entry_file);
    gtk_box_append(GTK_BOX(box_entry_file), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(enter), viewer);
}

void buttons_manager(t_viewer *viewer, GtkWidget *box_left, GtkWidget *box_right) {
    button_entry_file(viewer, box_left);
    button_transformation(viewer, box_left);
    button_proj(viewer, box_left);
    set_background_color(viewer, box_left);
    set_type_edge(viewer, box_left);
    set_color_edge(viewer, box_left);
    set_thickness_edge(viewer, box_left);
    set_type_vertices(viewer, box_left);
    set_color_vertices(viewer, box_left);
    set_size_vertices(viewer, box_left);
    set_screenshot_frame(viewer, box_right);
    set_gif_frame(viewer, box_right);
    set_resize_frame(viewer, box_right);
}