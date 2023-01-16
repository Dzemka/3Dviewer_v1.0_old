#include "viewer3D.h"

//returns: error(0), ok(1)
static int get_settings_from_file(t_viewer *viewer)
{
  FILE *file;

  file = fopen("settings", "r");
  if (!file) {
    printf("cannot open settings file\n");
    return (0);
  }
  if (!parse_settings_file(viewer, file))
    return (0);
  fclose(file);
  return (1);
}

static void get_settings_default(t_viewer *viewer)
{
  viewer->settings.func_proj = &central_proj;
  viewer->settings.is_dashed = 0;
  viewer->settings.edge_color.red = 105;
  viewer->settings.edge_color.green = 0;
  viewer->settings.edge_color.blue = 198;
  viewer->settings.edge_thickness = MIN_EDGE_THICKNESS;
  viewer->settings.vertices_type = NONE_VERTICES;
  viewer->settings.vertices_color.red = 0;
  viewer->settings.vertices_color.green = 255;
  viewer->settings.vertices_color.blue = 0;
  viewer->settings.vertices_size = MIN_VERTICES_SIZE;
  viewer->settings.background_color.red = 0;
  viewer->settings.background_color.green = 0;
  viewer->settings.background_color.blue = 0;
}

void get_settings(t_viewer *viewer) {
  // if (!get_settings_from_file(viewer))
    get_settings_default(viewer);
}