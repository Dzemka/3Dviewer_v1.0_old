NAME = viewer

SRC = main.c \
		run_app.c \
		gui_activate.c \
		draw_model.c \
		buttons_manager.c \
		button_x.c \
		button_y.c \
		button_z.c \
		button_zoom.c \
		matrix_transformation.c \
		parser.c \
		parse_value.c \
		set_values.c \
		ft_split.c \
		list_utils.c \
		utils.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_DIR = ./obj/

HEADER = src/viewer3D.h

TEX2DVI = $(shell tex2dvi)

#FLAGS
#	GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
#	GTK_LDFLAGS = $(shell pkg-config --libs gtk4)

	GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
	GTK_LDFLAGS = $(shell pkg-config --libs gtk4)

	CFLAGS = $(GTK_CFLAGS) #-Wall -Wextra -Werror
	LDFLAGS = $(GTK_LDFLAGS) -lm

#COMMANDS
	CC = gcc
	RM = rm -rf

VPATH = ./src/ ./src/parser ./src/buttons_manager

.PHONY	: all install uninstall clean  re dvi

all : install

install	:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:%.c $(HEADER)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean	:
			$(RM) $(OBJ_DIR)
uninstall	:	clean
			$(RM) $(NAME)
re 		: clean all

dvi :
	$(TEX2DVI)