#include "viewer3D.h"

void parallel_proj(t_viewer *viewer, int width, int height) {
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < viewer->info.count_v * 2) {
        viewer->info.vertexes2d[j] =
//                (5000 / (viewer->info.camera.z - viewer->info.vertexes3d[i + 2]) *
                 (viewer->info.vertexes3d[i] - viewer->info.camera.x) +
                 viewer->info.camera.x +
                 width / 2;  // xz = (5000/(cz - z) * (x - cx) + cx + width / 2)
        viewer->info.vertexes2d[j + 1] =
                (height / 2 -
//                 (5000 / (viewer->info.camera.z - viewer->info.vertexes3d[i + 2]) *
                  (viewer->info.vertexes3d[i + 1] - viewer->info.camera.y) +
                  viewer->info.camera.y);
        j += 2;
        i += 3;
    }
}

void central_proj(t_viewer *viewer, int width, int height) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (j < viewer->info.count_v * 2) {
    viewer->info.vertexes2d[j] =
        (5000 / (viewer->info.camera.z - viewer->info.vertexes3d[i + 2]) *
             (viewer->info.vertexes3d[i] - viewer->info.camera.x) +
         viewer->info.camera.x +
         width / 2);  // xz = (5000/(cz - z) * (x - cx) + cx + width / 2)
    viewer->info.vertexes2d[j + 1] =
        (height / 2 -
         (5000 / (viewer->info.camera.z - viewer->info.vertexes3d[i + 2]) *
              (viewer->info.vertexes3d[i + 1] - viewer->info.camera.y) +
          viewer->info.camera.y));
    j += 2;
    i += 3;
  }
}

static void draw(t_viewer *viewer, cairo_t *cr) {
  int i;
  t_list *list;
  t_plane *plane;
  double coord_x;
  double coord_y;
  size_t index_vertex;

  list = viewer->info.faces;

  while (list) {
    plane = (t_plane *)list->content;
    i = -1;
    double dashes[] = {50.0,
        25.0
    };
    int    ndash  = sizeof (dashes)/sizeof(dashes[0]);
    double offset = -50.0;

    cairo_set_dash (cr, dashes, ndash, offset);
    while (++i < (int)plane->size) {
      index_vertex = (plane->indexes[i % plane->size] -
                      1);  // 0 % 4 == 0 || 1 % 4 == 1 || 4 % 4 ==  0
      coord_x = viewer->info.vertexes2d[index_vertex * 2];
      coord_y = viewer->info.vertexes2d[index_vertex * 2 + 1];
      cairo_move_to(cr, coord_x, coord_y);
      index_vertex = (plane->indexes[(i + 1) % plane->size] - 1);
      coord_x = viewer->info.vertexes2d[index_vertex * 2];
      coord_y = viewer->info.vertexes2d[index_vertex * 2 + 1];
      cairo_line_to(cr, coord_x, coord_y);
    }
    cairo_stroke(cr);
    list = list->next;
  }
  cairo_stroke(cr);
}

static void draw_function(GtkDrawingArea *area, cairo_t *cr, int width,
                          int height, gpointer pointer) {
  t_viewer *viewer;
  viewer = pointer;

//  central_proj(viewer, width, height);
//  paralell_proj(viewer, width, height);
    viewer->func_proj(viewer, width, height);

  cairo_set_source_rgb(cr, 255, 255, 255);
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_fill(cr);
  cairo_set_source_rgb(cr, 0, 0, 255);
  draw(viewer, cr);
}

void draw_model(t_viewer *viewer) {
  gtk_widget_set_size_request(viewer->model, 1920 - 500, 1080);
  gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(viewer->model), draw_function,
                                 viewer, NULL);
}