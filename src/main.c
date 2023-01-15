#include "viewer3D.h"

static void init_values(t_viewer *viewer) {
  viewer->info.screenshot_file_name = NULL;
  viewer->info.screenshot_format = strdup("jpeg");
  viewer->info.faces = NULL;
  viewer->info.vertexes3d = NULL;
  viewer->info.vertexes2d = NULL;
  viewer->vertex_list = NULL;
  viewer->info.count_v = 0;
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
  status = run_app(argc, argv, viewer);
  save_settings(viewer);
  return (status);
}