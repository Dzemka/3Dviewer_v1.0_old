#include "viewer3D.h"

int main(int argc, char** argv) {
  int status;
  t_viewer viewer;
  // parser


  // graphics
  parser("Camera.obj", &viewer);
  status = run_app(argc, argv, &viewer);
  //graphics
  return (0);
}