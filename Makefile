CC          = cc
CFLAGS      = -Wall -Wextra -Werror
LIBS        = -lreadline

# Nom de l'exécutable
NAME        = minishell

# Chemins
SRCS_DIR    = srcs
OBJS_DIR    = objs
LIBFT_DIR   = libft_19
INCLUDES    = -Iincludes -I$(LIBFT_DIR)

# Libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Sources principales
SRCS        = $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/command_processor.c

# Sources des builtins
BUILTINS_SRCS = $(wildcard $(SRCS_DIR)/builtins/*.c)

# Sources des exécutions
EXECUTE_SRCS = $(wildcard $(SRCS_DIR)/execute/*.c)

# Sources des utilitaires
UTILS_SRCS = $(wildcard $(SRCS_DIR)/utils/*.c)

# Sources des signaux
SIGNALS_SRCS = $(wildcard $(SRCS_DIR)/signaux/*.c)

# Sources de l'environnement
ENV_SRCS = $(wildcard $(SRCS_DIR)/env/*.c)

# Sources du parser
PARSER_SRCS = $(wildcard $(SRCS_DIR)/parser/*.c)

# Sources du lexing
LEXING_SRCS = $(wildcard $(SRCS_DIR)/lexing/*.c)

# Sources des redirections
REDIR_SRCS = $(wildcard $(SRCS_DIR)/redirections/*.c)

# Sources des pipes
PIPES_SRCS = $(wildcard $(SRCS_DIR)/pipes/*.c)

# Combinaison de toutes les sources
ALL_SRCS = $(SRCS) $(BUILTINS_SRCS) $(EXECUTE_SRCS) $(UTILS_SRCS) \
		   $(SIGNALS_SRCS) $(ENV_SRCS) $(PARSER_SRCS) $(LEXING_SRCS) \
		   $(REDIR_SRCS) $(PIPES_SRCS)

# Fichiers objets
OBJS = $(ALL_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Règle principale
all: $(LIBFT) $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	@echo "🔨 Création de l'exécutable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "✅ Compilation de $(NAME) terminée !"

# Génération des objets
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@echo "🛠️ Compilation de $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@echo "🔧 Compilation de la libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Nettoyage des fichiers objets
clean:
	@echo "🧹 Suppression des fichiers objets..."
	rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

# Nettoyage complet (inclut les objets + exécutable)
fclean: clean
	@echo "🧹 Suppression de l'exécutable $(NAME)..."
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

# Recompiler tout
re: fclean all

# Règles phony pour éviter des conflits avec des fichiers du même nom
.PHONY: all clean fclean re