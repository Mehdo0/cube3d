# Nom de l'exécutable
NAME = so_long

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../includes -I../mlx -I../libft

# Dossiers et librairies
MLX_DIR = ../mlx
LIBFT_DIR = ../libft
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Flags de linkage
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Sources et objets
SRCS = main.c init.c move.c put_img.c parse_input.c valid_path.c create_map.c game_handler.c
OBJS = $(SRCS:.c=.o)

# Règle principale
all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "🔗 Linking objects to create $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(LIBFT_LIB) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

# Compilation de MLX
$(MLX_LIB):
	@echo "🛠 Building MiniLibX..."
	@make -C $(MLX_DIR)

# Compilation de Libft
$(LIBFT_LIB):
	@echo "🛠 Building Libft..."
	@make -C $(LIBFT_DIR)

# Nettoyage
clean:
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "🧹 Cleaned object files."

fclean: clean
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "🗑 Removed executable $(NAME)."

re: fclean all

.PHONY: all clean fclean re
