NAME = viewer
NAME_TEST = testing

SRC = main.c \
		run_app.c \
		gui_activate.c \
		draw_model.c \
		draw_settings.c \
		buttons_manager.c \
		fill_frame_moving.c \
		fill_frame_rotating.c \
		fill_frame_scaling.c \
		input_moving_x.c \
		input_moving_y.c \
		input_moving_z.c \
		input_rotating_x.c \
		input_rotating_y.c \
		input_rotating_z.c \
		button_proj.c \
		set_background_color.c \
		set_type_edge.c \
		set_color_edge.c \
		set_thickness_edge.c \
		set_type_vertices.c \
		set_color_vertices.c \
		set_size_vertices.c \
		set_screenshot_frame.c \
		set_gif_frame.c \
		set_resize_frame.c \
		projection.c \
		get_screenshot.c \
		matrix_transformation.c \
		parser.c \
		parse_value.c \
		set_values.c \
		ft_split.c \
		list_utils.c \
		ft_itoa.c \
		utils.c \
		save_settings.c \
		get_settings.c \
		parse_settings_from_file.c \
	
SRC_TEST = test.c \
		matrix_transformation.c \
		parser.c \
		parse_value.c \
		set_values.c \
		ft_split.c \
		list_utils.c \
		utils.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
OBJ_TEST = $(SRC_TEST:%.c=$(OBJ_TEST_DIR)%.o)

OBJ_DIR = ./obj/
OBJ_TEST_DIR = ./obj_test/

HEADER = src/viewer3D.h

TEX2DVI = $(shell tex2dvi)

#FLAGS
#	GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
#	GTK_LDFLAGS = $(shell pkg-config --libs gtk4)

	GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
	GTK_LDFLAGS = $(shell pkg-config --libs gtk4)

	CFLAGS = $(GTK_CFLAGS) #-Wall -Wextra -Werror
	LDFLAGS = $(GTK_LDFLAGS) -lm -lgd

#COMMANDS
	CC = gcc -g
	RM = rm -rf

VPATH = ./src/ ./src/parser ./src/buttons_manager

.PHONY	: all install uninstall clean  re dvi test

all : install

install	:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:%.c $(HEADER)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

test	:	$(NAME_TEST)

$(NAME_TEST):	$(OBJ_TEST)
		$(CC) $(OBJ_TEST) $(LDFLAGS) -o $(NAME_TEST)

$(OBJ_TEST_DIR)%.o:%.c $(HEADER)
				mkdir -p $(OBJ_TEST_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean	:
			$(RM) $(OBJ_DIR) $(OBJ_TEST_DIR)
uninstall	:	clean
			$(RM) $(NAME) $(NAME_TEST)
re 		: clean all

dvi :
	$(TEX2DVI)