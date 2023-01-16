#include "../viewer3D.h"

static void change_background_color(GtkWidget *btn, t_viewer *viewer)
{
    GdkRGBA color;

    if (viewer->info.make_screenshot != 0)
        return;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(btn), &viewer->settings.background_color);
    char *temp;
  char *str;
  char *res;
  temp = ft_itoa(viewer->info.count_v);
  str = ft_strjoin(viewer->filename, " ");
  res = ft_strjoin(str, temp);
  free(str);
  free(temp);
    create_stringlabel(res, viewer);
    free(res);
    gtk_widget_queue_draw(viewer->model);
}

void set_background_color(t_viewer *viewer, GtkWidget *box_buttons)
{
    GtkWidget *box_color;
    GtkWidget *color_button;
    GtkWidget *frame;

    box_color = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box_buttons), box_color);
    color_button = gtk_color_button_new();
    gtk_color_button_set_title(GTK_COLOR_BUTTON(color_button), "Select background color");
    gtk_color_button_set_modal(GTK_COLOR_BUTTON(color_button), TRUE);
    g_signal_connect_after(GTK_COLOR_BUTTON(color_button), "color-set", G_CALLBACK(change_background_color), viewer);
    frame = gtk_frame_new("Select background color");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box_buttons), frame);
    gtk_frame_set_child(GTK_FRAME(frame), color_button);

}