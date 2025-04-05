# Compilateur et flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBS        = -lreadline
# Nom de l'exécutable
NAME		= minishell

# Chemins
SRCS_DIR	= srcs
OBJS_DIR	= objs
LIBFT_DIR	= libft_19
INCLUDES	= -Iincludes -I$(LIBFT_DIR)

# Libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Sous-dossiers des sources
BUILTINS_DIR	= $(SRCS_DIR)/builtins
EXECUTE_DIR		= $(SRCS_DIR)/execute
UTILS_DIR		= $(SRCS_DIR)/utils
SIGNALS_DIR		= $(SRCS_DIR)/signaux
ENV_DIR			= $(SRCS_DIR)/env
PARSER_DIR		= $(SRCS_DIR)/parser
LEXING_DIR		= $(SRCS_DIR)/lexing

# Fichiers sources
SRCS       = $(SRCS_DIR)/main.c \
			 $(SIGNALS_DIR)/signaux.c \
			 $(ENV_DIR)/env.c \
			 $(ENV_DIR)/env_add.c \
			 $(ENV_DIR)/env_init.c \
			 $(ENV_DIR)/env_utils.c \
			 $(BUILTINS_DIR)/cd.c \
			 $(BUILTINS_DIR)/echo.c \
			 $(BUILTINS_DIR)/env_builtins.c \
			 $(BUILTINS_DIR)/exit.c \
			 $(BUILTINS_DIR)/export.c \
			 $(BUILTINS_DIR)/export_utils.c \
			 $(BUILTINS_DIR)/unset.c \
			 $(BUILTINS_DIR)/pwd.c \
			 $(EXECUTE_DIR)/redirections.c \
			 $(EXECUTE_DIR)/pipes.c \
			 $(EXECUTE_DIR)/builtins.c \
			 $(EXECUTE_DIR)/execute.c \
			 $(EXECUTE_DIR)/execute_command.c \
			 $(EXECUTE_DIR)/utils.c \
			 $(EXECUTE_DIR)/heredoc.c \
			 $(EXECUTE_DIR)/heredoc_utils.c \
			 $(UTILS_DIR)/error.c \
			 $(UTILS_DIR)/free_shell.c \
			 $(ENV_DIR)/var_expend.c \
			 $(ENV_DIR)/var_expend2.c \
			 $(PARSER_DIR)/parser.c \
			 $(PARSER_DIR)/parser_clean.c \
			 $(PARSER_DIR)/handle_redir.c \
			 $(PARSER_DIR)/parser_utils.c \
			 $(LEXING_DIR)/lexing.c \
			 $(LEXING_DIR)/lex_utils.c \
			 $(LEXING_DIR)/lex_pipe_redir.c \
			 $(LEXING_DIR)/handle_quotes.c \



# Fichiers objets
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Règle principale
all: $(LIBFT) $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	@echo "🔨 Création de l'exécutable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "✅ Compilation de $(NAME) terminée !"

# Génération des objets
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D) # Crée les sous-dossiers dans objs/ si besoin
	@echo "🛠️  Compilation de $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@echo "🔧 Compilation de la libft..."
	$(MAKE) -C $(LIBFT_DIR)

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
