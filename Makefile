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

# Structure des sources
MAIN_SRCS   = main.c command_processor.c
BUILTINS_SRCS_RAW = builtins.c cd.c echo.c env_builtins.c exit.c export.c export_utils.c pwd.c unset.c
ENV_SRCS_RAW = env.c env_add.c env_init.c env_utils.c unset_utils.c var_expend.c var_verif.c
EXECUTE_SRCS_RAW = cmd_path_utils.c execute.c execute_command.c execute_utils.c utils.c
LEXING_SRCS_RAW = handle_quotes.c lex_pipe_redir.c lex_utils.c lexing.c
PARSER_SRCS_RAW = handle_redir.c parser.c parser_clean.c parser_utils.c
PIPES_SRCS_RAW = pipes.c pipes_utils.c
REDIRECTIONS_SRCS_RAW = heredoc.c heredoc_utils.c redirections.c redirections_utils.c
SIGNALS_SRCS_RAW = signaux.c
UTILS_SRCS_RAW = error.c free_shell.c shell_utils.c

# Préfixage des chemins complets
SRCS        = $(addprefix $(SRCS_DIR)/, $(MAIN_SRCS)) \
			  $(addprefix $(SRCS_DIR)/builtins/, $(BUILTINS_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/env/, $(ENV_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/execute/, $(EXECUTE_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/lexing/, $(LEXING_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/parser/, $(PARSER_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/pipes/, $(PIPES_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/redirections/, $(REDIRECTIONS_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/signaux/, $(SIGNALS_SRCS_RAW)) \
			  $(addprefix $(SRCS_DIR)/utils/, $(UTILS_SRCS_RAW))

# Fichiers objets
OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Règle principale
all: $(NAME)

# Création de l'exécutable
$(NAME): $(LIBFT) $(OBJS)
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
