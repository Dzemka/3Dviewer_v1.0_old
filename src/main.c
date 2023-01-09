#include "viewer3D.h"

int main(int argc, char **argv, char **env) {
    int status;
    t_viewer *viewer;
    viewer = malloc(sizeof(t_viewer));
    // parser

    // graphics


//    parser("Camera.obj", viewer);

    //create init

    viewer->func_proj = &central_proj;
    viewer->info.edge_color.red = 255;
    viewer->info.edge_color.green = 0;
    viewer->info.edge_color.blue = 255;
    viewer->info.edge_thickness = 0.1;
    viewer->info.vertices_color.red = 0;
    viewer->info.vertices_color.green = 255;
    viewer->info.vertices_color.blue = 0;
    viewer->info.screenshot_file_name = malloc(sizeof(char *));
    viewer->info.screenshot_format = malloc(sizeof(char *));
    *viewer->info.screenshot_file_name = NULL;
    *viewer->info.screenshot_format = strdup("jpeg");
    viewer->info.make_screenshot = 0;
    viewer->reparse = 0;

//    viewer->filename = malloc(sizeof(char *));
//    viewer->filename = strdup("Camera.obj");
    viewer->filename = NULL;

    status = run_app(argc, argv, viewer);
    //graphics
    return (0);
}