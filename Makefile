CC=cc
NAME=fdf

CMP_FLAGS=-Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3
MLX_FLAGS=-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz



SRC_MAIN=main.c
SRC_OBJ=main.o

OBJ_ALL=$(SRC_OBJ)

%.o: %.c
	$(CC) $(CMP_FLAGS) -c $< -o $@


all: $(NAME)

$(NAME): $(OBJ_ALL)
		$(CC) $(OBJ_ALL) $(MLX_FLAGS) -o $(NAME)



clean:
	$(RM) $(OBJ_ALL)
fclean: clean
	$(RM) $(NAME)
