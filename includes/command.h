/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:35:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 19:40:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
#include "minishell.h"

# include <sys/types.h>
# include "env.h"
# include "shell_data.h"
# include "execute.h"
# include "builtins.h"
# include "parser.h"
# include "signals.h"

typedef enum e_redir_type {
    REDIR_INPUT,     // <
    REDIR_OUTPUT,    // >
    REDIR_APPEND,    // >>
    REDIR_HEREDOC    // <<
} t_redir_type;

typedef struct s_redirection {
    char *file;               // Nom du fichier
    int type;                 // Type: INPUT, OUTPUT, APPEND, HEREDOC
    char *heredoc_content;    // Contenu du heredoc (si applicable)
    struct s_redirection *next; // Pointeur vers la prochaine redirection
} t_redirection;

typedef struct s_command
{
	char *cmd;               // Commande principale (ex: "ls", "grep", "echo")
	char **args;             // Liste des arguments (ex: ["ls", "-l", NULL])
	t_redirection	*redirections;
	// char *input_file;        // Fichier si redirection de stdin (ex: "input.txt" pour `< input.txt`)
	// char *output_file;       // Fichier si redirection de stdout (ex: "output.txt" pour `> output.txt`)
	// int append;              // Flag pour append : 1 = `>>`, 0 = `>`
	// char *heredoc;          // Le contenu du heredoc (si heredoc utilisé)
	struct s_command *next;  // Pointeur vers la commande suivante (en cas de pipe)
	struct s_command *prev;
	pid_t		pid;
	int is_builtin;          // 1 si c'est une commande builtin, 0 sinon
	int pipe_fd[2];
} t_cmd;

// Fonctions de gestion des commandes
t_cmd       	*create_command(void);
void            free_command(t_cmd *cmd);
void            free_command_list(t_cmd *cmd);
bool 			create_pipes(t_cmd *cmd_list);
int setup_redirection(t_redirection *redirections);
void			restore_io(int stdin_fd, int stdout_fd);

#endif