#include "../viewer3D.h"

void set_values(t_viewer *viewer) {
    int i;
    int j;
    t_list *temp;
    double width;
    double height;

    width = viewer->dimensions.x_max - viewer->dimensions.x_min;
    height = viewer->dimensions.y_max - viewer->dimensions.y_min;
    if (width / height > viewer->info.width / viewer->info.height)
        viewer->info.camera.screen_z = viewer->info.width / (1.5 * width);
    else
        viewer->info.camera.screen_z = viewer->info.height / (1.5 * height);
    temp = viewer->vertex_list;
    j = 0;
    while (temp) {
        i = -1;
        while (++i < 3) {
            if (i == 0) {
              viewer->info.vertexes3d[j] = ((double *) temp->content)[i] - (viewer->dimensions.x_min + width / 2);
            } else if (i == 1) {
              viewer->info.vertexes3d[j] = ((double *) temp->content)[i] - (viewer->dimensions.y_min + height / 2);
            }
            else
              viewer->info.vertexes3d[j] = ((double *) temp->content)[i];
            viewer->info.vertexes3d[j] *= viewer->info.camera.screen_z;
            j++;
        }
        temp = temp->next;
    }
    viewer->dimensions.x_min *= viewer->info.camera.screen_z;
    viewer->dimensions.x_max *= viewer->info.camera.screen_z;
    viewer->dimensions.y_min *= viewer->info.camera.screen_z;
    viewer->dimensions.y_max *= viewer->info.camera.screen_z;
    viewer->dimensions.z_min *= viewer->info.camera.screen_z;
    viewer->dimensions.z_max *= viewer->info.camera.screen_z;
    viewer->info.camera.x = 0;
    viewer->info.camera.y = 0;
    viewer->info.camera.z = viewer->dimensions.z_max + 500;
}