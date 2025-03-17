# Nom de l'exécutable
NAME = cub3D

# Compilateur et options
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Chemins des dépendances
MLX_PATH = mlx/
MLX_LIB = $(MLX_PATH)libmlx.a
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

# Flags pour MiniLibX
MLX_FLAGS = -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lXrandr -lXrender -lm -lz -lpthread

# Fichiers sources
CFILES = $(wildcard *.c) $(wildcard src/*.c)

# Objets
OBJECTS = $(CFILES:.c=.o)

# Couleurs pour les messages
G = \033[32m
R = \033[31m
Y = \033[33m
B = \033[34m
X = \033[0m

# Règle principale
all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

# Compilation des fichiers .c en .o
%.o : %.c
	@echo "$(Y)Compiling [$<]...$(X)"
	@$(CC) $(CFLAGS) -I$(MLX_PATH) -I$(LIBFT_PATH) -c -o $@ $<

# Linkage final
$(NAME): $(OBJECTS)
	@echo "$(Y)Linking objects to create [$(NAME)]...$(X)"
	@$(CC) $(CFLAGS) $(OBJECTS) $(MLX_LIB) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(G)Finished [$(NAME)]$(X)"

# Compilation de MiniLibX
$(MLX_LIB):
	@echo "$(B)Building MLX...$(X)"
	@make -C $(MLX_PATH)

# Compilation de Libft
$(LIBFT_LIB):
	@echo "$(B)Building Libft...$(X)"
	@make -C $(LIBFT_PATH)

# Nettoyage des fichiers objets
clean:
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) clean
	@rm -f $(OBJECTS)
	@echo "$(R)Removed objects$(X)"

# Nettoyage total
fclean: clean
	@make -C $(MLX_PATH) clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(R)Removed executable $(NAME)$(X)"

# Recompilation complète
re: fclean all

# Norminette
norm:
	@norminette $(CFILES) $(LIBFT_PATH)

.PHONY: all clean fclean re norm
