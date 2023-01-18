#include "../viewer3D.h"

void *build_gif(t_viewer *viewer) {
    FILE *out;
    gdImagePtr image;
    char *file_str;
    GtkEntryBuffer *buf;
    char *name;
    char *tmp;
    int status;

    buf = gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_gif));
    if (gtk_entry_buffer_get_length(buf) == 0)
        name = strdup("gifs/unnamed.gif");
    else {
        tmp = ft_strjoin((char *) gtk_entry_buffer_get_text(buf), ".gif");
        name = ft_strjoin("gifs/", tmp);
        free(tmp);
    }
    out = NULL;
    int fd;
    out = fopen(name, "wb");
    if (!out) {
        printf("error %d\n", errno);
        exit(errno);
    }
    free(name);
    image = gdImageCreateFromFile("temp_png/00.png");
    gdImageGifAnimBegin(image, out, 0, 0);
    gdImageGifAnimAdd(image, out, 1, 0, 0, 10, gdDisposalNone, NULL);
    gdImageDestroy(image);
    file_str = strdup("temp_png/00.png");
    if (!file_str)
        printf("file str error\n");
    int i = 0;
    while (i < 50) {
        file_str[9] = i / 10 + 48;
        file_str[10] = (i % 10) + 48;
        image = gdImageCreateFromFile(file_str);
        gdImageTrueColorToPalette(image, 1, 4);
        gdImageGifAnimAdd(image, out, 1, 0, 0, 10, gdDisposalNone, NULL);
        gdImageDestroy(image);
        fd = open(file_str, O_RDONLY);
        if (fd != -1) {
            close(fd);
            status = remove(file_str);
            if (status == -1)
                printf("remove error file %s\n", file_str);
        }
        i++;
    }
    free(file_str);
    putc(';', out);
    fclose(out);
    rmdir("temp_png");
}

static void create_png(t_viewer *viewer, double *move_value, double *rotate_value, double z) {
    int i;
    int j;

    g_mkdir_with_parents("temp_png", 0777);
    viewer->info.screenshot_file_name = strdup("temp_png/00.png");
    viewer->png_pause = FALSE;
    i = -1;
    while (++i < 50) {
        (viewer->info.screenshot_file_name)[9] = i / 10 + 48;
        (viewer->info.screenshot_file_name)[10] = i % 10 + 48;
        j = -1;
        while (++j < 3) {
            rotate(viewer->info.vertexes3d, viewer->info.count_v * 3, j, rotate_value[j]);
            move(viewer->info.vertexes3d, viewer->info.count_v * 3, j, move_value[j]);
        }
        zoom(viewer->info.vertexes3d, viewer->info.count_v * 3, z);
        viewer->png_pause = TRUE;
        gtk_widget_queue_draw(viewer->model);
        while (viewer->png_pause);
    }
}

void get_transform_values(t_viewer *viewer, double *move_value, double *rotate_value, double *z) {
    rotate_value[0] =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_x)))) / 50;
    rotate_value[1] =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_y)))) / 50;
    rotate_value[2] =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_rotate_z)))) / 50;
    move_value[0] =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_x)))) / 50;
    move_value[1] =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_y)))) / 50;
    move_value[2] =
            atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_move_z)))) / 50;
    *z = atof(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_zoom))));
    if (*z == 0)
        *z = 1;
    *z = pow(10, log10(*z) / 50);
}

void *gif_create(void *arg) {
    t_viewer *viewer;
    double *move_value;
    double *rotate_value;
    double z;
    double k;

    viewer = arg;
    g_mkdir_with_parents("gifs", 0777);
    k = 640.0 / viewer->info.width;
    gtk_widget_set_size_request(viewer->model, 640, 480);
    zoom(viewer->info.vertexes3d, viewer->info.count_v * 3, k);
    move_value = malloc(sizeof(double) * 3);
    rotate_value = malloc(sizeof(double) * 3);
    get_transform_values(viewer, move_value, rotate_value, &z);
    viewer->info.make_screenshot = GIF_CREATE;
    create_png(viewer, move_value, rotate_value, z);
    free(move_value);
    free(rotate_value);
    viewer->info.make_screenshot = DO_NOTHING;
    k = viewer->info.width / 640.0;
    zoom(viewer->info.vertexes3d, viewer->info.count_v * 3, k);
    gtk_widget_set_size_request(viewer->model, viewer->info.width, viewer->info.height);
    build_gif(viewer);
}

static void transform_all(GtkButton *btn, t_viewer *viewer) {

    pthread_t pthread;

    if (viewer->info.make_screenshot != 0)
        return;
    pthread_create(&pthread, NULL, &gif_create, viewer);
    pthread_detach(pthread);
}

void set_gif_frame(t_viewer *viewer, GtkWidget *box) {
    GtkWidget *frame;
    GtkWidget *box_gif;
    GtkWidget *button;

    frame = gtk_frame_new("Create gif");
    gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
    gtk_box_append(GTK_BOX(box), frame);
    box_gif = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_frame_set_child(GTK_FRAME(frame), box_gif);
    viewer->entry.entry_gif = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_gif), "Enter file name for gif");
    gtk_box_append(GTK_BOX(box_gif), viewer->entry.entry_gif);
    button = gtk_button_new_with_label("make gif");
    gtk_box_append(GTK_BOX(box_gif), button);
    g_signal_connect_after(GTK_BUTTON(button), "clicked", G_CALLBACK(transform_all), viewer);
}