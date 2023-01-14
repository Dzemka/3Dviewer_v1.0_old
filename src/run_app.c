
#include "viewer3D.h"

static void
resize_cb(GtkWidget *widget,
          int width,
          int height,
          gpointer data) {
    printf("%d %d\n",width, height);
}

static void app_activate(GApplication *app, t_viewer *viewer) {
    GtkWidget *win;

    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "3Dviewer_v1.0");
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(win), 640 + 280 + 280, 480);
    gui_activate(viewer, win);
    gtk_widget_show(win);
}

int run_app(int argc, char **argv, t_viewer *viewer) {
    GtkApplication *app;
//    char *s;

    int status;
    app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), viewer);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return (status);
}