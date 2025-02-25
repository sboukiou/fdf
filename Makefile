NAME=fdf

CC=cc -Wall -Werror -Wextra -I/usr/include -Imlx_linux -O3 -c
BUILD=cc -o
MLX_FLAGS=-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
RM=rm -f


MAN_SRCS=main.c
MAN_OBJS=$(MAN_SRCS:%.c=%.o)


%.o: %.c
	$(CC) $< -o $@

all: $(NAME)

$(NAME): $(MAN_OBJS)
	$(BUILD) $(NAME) $(MAN_OBJS) $(MLX_FLAGS)
clean:
	$(RM) $(MAN_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
