#include "../viewer3D.h"

static void dec_to_hex(char **rgb_hex, int decimal) {
  int i;

  i = 5;
  while (decimal) {
    (*rgb_hex)[i] = decimal % 16;
    if ((*rgb_hex)[i] < 10)
      (*rgb_hex)[i] += 48;
    else
      (*rgb_hex)[i] += 55;
    decimal /= 16;
    i--;
  }
}

static void fill_str_rgb_hex(char *str, GdkRGBA rgb) {
  char *rgb_str;
  int rgb_decimal;
  char *rgb_hex;
  char **split_rgb;

  rgb_str = gdk_rgba_to_string(&rgb);
  split_rgb = ft_split(strchr(rgb_str, '(') + 1, ',');
  if (!split_rgb) exit_message("Malloc error\n");
  rgb_decimal = atoi(split_rgb[0]) * 256 * 256 + atoi(split_rgb[1]) * 256 +
                atoi(split_rgb[2]);
  rgb_hex = strdup("000000");
  dec_to_hex(&rgb_hex, rgb_decimal);
  memcpy(str, rgb_hex, 6);
  free(rgb_str);
  free(rgb_hex);
}

char *get_label_str(t_viewer *viewer) {
  char *temp;
  char *str;
  char *res;
  temp = ft_itoa(viewer->info.count_v);
  str = ft_strjoin(viewer->filename, " ");
  res = ft_strjoin(str, temp);
  free(str);
  free(temp);
  return (res);
}

void create_stringlabel(t_viewer *viewer) {
  char *str;
  char *label_string;
  int i, j;

  label_string = get_label_str(viewer);
  str = strdup(
      "<span style=\"italic\" background=\"#RRGGBB\" foreground=\"#RRGGBB\" "
      "font-size=\"25pt\">\%s</span>");
  fill_str_rgb_hex(str + 34, viewer->settings.background_color);
  fill_str_rgb_hex(str + 55, viewer->settings.edge_color);
  char *markup;
  markup = g_markup_printf_escaped(str, label_string);
  free(str);
  free(label_string);
  gtk_label_set_markup(GTK_LABEL(viewer->label_filename), markup);
  g_free(markup);
}