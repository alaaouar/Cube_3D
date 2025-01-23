CC		= cc
SRC		= get_next_line.c get_next_line_utils.c main.c utils.c map_draw.c
NAME	= Cube_3D
CFLAGS	= #-Wall -Wextra -Werror
CLIBS	= -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz
OBJ		= $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(CLIBS) -o $(NAME) 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re