#include "viewer3D.h"

int main(int argc, char **argv, char **env) {
    int status;
    t_viewer *viewer;
    viewer = malloc(sizeof(t_viewer));
    // parser

    // graphics
    viewer->vertex_list = NULL;
    viewer->info.faces = NULL;
    viewer->info.vertexes2d = NULL;
    viewer->info.vertexes3d = NULL;
    viewer->info.count_v = 0;

//    parser("Camera.obj", viewer);

    //create init
    viewer->info.camera.x = 0;
    viewer->info.camera.y = 0;
    viewer->info.camera.z = viewer->dimensions.z_max + 200;
    viewer->func_proj = &central_proj;
    viewer->info.edge_color.red = 255;
    viewer->info.edge_color.green = 0;
    viewer->info.edge_color.blue = 255;
    viewer->info.edge_thickness = 1;
    viewer->info.vertices_color.red = 0;
    viewer->info.vertices_color.green = 255;
    viewer->info.vertices_color.blue = 0;
    viewer->info.screenshot_file_name = malloc(sizeof(char *));
    viewer->info.screenshot_format = malloc(sizeof(char *));
    *viewer->info.screenshot_file_name = NULL;
    *viewer->info.screenshot_format = strdup("jpeg");
    viewer->info.make_screenshot = 0;

//    viewer->filename = malloc(sizeof(char *));
//    *viewer->filename = strdup("Camera.obj");
    status = run_app(argc, argv, viewer);
    //graphics
    return (0);
}