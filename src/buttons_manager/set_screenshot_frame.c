#include "../viewer3D.h"

static void make_screenshot(GtkWidget *btn, t_viewer *viewer) {
    GtkEntryBuffer *buf;
    char *str;

    if (viewer->info.make_screenshot != 0)
        return;
    buf = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_screenshot));
    if (gtk_entry_buffer_get_length(buf) == 0) {
        if (viewer->info.screenshot_file_name)
            free(viewer->info.screenshot_file_name);
        viewer->info.screenshot_file_name = strdup("unnamed");
        printf("%s\n", viewer->info.screenshot_file_name);
    }
    else {
        str = (char *) gtk_entry_buffer_get_text(buf);
        if (str) {
            if (viewer->info.screenshot_file_name)
              free(viewer->info.screenshot_file_name);
            viewer->info.screenshot_file_name = strdup(str);
        }
    }
    viewer->info.make_screenshot = SCREENSHOT_CREATE;
    gtk_widget_queue_draw(viewer->model);
}

static void set_jpeg(GtkWidget *btn, t_viewer *viewer) {
    free(viewer->info.screenshot_format);
    viewer->info.screenshot_format = strdup("jpeg");

}

static void set_bmp(GtkWidget *btn, t_viewer *viewer) {
    free(viewer->info.screenshot_format);
    viewer->info.screenshot_format = strdup("bmp");

}

void set_screenshot_frame(t_viewer *viewer, GtkWidget *box) {
    GtkWidget *frame;
    GtkWidget *box_screenshot;
    GtkWidget *box_select_format;
    GtkWidget *button_jpeg;
    GtkWidget *button_bmp;
    GtkWidget *screenshot;

    frame = gtk_frame_new("Save screenshot");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box), frame);
    box_screenshot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_screenshot);
    viewer->entry.entry_screenshot = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_screenshot), "Enter file name for screenshot");
    gtk_box_append(GTK_BOX(box_screenshot), viewer->entry.entry_screenshot);
    box_select_format = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_screenshot), box_select_format);
    button_jpeg = gtk_check_button_new_with_label("Jpeg");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(button_jpeg), TRUE);
    gtk_box_append(GTK_BOX(box_select_format), button_jpeg);
    g_signal_connect(GTK_CHECK_BUTTON(button_jpeg), "toggled", G_CALLBACK(set_jpeg), viewer);

    button_bmp = gtk_check_button_new_with_label("Bmp");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(button_bmp), GTK_CHECK_BUTTON(button_jpeg));
    gtk_box_append(GTK_BOX(box_select_format), button_bmp);
    g_signal_connect(GTK_CHECK_BUTTON(button_bmp), "toggled", G_CALLBACK(set_bmp), viewer);
    screenshot = gtk_button_new_with_label("Screenshot");
    gtk_box_append(GTK_BOX(box_screenshot), screenshot);
    g_signal_connect(GTK_BUTTON(screenshot), "clicked", G_CALLBACK(make_screenshot), viewer);

}