# Compiler et drapeaux
CC			= gcc
INCLUDES	= -Iincludes -Ilibft_19

# Nom de l'exécutable final
NAME		= minishell

# Dossiers
SRCS_DIR	= srcs
OBJS_DIR	= objs
LIBFT_DIR	= libft_19

# Sous-dossiers des sources
BUILTINS_DIR	= $(SRCS_DIR)/builtins
EXECUTE_DIR		= $(SRCS_DIR)/execute
UTILS_DIR		= $(SRCS_DIR)/utils

# Nom de la bibliothèque libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Sources
SRCS		= $(SRCS_DIR)/main.c \
			$(SRCS_DIR)/signaux.c \
			$(BUILTINS_DIR)/cd.c \
			$(BUILTINS_DIR)/echo.c \
			$(EXECUTE_DIR)/redirections.c \
			$(EXECUTE_DIR)/pipes.c \
			$(EXECUTE_DIR)/builtins.c \
			$(EXECUTE_DIR)/execute.c \
			$(UTILS_DIR)/clean_exit.c \
			$(UTILS_DIR)/error.c

# Objets
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Règles Makefile
all: $(LIBFT) $(NAME)

# Compilation de l'exécutable final, en liant libft
$(NAME): $(OBJS)
	@echo "Compilation de $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) -o $(NAME)
	@echo "Compilation terminée avec succès ✅"

# Compiler les fichiers objets pour le projet principal
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D) # Crée le dossier objs/ s'il n'existe pas
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@echo "Compilation de la libft..."
	$(MAKE) -C $(LIBFT_DIR)

# Nettoyer les fichiers objets
clean:
	@echo "Suppression des fichiers objets..."
	rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

# Nettoyer tout (objets + exécutable)
fclean: clean
	@echo "Suppression de l'exécutable $(NAME)..."
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

# Recompiler tout
re: fclean all

# Règles pour éviter des erreurs sur des noms de fichiers
.PHONY: all clean fclean re
