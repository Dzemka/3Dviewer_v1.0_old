#include "viewer3D.h"

void parallel_proj(t_viewer *viewer, int width, int height) {
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < viewer->info.count_v * 2) {
        viewer->info.vertexes2d[j] =
                (viewer->info.vertexes3d[i] - viewer->info.camera.x) +
                viewer->info.camera.x +
                width / 2;  // xz = (5000/(cz - z) * (x - cx) + cx + width / 2)
        viewer->info.vertexes2d[j + 1] =
                (height / 2 -
                 (viewer->info.vertexes3d[i + 1] - viewer->info.camera.y) +
                 viewer->info.camera.y);
        j += 2;
        i += 3;
    }
}

void central_proj(t_viewer *viewer, int width, int height) {
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < viewer->info.count_v * 2) {
        viewer->info.vertexes2d[j] =
                (5000 / (viewer->info.camera.z - viewer->info.vertexes3d[i + 2]) *
                 (viewer->info.vertexes3d[i] - viewer->info.camera.x) +
                 viewer->info.camera.x +
                 width / 2);
        viewer->info.vertexes2d[j + 1] =
                (height / 2 -
                 (5000 / (viewer->info.camera.z - viewer->info.vertexes3d[i + 2]) *
                  (viewer->info.vertexes3d[i + 1] - viewer->info.camera.y) +
                  viewer->info.camera.y));
        j += 2;
        i += 3;
    }
}