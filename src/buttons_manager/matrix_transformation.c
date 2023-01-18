#include "../viewer3D.h"

void rotate(double *vertexes3d, size_t count_coord, int axes, double degree)
{
    int i;
    double coord1;
    double coord2;
    int el1;
    int el2;

    if (degree > 1000000)
      return ;
    degree *= M_PI / 180;
    el1 = (axes + 1) % 3;
    el2 = (axes + 2) % 3;
    i = 0;
    while (i < count_coord)
    {
        coord1 = vertexes3d[i + el1] * cos(degree) + vertexes3d[i + el2] * sin(degree);
        coord2 = -1 * vertexes3d[i + el1] * sin(degree) + vertexes3d[i + el2] * cos(degree);
        vertexes3d[i + el1] = coord1;
        vertexes3d[i + el2] = coord2;
        i += 3;
    }
}

void zoom(double *vertexes3d, size_t count_coord, double scale)
{
    int i;

    i = -1;
    while (++i < count_coord)
        vertexes3d[i] *= scale;
}

void move(double *vertexes3d, size_t count_coord, int axes, double move_step)
{
    int i;

    i = 0;
    while (i < count_coord)
    {
        vertexes3d[i + axes] += move_step;
        i += 3;
    }
}