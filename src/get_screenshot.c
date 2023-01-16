#include "./viewer3D.h"

void    get_screenshot(t_viewer *viewer, cairo_surface_t *surface) {
    GdkPixbuf *pixbuf = NULL;
    char *str;
    char *tmp;
    cairo_status_t status_png;

    if (viewer->info.make_screenshot == SCREENSHOT_CREATE) {
        tmp = ft_strjoin(viewer->info.screenshot_file_name, ".");
        str = ft_strjoin(tmp, viewer->info.screenshot_format);
        free(tmp);
        tmp = ft_strjoin("screenshots/", str);
        pixbuf = gdk_pixbuf_get_from_surface(surface, 0, 0, gtk_widget_get_width(viewer->model),
                                             gtk_widget_get_height(viewer->model));
        gdk_pixbuf_save(pixbuf, tmp, viewer->info.screenshot_format, NULL, "quality", "100", NULL);
        g_object_unref(pixbuf);
        free(str);
        free(tmp);
        viewer->info.make_screenshot = DO_NOTHING;
    }
    else
    {
        status_png = cairo_surface_write_to_png(surface, viewer->info.screenshot_file_name);
    //    printf("%d\n", status_png);
        viewer->png_pause = FALSE;
    }
}