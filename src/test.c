// gcc $( pkg-config --cflags gtk4 ) -o test test.c $( pkg-config --libs gtk4 )

#include "viewer3D.h"

int main(int argc, char **argv, char **env) {
	t_viewer *viewer;
	int result;

	viewer = malloc(sizeof(t_viewer));
	viewer->vertex_list = NULL;
    viewer->info.faces = NULL;
    viewer->info.vertexes2d = NULL;
    viewer->info.vertexes3d = NULL;
	viewer->info.count_v = 0;
	viewer->dimensions.x_min = 0;
	viewer->dimensions.x_max = 0;
	viewer->dimensions.y_min = 0;
	viewer->dimensions.y_max = 0;
	viewer->dimensions.z_min = 0;
	viewer->dimensions.z_max = 0;
	viewer->info.width = 1360;
	viewer->info.height = 1000;

    //файл не существует
    result = parser("tests/test1", viewer);
    if (result == 1) printf("Parser Tets1: OK\n");
    else printf("Parser Tets1: NO\n");
	free_all(viewer);
    
	//файл не имеет формат .obj
    result = parser("tests/test2_file", viewer);
    if (result == 1) printf("Parser Tets2: OK\n");
    else printf("Parser Tets2: NO\n");
	free_all(viewer);

    // //файл закрыт на чтение
    // result = parser("tests/test3_file.obj", viewer);
    // if (result == 1) printf("Parser Tets3: OK\n");
    // else printf("Parser Tets3: NO\n");
	// free_all(viewer);

    //в файле нет точек
    result = parser("tests/test4_file.obj", viewer);
    if (!result && !viewer->info.count_v) printf("Parser Tets4: OK\n");//доделать
    else printf("Parser Tets4: NO\n");
	free_all(viewer);
	
    //у точек недостаточно координат
    result = parser("tests/test5_file.obj", viewer);
    if (result) printf("Parser Tets5: OK\n");
    else printf("Parser Tets5: NO\n");
	free_all(viewer);

    //у плоскости меньше 3 точек
	result = parser("tests/test6_file.obj", viewer);
    if (result == 1) printf("Parser Tets6: OK\n");
    else printf("Parser Tets6: NO\n");
	free_all(viewer);

	// free(viewer);
	// return(0);

    //плоскость ссылается на несуществующую точку
    result = parser("tests/test7_file.obj", viewer);
    if (result == 1) printf("Parser Tets7: OK\n");
    else printf("Parser Tets7: NO\n");
	free_all(viewer);

	//хороший файл
	result = parser("tests/test8_file.obj", viewer);
	if (!result && viewer->info.count_v == 5)
	{
		int i;
		int j = 0;
		double vertexes[15] = {1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0};
		size_t faces[6] = {1, 2, 3, 4, 2, 5};
		t_list *tmp = viewer->vertex_list;
		while (tmp)
		{
			i = 0;
			while (i < 3)
			{
				if (((double *)tmp->content)[i] != vertexes[j])
				{
					printf("Parser Tets8: NO\n");
					tmp = NULL;
					break;
				}
				i++;
				j++;
			}
			if (tmp) tmp = tmp->next;
		}
		if (j == 15)
		{
			j = 0;
			t_list *tmp = viewer->info.faces;
			while (tmp)
			{
				i = 0;
				while (i < ((t_plane *)tmp->content)->size)
				{
					if (j > 5 || ((size_t *)((t_plane *)tmp->content)->indexes)[i] != faces[j])
					{
						tmp = NULL;
						j = 0;
						break;
					}
					i++;
					j++;
				}
				if (tmp) tmp = tmp->next;
			}
			if (j == 6) printf("Parser Tets8: OK\n");
			else printf("Parser Tets8: NO\n");
		}
	}
	else printf("Parser Tets8: NO\n");
	free_all(viewer);

// 	printf("length = %ld\n", strlen("<span style=\"italic\" background=\"#000000\" foreground=\"#FFFFFF\" font-size=\"25pt\">\%s</span>"));
// 	char color_bg[] = "HHHHHH", color_fg[] = "LLLLLL";
//   char *str;
//   int i, j;
//   str = strdup("<span style=\"italic\" background=\"#000000\" foreground=\"#FFFFFF\" font-size=\"25pt\">\%s</span>");
// 	printf("%s\n", str);
//   i = 34;
//   j = 0;
//   while(i < 40)
//     str[i++] = color_bg[j++];
//   i = 55;
//   j = 0;
//   while(i < 61)
//     str[i++] = color_fg[j++];
// 	printf("%s\n", str);
// 	free(str);
	// viewer->settings.background_color.red = 200;
	// char a = (int)viewer->settings.background_color.red / 16;
	// if (a < 10) a += 48;
	// else a += 55;
	// char b = (int)viewer->settings.background_color.red % 16;
	// if (b < 10) b += 48;
	// else b += 55;
	// printf("%X\n",(int)viewer->settings.background_color.red);
	// printf("%c %c\n",a, b);
	free(viewer);
}