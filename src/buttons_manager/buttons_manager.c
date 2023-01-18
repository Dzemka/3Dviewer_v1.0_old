#include "../viewer3D.h"

void tester(t_viewer *viewer) {
  printf("%ld\n", viewer->info.count_v);

  //  int m[viewer->info.count_v][viewer->info.count_v];
  int **m;
  int i;

  m = malloc(sizeof(int *) * viewer->info.count_v);
  i = -1;
  while (++i < viewer->info.count_v)
    m[i] = malloc(sizeof(int) * viewer->info.count_v);
  t_list *list;
  t_plane *plane;
  double coord_x;
  double coord_y;
  size_t index_vertex1;
  size_t index_vertex2;

  list = viewer->info.faces;
  int j;

  i = -1;
  while (++i < viewer->info.count_v) {
    j = -1;
    while (++j < viewer->info.count_v) {
      m[i][j] = 0;
    }
  }
  printf("ok\n");
  j = 0;

  viewer->info.count_edge = 0;
  while (list) {
    j++;
    plane = (t_plane *)list->content;
    i = -1;
    while (++i < (int)plane->size) {
      index_vertex1 = (plane->indexes[i] - 1);
      index_vertex2 = (plane->indexes[(i + 1) % plane->size] - 1);
      if (m[index_vertex1][index_vertex2] == 0) {
        m[index_vertex1][index_vertex2] = 1;
        m[index_vertex2][index_vertex1] = 1;
        viewer->info.count_edge++;
      }
    }
    list = list->next;
  }
  printf("%ld\n", viewer->info.count_edge);
  i = -1;
  while (++i < viewer->info.count_v) free(m[i]);
  free(m);
}

static void enter(GtkButton *btn, t_viewer *viewer) {
  const char *s;
  int i;

  if (viewer->info.make_screenshot != 0) return;

  viewer->filename = strdup(gtk_entry_buffer_get_text(
      gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_file))));
  clean_info(viewer);
  if (parser(viewer->filename, viewer) == 1) {
    create_stringlabel(viewer);
    clean_info(viewer);
    return;
  }
  set_values(viewer);
  //  tester(viewer);
  create_stringlabel(viewer);
  gtk_widget_queue_draw(viewer->model);
}

static void button_transformation(t_viewer *viewer, GtkWidget *box_buttons) {
  fill_frame_moving(viewer, box_buttons);
  fill_frame_rotating(viewer, box_buttons);
  fill_frame_scaling(viewer, box_buttons);
}

void button_entry_file(t_viewer *viewer, GtkWidget *box_buttons) {
  GtkWidget *frame;
  GtkWidget *box_entry_file;
  GtkWidget *button;

  frame = gtk_frame_new("Select file");
  gtk_frame_set_label_align(GTK_FRAME(frame), 0.5);
  gtk_box_append(GTK_BOX(box_buttons), frame);
  box_entry_file = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_frame_set_child(GTK_FRAME(frame), box_entry_file);
  viewer->entry.entry_file = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(viewer->entry.entry_file),
                                 "input file");
  button = gtk_button_new_with_label("Enter file");
  gtk_box_append(GTK_BOX(box_entry_file), viewer->entry.entry_file);
  gtk_box_append(GTK_BOX(box_entry_file), button);
  g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(enter), viewer);
}

void buttons_manager(t_viewer *viewer, GtkWidget *box_left,
                     GtkWidget *box_right) {
  button_entry_file(viewer, box_left);
  button_transformation(viewer, box_left);

  set_screenshot_frame(viewer, box_right);
  set_gif_frame(viewer, box_right);
  set_resize_frame(viewer, box_left);

  button_proj(viewer, box_right);
  set_background_color(viewer, box_right);
  set_type_edge(viewer, box_right);
  set_color_edge(viewer, box_right);
  set_thickness_edge(viewer, box_right);
  set_type_vertices(viewer, box_right);
  set_color_vertices(viewer, box_right);
  set_size_vertices(viewer, box_right);
}