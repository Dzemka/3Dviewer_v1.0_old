#include "viewer3D.h"

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data)
{

  int x;
  int y;
  int z;

  int zd;

  int zx;
  int zy;
  zd = 10;

  x = 100;
  y = 200;
  z = -10;

  cairo_set_source_rgb(cr, 255, 0, 0);
  cairo_set_line_width(cr, 1);


  cairo_move_to(cr, width / 5, 0);
  cairo_line_to(cr, width / 5, height);
//  cairo_rel_line_to(cr, 30, 30);
//  cairo_line_to(cr, p.x, p.y + 100);
//  cairo_move_to(cr, p.x, p.y);
//  cairo_line_to(cr, x + 100, y);
//  cairo_move_to(cr, p.x, p.y);
//  cairo_line_to(cr, x + 50, y + 50);
//  cairo_rel_line_to(cr, 50, 20);

  cairo_stroke(cr);
}

static void app_activate(GApplication *app, gpointer user_data)
{
  GtkWidget *win = gtk_application_window_new(GTK_APPLICATION(app));

  GtkWidget *box;
  GtkWidget *button;

  gtk_window_set_title(GTK_WINDOW(win), "da1");
  gtk_window_set_default_size(GTK_WINDOW(win), 500, 500);
  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign (box, GTK_ALIGN_CENTER);
  gtk_window_set_child (GTK_WINDOW (win), box);

  button = gtk_button_new_with_label ("Hello World");

  gtk_window_set_child(GTK_WINDOW(button), box);

  GtkWidget *area = gtk_drawing_area_new();
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), draw_function, NULL, NULL);
  gtk_window_set_child(GTK_WINDOW(win), area);
//  gtk_box_append (GTK_BOX (area), button);
  gtk_widget_show(win);
}

int run_app(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return (status);
}