#include "viewer3D.h"

static void get_settings(t_viewer *viewer) {
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

static void init_values(t_viewer *viewer) {
  viewer->info.screenshot_file_name = NULL;
  viewer->info.screenshot_format = strdup("jpeg");
  viewer->info.faces = NULL;
  viewer->info.vertexes3d = NULL;
  viewer->info.vertexes2d = NULL;
  viewer->vertex_list = NULL;
//  viewer->p = NULL;
//  viewer->f = NULL;
  viewer->info.width = 1360;
  viewer->info.height = 1000;
  viewer->filename = NULL;
  viewer->info.make_screenshot = 0;
  get_settings(viewer);
}

int main(int argc, char **argv, char **env) {
  int status;
  t_viewer *viewer;

  viewer = malloc(sizeof(t_viewer));
  if (!viewer)
    exit_message("Malloc error\n");
  init_values(viewer);

  //добавить проверку на .obj
  //    parser("Camera.obj", viewer);
  status = run_app(argc, argv, viewer);
  save_settings(viewer);
  // graphics
  printf("return\n");
  exit(0);

  return (status);
}