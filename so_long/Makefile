NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

MLX_PATH = mlx/
MLX_LIB = $(MLX_PATH)libmlx.a
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

CFILES = main.c \
		 init.c \
		 move.c \
		 put_img.c \
		 parse_input.c \
		 valid_path.c\
		 create_map.c \
		 game_handler.c

OBJECTS = $(CFILES:.c=.o)

G = \033[32m
R = \033[31m
Y = \033[33m
B = \033[34m
X = \033[0m

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

%.o : %.c
	@echo "$(Y)Compiling [$<]...$(X)"
	@$(CC) $(CFLAGS) -Imlx -c -o $@ $<

$(NAME): $(OBJECTS)
	@echo "$(Y)Linking objects to create [$(NAME)]...$(X)"
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJECTS) $(MLX_LIB) $(LIBFT_LIB) -o $(NAME)
	@echo "$(G)Finished [$(NAME)]$(X)"

$(MLX_LIB):
	@echo "$(B)Building MLX...$(X)"
	@make -C $(MLX_PATH) all

$(LIBFT_LIB):
	@echo "$(B)Building Libft...$(X)"
	@make -C $(LIBFT_PATH) all

clean:
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJECTS)
	@echo "$(R)Removed objects$(X)"

fclean: clean
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(R)Removed executable $(NAME)$(X)"

re: fclean all

norm:
	@norminette $(CFILES) $(LIBFT_PATH)

.PHONY: all clean fclean re norm
