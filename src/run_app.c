
#include "viewer3D.h"

static void ft_click1(GtkButton *btn, gpointer userdata) {
  g_print("signal 1\n");
}

static void ft_click2(GtkButton *btn, gpointer userdata) {
  g_print("SIGNAL 2\n");
}

static void rotate(GtkWidget *widget, gpointer angle)
{

//  (*(double *)angle) += 0.5;
  gtk_widget_queue_draw (angle);

}

static void get_text(GtkWidget *widget, gpointer b)
{
  const char *s;

  s = gtk_entry_buffer_get_text(gtk_entry_get_buffer(b));
  printf("%s\n", s);


  FILE *fd;

  fd = fopen(s, "r");
  char *str;
  str = NULL;
  size_t u;

  printf("err\n");
  getline(&str, &u, fd);
  printf("err\n");

  printf("%s", str);
  free(str);
  fclose(fd);
}

static void app_activate(GApplication *app, t_viewer *viewer) {

  GtkWidget *win;

  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(win), "3Dviewer_v1.0");
//  gtk_window_set_default_size(GTK_WINDOW(win), 1920, 1080);
      gui_activate(viewer, win);
  printf("%d\n", gtk_widget_get_width(GTK_WIDGET(win)));

  //draw_model

////  g_signal_connect (press, "pressed", G_CALLBACK(pressed), area);

  gtk_widget_show(win);
//  g_object_unref(win);
}

static void app_open(GApplication *app, GFile **files, gint n_files,
                     gchar *hint, gpointer user_data) {
  int i;

  i = -1;
  //  while (files[++i])
  //    printf("%s\n", g_file_get_basename (files[0]));
  //    g_print(g_file_get_basename (files[0]));
  write(1, "sdf", 3);
}

int run_app(int argc, char **argv, t_viewer *viewer) {
  GtkApplication *app;
  char *s;

   int status;
   app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
   g_signal_connect(app, "activate", G_CALLBACK(app_activate), viewer);
////   // g_signal_connect(app, "open", G_CALLBACK(app_open), NULL);
   status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  printf("return\n");
  exit(0);
  return (status);
}