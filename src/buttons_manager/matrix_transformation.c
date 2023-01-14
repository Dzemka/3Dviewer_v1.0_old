#include "../viewer3D.h"

void rotate(t_viewer *viewer, int axes, double rad)
{
    int i;
    double *m;
    double v1;
    double v2;
    int el1;
    int el2;

    el1 = (axes + 1) % 3;
    el2 = (axes + 2) % 3;
    i = 0;
    m = viewer->info.vertexes3d;
    while (i < viewer->info.count_v * 3)
    {
        v1 = m[i + el1] * cos(rad) + m[i + el2] * sin(rad);
        v2 = -1 * m[i + el1] * sin(rad) + m[i + el2] * cos(rad);
        m[i + el1] = v1;
        m[i + el2] = v2;
        i += 3;
    }
}

void zoom(t_viewer *viewer, double scale)
{
    int i;

    i = -1;
    while (++i < viewer->info.count_v * 3)
        viewer->info.vertexes3d[i] *= scale;
}

void move(t_viewer *viewer, int axes, double move_step)
{
    int i;

    i = 0; // добавить функцию пересчёта dimensions и добавить во все трансформации
    while (i < viewer->info.count_v * 3)
    {
        viewer->info.vertexes3d[i + axes] += move_step;
        i += 3;
    }
}