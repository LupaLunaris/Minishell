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

# Variables pour la barre de progression
TOTAL_FILES := $(words $(ALL_SRCS))

# Couleurs
RED = \033[1;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
RESET = \033[0m

# Règle principale
all: $(LIBFT) compile_start $(NAME)

compile_start:
	@echo "🚀 Début de la compilation de $(TOTAL_FILES) fichiers..."

# Création de l'exécutable
$(NAME): $(OBJS)
	@echo "\n🔨 Création de l'exécutable $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "${GREEN}✅ Compilation de $(NAME) terminée !${RESET}"

# Variable pour suivre les fichiers compilés
COMPILE_COUNT = 0

# Génération des objets avec barre de progression mise à jour
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@$(eval COMPILE_COUNT=$(shell echo $$(($(COMPILE_COUNT) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(COMPILE_COUNT) * 100 / $(TOTAL_FILES)))))
	@printf "\r\033[K⏳ Progression: [${RED}%-50s${RESET}] %3d%% (%d/%d)" \
		"$(shell printf '█%.0s' $$(seq 1 $$(($(PERCENT) * 50 / 100))))" \
		$(PERCENT) $(COMPILE_COUNT) $(TOTAL_FILES)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@echo "${BLUE}🔧 Compilation de la libft...${RESET}"
	@$(MAKE) -s -C $(LIBFT_DIR)

# Nettoyage des fichiers objets
clean:
	@echo "${YELLOW}🧹 Suppression des fichiers objets...${RESET}"
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@echo "${GREEN}🧹 Nettoyage terminé.${RESET}"

# Nettoyage complet (inclut les objets + exécutable)
fclean: clean
	@echo "${YELLOW}🧹 Suppression de l'exécutable $(NAME)...${RESET}"
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@echo "${GREEN}🧹 Nettoyage complet terminé.${RESET}"

# Recompiler tout
re: fclean all

# Règles phony pour éviter des conflits avec des fichiers du même nom
.PHONY: all clean fclean re compile_start

# Règle pour voir l'état du projet
status:
	@echo "📊 État du projet:"
	@echo "  - Nombre total de fichiers sources: $(TOTAL_FILES)"
	@if [ -f "$(NAME)" ]; then \
		echo "  - Exécutable '$(NAME)': ${GREEN}✅ Présent${RESET}"; \
	else \
		echo "  - Exécutable '$(NAME)': ${RED}❌ Absent${RESET}"; \
	fi
	@echo "  - Libft: $(shell if [ -f "$(LIBFT)" ]; then echo "${GREEN}✅ Compilée${RESET}"; else echo "${RED}❌ Non compilée${RESET}"; fi)"
