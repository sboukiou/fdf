CC=cc
NAME=fdf

CMP_FLAGS=-Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -g
MLX_FLAGS=-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

MAIN_SRCS=main.c drawer.c geometry.c mlx_spec.c
MAIN_OBJS=$(MAIN_SRCS:%.c=%.o)

LIBFT_DIR=./dependencies/libft
PRINTF_DIR=./dependencies/ft_printf

LIBFT_SRCS=$(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_isdigit.c $(LIBFT_DIR)/ft_split.c $(LIBFT_DIR)/ft_strlen.c\
		   $(LIBFT_DIR)/ft_bzero.c $(LIBFT_DIR)/ft_itoa.c $(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_memcpy.c\
		   $(LIBFT_DIR)/ft_strncmp.c $(LIBFT_DIR)/ft_calloc.c  $(LIBFT_DIR)/ft_memset.c   $(LIBFT_DIR)/ft_strlcpy.c
LIBFT_OBJS=$(LIBFT_SRCS:%.c=%.o)

PRINTF_SRCS=$(PRINTF_DIR)/format_handler.c  $(PRINTF_DIR)/ft_printf.c  $(PRINTF_DIR)/printers.c
PRINTF_OBJS=$(PRINTF_SRCS:%.c=%.o)

DEPS=$(LIBFT_OBJS) $(PRINTF_OBJS)


OBJ_ALL=$(MAIN_OBJS) $(LIBFT_OBJS) $(PRINTF_OBJS)

%.o: %.c
	$(CC) $(CMP_FLAGS) -c $< -o $@


all: $(NAME)

$(NAME): $(OBJ_ALL)
		$(CC)  $(OBJ_ALL)  $(MLX_FLAGS) -o $(NAME)



clean:
	$(RM) $(OBJ_ALL)
fclean: clean
	$(RM) $(NAME)
