#include "../viewer3D.h"
#include <gd.h>


void *create_gif(t_viewer *viewer)
{

    FILE *out;
    gdImagePtr image;
    out = fopen("result.gif", "wb");
    image = gdImageCreateFromFile("gifs/00.png");
    gdImageTrueColorToPalette(image, 1, 3);
    gdImageGifAnimBegin(image, out, 0, 0);
    gdImageGifAnimAdd(image, out, 1, 0, 0, 10, gdDisposalNone, NULL);
    gdImageDestroy(image);
    char *file_str;
    file_str = strdup("gifs/01.png");
    int i = 1;
    while (i < 50)
    {
        file_str[5]= i / 10 + 48;
        file_str[6]= (i % 10) + 48;
        image = gdImageCreateFromFile(file_str);
        gdImageTrueColorToPalette(image, 1, 3);
        gdImageGifAnimAdd(image, out, 1, 0, 0, 10, gdDisposalNone, NULL);
        gdImageDestroy(image);
        i++;
        usleep(10000);
    }
    free(file_str);
    putc (';', out);
    fclose(out);
}

void *gif_create(void *arg) {
    t_viewer *viewer;

    viewer = arg;
    double move_value_x;
    double move_value_y;
    double move_value_z;
    double rotate_value_x;
    double rotate_value_y;
    double rotate_value_z;
    double z;
    char *str;
    char *tmp;
    int i;

    i = 0;
    viewer->info.make_screenshot = 2;
    rotate_value_x =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_x)))) / 50 * M_PI / 180;
    rotate_value_y =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_y)))) / 50 * M_PI / 180;
    rotate_value_z =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_z)))) / 50 * M_PI / 180;
    move_value_x =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_x)))) / 50;
    move_value_y =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_y)))) / 50;
    move_value_z =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_z)))) / 50;
    tmp = strdup("gifs/00.png");
    gtk_widget_set_size_request(viewer->model, 640, 480);
    while (++i <= 50) {
        rotate(viewer, 0, rotate_value_x);
        rotate(viewer, 1, rotate_value_y);
        rotate(viewer, 2, rotate_value_z);
        move(viewer, 0, move_value_x);
        move(viewer, 1, move_value_y);
        move(viewer, 2, move_value_z);
        z = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_zoom))));
        if (z == 0)
            z = 1;
        z = pow(10, log10(z) / 50);
        zoom(viewer, z);
        *viewer->info.screenshot_file_name = tmp;
        gtk_widget_queue_draw(viewer->model);
        usleep(300000);
        tmp[5] = i / 10 + 48;
        tmp[6] = i % 10 + 48;
    }
    gtk_widget_set_size_request(viewer->model, 1000, 1000);
    create_gif(viewer);
    viewer->info.make_screenshot = 0;
}

static void transform_all(GtkButton *btn, t_viewer *viewer) {

    pthread_t pthread;

//    gif_create(viewer);
    pthread_mutex_init(&viewer->mutex, NULL);
    pthread_create(&pthread, NULL, &gif_create, viewer);
    pthread_detach(pthread);
//    pthread_join(pthread, NULL);
}

void set_gif_frame(t_viewer *viewer, GtkWidget *box) {
    GtkWidget *frame;
    GtkWidget *button;

    frame = gtk_frame_new("gif");
    gtk_box_append(GTK_BOX(box), frame);
    button = gtk_button_new_with_label("make gif");
    gtk_frame_set_child(GTK_FRAME(frame), button);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(transform_all), viewer);
}