#include "viewer3D.h"

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer pointer ) {
  //drawing area
}

void  draw_model(t_viewer *viewer)
{
  gtk_widget_set_size_request(viewer->model, 1000, 1000);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(viewer->model), draw_function, viewer,
                                 NULL);
}