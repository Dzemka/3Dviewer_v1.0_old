#include "viewer3D.h"

void draw_vertices(t_viewer *viewer, cairo_t *cr)
{
    int i;

    i = 0;
    cairo_set_source_rgb(cr, viewer->info.vertices_color.red, viewer->info.vertices_color.green, viewer->info.vertices_color.blue);
    while (i < viewer->info.count_v * 2)
    {
        if (viewer->info.type_vertices == 1)
           cairo_arc(cr, viewer->info.vertexes2d[i], viewer->info.vertexes2d[i + 1], viewer->info.vertices_size, 0, 2 * M_PI);
        else
            cairo_rectangle(cr, viewer->info.vertexes2d[i] - viewer->info.vertices_size, viewer->info.vertexes2d[i + 1] - viewer->info.vertices_size, viewer->info.vertices_size * 2, viewer->info.vertices_size * 2);
        i += 2;
        cairo_fill(cr);
    }
    cairo_set_source_rgb(cr, viewer->info.edge_color.red, viewer->info.edge_color.green, viewer->info.edge_color.blue);

}

void draw_settings(t_viewer *viewer, cairo_t *cr) {
    if (viewer->info.is_dashed)
    {
        double dashes[] = {25.0,
                           25.0
        };
        int ndash = sizeof(dashes) / sizeof(dashes[0]);
        double offset = 0.0;
        cairo_set_dash(cr, dashes, ndash, offset);
    }
    cairo_set_source_rgb(cr, viewer->info.edge_color.red, viewer->info.edge_color.green, viewer->info.edge_color.blue);
    cairo_set_line_width(cr, viewer->info.edge_thickness);
    if (viewer->info.type_vertices)
        draw_vertices(viewer, cr);
}