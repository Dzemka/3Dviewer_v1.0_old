#include "../viewer3D.h"

void  create_stringlabel(char *text, t_viewer *viewer)
{
  char *str;
  int i, j;

  str = strdup("<span style=\"italic\" background=\"#AAAAAA\" foreground=\"#FFFFFF\" font-size=\"25pt\">\%s</span>");
  printf("%s\n", str);
  str[34] = (int)(viewer->settings.background_color.red * 255) / 16;
	if (str[34] < 10) str[34] += 48;
	else str[34] += 55;
  str[35] = (int)(viewer->settings.background_color.red * 255) % 16;
	if (str[35] < 10) str[35] += 48;
	else str[35] += 55;
  str[36] = (int)(viewer->settings.background_color.green * 255) / 16;
	if (str[36] < 10) str[36] += 48;
	else str[36] += 55;
  str[37] = (int)(viewer->settings.background_color.green * 255) % 16;
	if (str[37] < 10) str[37] += 48;
	else str[37] += 55;
  str[38] = (int)(viewer->settings.background_color.blue * 255) / 16;
	if (str[38] < 10) str[38] += 48;
	else str[38] += 55;
  str[39] = (int)(viewer->settings.background_color.blue * 255) % 16;
	if (str[39] < 10) str[39] += 48;
	else str[39] += 55;

  printf("%s\n", str);

  // i = 55;
  // j = 0;
  // while(i < 61)
  //   str[i++] = color_fg[j++];

  char *markup;
  markup = g_markup_printf_escaped(str, text);
  free(str);
  gtk_label_set_markup(GTK_LABEL(viewer->label_filename), markup);
  g_free(markup);
}

static void enter(GtkButton *btn, t_viewer *viewer) {
  const char *s;
  int i;
  int result;

  if (viewer->info.make_screenshot != 0) return;

  viewer->filename = strdup(gtk_entry_buffer_get_text(
      gtk_entry_get_buffer(GTK_ENTRY(viewer->entry.entry_file))));
  // подготовить особождение перед открытием нового файла
  free_all(viewer);
  result = parser(viewer->filename, viewer);

  if (result == 1)
  {
    free_all(viewer);
    return;
  }

  viewer->info.vertexes3d = malloc(sizeof(double) * viewer->info.count_v * 3);
  viewer->info.vertexes2d = malloc(sizeof(double) * viewer->info.count_v * 2);
  set_values(viewer);

  char *temp;
  char *str;
  char *res;
  temp = ft_itoa(viewer->info.count_v);
  str = ft_strjoin(viewer->filename, " ");
  res = ft_strjoin(str, temp);
  free(str);
  free(temp);
  //    temp = ft_strjoin(viewer->filename, str);
  create_stringlabel(res, viewer);
  free(res);

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
  button_proj(viewer, box_left);
  set_background_color(viewer, box_left);
  set_type_edge(viewer, box_left);
  set_color_edge(viewer, box_left);
  set_thickness_edge(viewer, box_left);
  set_type_vertices(viewer, box_left);
  set_color_vertices(viewer, box_left);
  set_size_vertices(viewer, box_left);
  set_screenshot_frame(viewer, box_right);
  set_gif_frame(viewer, box_right);
  set_resize_frame(viewer, box_right);
}