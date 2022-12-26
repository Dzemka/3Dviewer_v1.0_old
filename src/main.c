#include "viewer3D.h"

int main(int argc, char **argv) {
  int status;
  t_viewer *viewer;
  viewer = malloc(sizeof(t_viewer));
  // parser


  // graphics
  parser("shopping_cart.obj", viewer);

  viewer->info.camera.x = 0;
  viewer->info.camera.y = 0;
  viewer->info.camera.z = viewer->dimensions.z_max + 200;
    viewer->func_proj = &central_proj;

  status = run_app(argc, argv, viewer);
  //graphics
  return (0);
}