#include "viewer3D.h"

void draw_vertices(t_viewer *viewer, cairo_t *cr)
{
    int i;
    int size;

    size = viewer->info.count_v * 2;
    i = 0;
    cairo_set_source_rgb(cr, viewer->settings.vertices_color.red, viewer->settings.vertices_color.green, viewer->settings.vertices_color.blue);
    while (i < size)
    {
        if (viewer->settings.vertices_type == CIRCLE_VERTICES)
           cairo_arc(cr, viewer->info.vertexes2d[i], viewer->info.vertexes2d[i + 1], viewer->settings.vertices_size, 0, 2 * M_PI);
        else
            cairo_rectangle(cr, viewer->info.vertexes2d[i] - viewer->settings.vertices_size, viewer->info.vertexes2d[i + 1] - viewer->settings.vertices_size, viewer->settings.vertices_size * 2, viewer->settings.vertices_size * 2);
        i += 2;
        cairo_fill(cr);
    }
}

void draw_settings(t_viewer *viewer, cairo_t *cr) {
    if (viewer->settings.is_dashed)
    {
        double dashes[] = {20.0,
                           20.0
        };
        int ndash = sizeof(dashes) / sizeof(dashes[0]);
        double offset = 0.0;
        cairo_set_dash(cr, dashes, ndash, offset);
    }
    cairo_set_line_width(cr, viewer->settings.edge_thickness);
    if (viewer->settings.vertices_type)
        draw_vertices(viewer, cr);
    cairo_set_source_rgb(cr, viewer->settings.edge_color.red, viewer->settings.edge_color.green, viewer->settings.edge_color.blue);
}