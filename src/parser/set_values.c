#include "../viewer3D.h"

void set_values(t_viewer *viewer)
{
  int i;
  int j;
  t_list *temp;

  viewer->info.vertexes3d = malloc(sizeof (double) * viewer->info.count_v * 3);
  viewer->info.vertexes2d = malloc(sizeof (double) * viewer->info.count_v * 2);
  temp = viewer->vertex_list;
  j = 0;
  while (temp)
  {
    i = -1;
    while (++i < 3) {
      viewer->info.vertexes3d[j] = ((double *)temp->content)[i];
      j++;
    }
    temp = temp->next;
  }
}