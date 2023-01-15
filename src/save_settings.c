#include "./viewer3D.h"

void save_settings(t_viewer *viewer) {
  FILE *file;

  file = fopen("settings", "w");
  fprintf(file, "PROJECTION ");
//  if (viewer->settings.func_proj == central_proj)
//    fprintf(file, "0\n");
//  else
//    fprintf(file, "1\n");
  fprintf(file, "%d\n", viewer->settings.func_proj == parallel_proj);
  fprintf(file, "EDGE_TYPE ");
  fprintf(file, "%d\n", viewer->settings.is_dashed);
//  if (viewer->settings.is_dashed)
//    fprintf(file, "DASHED\n");
//  else
//    fprintf(file, "SOLID\n");
  fprintf(file, "EDGE_COLOR %f:%f:%f\n", viewer->settings.edge_color.red,
          viewer->settings.edge_color.green, viewer->settings.edge_color.blue);
  fprintf(file, "EDGE_THICKNESS %f\n", viewer->settings.edge_thickness);
  fprintf(file, "VERTICES_TYPE %d\n", viewer->settings.vertices_type);
  fprintf(file, "VERTICES_COLOR %f:%f:%f\n",
          viewer->settings.vertices_color.red,
          viewer->settings.vertices_color.green,
          viewer->settings.vertices_color.blue);
  fprintf(file, "VERTICES_SIZE %f\n", viewer->settings.vertices_size);
  fprintf(file, "BACKGROUND_COLOR %f:%f:%f\n",
          viewer->settings.background_color.red,
          viewer->settings.background_color.green,
          viewer->settings.background_color.blue);
  fclose(file);
  printf("ok\n");
}