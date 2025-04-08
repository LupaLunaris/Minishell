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

# Règles pour le testing et debugging

# Règle pour tester les fuites de mémoire avec Valgrind
valgrind: $(NAME)
	@echo "🔍 Lancement avec Valgrind pour vérifier les fuites..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)

# Règle pour tester les fuites avec option de suppression des erreurs de readline
valgrind-readline: readline-supp $(NAME)
	@echo "🔍 Lancement avec Valgrind (suppression des erreurs readline)..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --suppressions=readline.supp ./$(NAME)

# Règle pour générer un fichier de suppression pour readline
readline-supp:
	@echo "📝 Génération du fichier de suppression readline.supp..."
	@echo "{\n   <Readline>\n   Memcheck:Leak\n   match-leak-kinds: reachable\n   ...\n   fun:readline\n}\n{\n   <AddHistory>\n   Memcheck:Leak\n   match-leak-kinds: reachable\n   ...\n   fun:add_history\n}" > readline.supp

# Règle pour tester avec un analyseur statique
analyze:
	@echo "🔬 Analyse statique du code..."
	scan-build make re

# Règle pour tester avec l'AddressSanitizer et l'UBSanitizer
sanitize: CFLAGS += -fsanitize=address,undefined -g
sanitize: re
	@echo "🧪 Exécution avec sanitizers..."
	./$(NAME)

# Règle pour tester avec des outils de détection de fuites spécifiques à macOS
leaks: $(NAME)
	@echo "🔍 Exécution avec l'outil leaks de macOS..."
	leaks -atExit -- ./$(NAME)

# Règle pour exécuter avec un input spécifique
test-cmd: $(NAME)
	@echo "🧪 Test avec commande spécifique: $(CMD)"
	echo "$(CMD)" | ./$(NAME)

# Règles phony pour éviter des conflits avec des fichiers du même nom
.PHONY: all clean fclean re valgrind valgrind-readline readline-supp analyze sanitize leaks test-cmd
