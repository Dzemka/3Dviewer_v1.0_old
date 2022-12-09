NAME = viewer

SRC = main.c \
		run_app.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

OBJ_DIR = ./obj/

TEX2DVI = $(shell tex2dvi)

#FLAGS
	GTK_CFLAGS = $(shell pkg-config --cflags gtk4)
	GTK_LDFLAGS = $(shell pkg-config --libs gtk4)

	CFLAGS = $(GTK_CFLAGS)  #-Wall -Wextra -Werror
	LDFLAGS = $(GTK_LDFLAGS) -lreadline -L/usr/lib/x86_64-linux-gnu -lm

#COMMANDS
	CC = gcc
	RM = rm -rf

VPATH = ./src/

.PHONY	: all install uninstall clean  re dvi

all : install

install	:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o:%.c $(HEADERS)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean	:
			$(RM) $(OBJ_DIR)
uninstall	:	clean
			$(RM) $(NAME)
re 		: clean all

dvi :
	$(TEX2DVI)