#include "../viewer3D.h"

static FILE *get_file(const char *s) {
    FILE *file;

    file = fopen(s, "r");
    if (!file) printf("cannot open file\n");
    return (file);
}

int parse_values(char **line, t_viewer *viewer) {
    char **split_line;
    int status;

    split_line = ft_split((*line) + 2, ' ');
    if ((*line)[0] == 'v')
        status = parse_vertex(split_line, viewer);
    else
        status = parse_face(split_line, viewer);
    free(*line);
    clean_massive_2d(&split_line);
    return (status);
}

static int parse_file(FILE **file, t_viewer *viewer) {
    char *line;
    size_t len;

    line = NULL;
    if (getline(&line, &len, *file) == -1) return (1);
//    printf("s\n");
    if (len > 2) {
        if ((line[0] == 'v' || line[0] == 'f') && line[1] == ' ')
            return (parse_values(&line, viewer));
    }
    return (0);
}

int parser(const char *s, t_viewer *viewer) {
    FILE *file;
    int read_end;

    file = get_file(s);
    if (!file) return (1);
    viewer->vertex_list = NULL;
    viewer->info.faces = NULL;
    viewer->info.vertexes2d = NULL;
    viewer->info.vertexes3d = NULL;
    viewer->info.count_v = 0;
    read_end = 0;
    while (!read_end) read_end = parse_file(&file, viewer);
    fclose(file);
    set_values(viewer);

//    double width;
//    double height;
//
//    width = (viewer->dimensions.x_max - viewer->dimensions.x_min);
    viewer->info.camera.x = 0;
    viewer->info.camera.y = 0;
    viewer->info.camera.z = viewer->dimensions.z_max + 200;
//
//    height = (viewer->dimensions.y_max - viewer->dimensions.y_min);
//
//
//    if (width > height)
//    {
//        viewer->info.camera.z = viewer->dimensions.z_max + width / 2;
////        viewer->info.camera.screen_z = 680 * height / width;
//    }
//    else {
//        viewer->info.camera.screen_z = 540;
//        viewer->info.camera.z = viewer->dimensions.z_max + height / 2;
//    }

//    viewer->info.camera.screen_z = viewer->info.camera.z * 1360 / width;

    printf("%ld\n", viewer->info.count_v);
}