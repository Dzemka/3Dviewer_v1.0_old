#include "../viewer3D.h"

static void scale_dimensions(t_viewer *viewer, double scaling) {
  viewer->dimensions.x_min *= scaling;
  viewer->dimensions.x_max *= scaling;
  viewer->dimensions.y_min *= scaling;
  viewer->dimensions.y_max *= scaling;
  viewer->dimensions.z_min *= scaling;
  viewer->dimensions.z_max *= scaling;
}

static void fill_vertexes3d(t_viewer *viewer, double scaling, double width,
                            double height) {
  int i;
  int j;
  t_list *temp;
  temp = viewer->vertex_list;

  j = 0;
  while (temp) {
    i = -1;
    while (++i < 3) {
      if (i == 0) {
        viewer->info.vertexes3d[j] = ((double *)temp->content)[i] -
                                     (viewer->dimensions.x_min + width / 2);
      } else if (i == 1) {
        viewer->info.vertexes3d[j] = ((double *)temp->content)[i] -
                                     (viewer->dimensions.y_min + height / 2);
      } else
        viewer->info.vertexes3d[j] = ((double *)temp->content)[i];
      viewer->info.vertexes3d[j] *= scaling;
      j++;
    }
    temp = temp->next;
  }
}

static void get_scaling(t_viewer *viewer, double *scaling, double *width,
                        double *height) {
  *width = viewer->dimensions.x_max - viewer->dimensions.x_min;
  *height = viewer->dimensions.y_max - viewer->dimensions.y_min;
  if (*width / *height > viewer->info.width / viewer->info.height)
    *scaling = viewer->info.width / (1.5 * *width);
  else
    *scaling = viewer->info.height / (1.5 * *height);
}

static void set_camera(t_viewer *viewer) {
  viewer->info.camera.x = 0;
  viewer->info.camera.y = 0;
  viewer->info.camera.z = viewer->dimensions.z_max + 500;
}

void set_values(t_viewer *viewer) {
  double width;
  double height;
  double scaling;

  viewer->info.vertexes3d = malloc(sizeof(double) * viewer->info.count_v * 3);
  if (!viewer->info.vertexes3d) exit_message("Malloc error\n");
  viewer->info.vertexes2d = malloc(sizeof(double) * viewer->info.count_v * 2);
  if (!viewer->info.vertexes2d) exit_message("Malloc error\n");
  get_scaling(viewer, &scaling, &width, &height);
  fill_vertexes3d(viewer, scaling, width, height);
  scale_dimensions(viewer, scaling);
  set_camera(viewer);
}