/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:35:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/05 23:00:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H


# include <sys/types.h>

typedef enum e_redir_type {
    REDIR_INPUT,     // <
    REDIR_OUTPUT,    // >
    REDIR_APPEND,    // >>
    REDIR_HEREDOC    // <<
} t_redir_type;

typedef struct s_redirection {
    char *file;                    // Nom du fichier
    t_redir_type type;             // Type: utilise l'enum t_redir_type
    char *heredoc_content;         // Contenu du heredoc (si applicable)
    struct s_redirection *next;    // Pointeur vers la prochaine redirection
} t_redirection;


typedef struct s_command
{
	char *cmd;               // Commande principale (ex: "ls", "grep", "echo")
	char **args;             // Liste des arguments (ex: ["ls", "-l", NULL])
	t_redirection	*redirections;
	struct s_command *next;  // Pointeur vers la commande suivante (en cas de pipe)
	struct s_command *prev;
	pid_t		pid;
	int is_builtin;          // 1 si c'est une commande builtin, 0 sinon
	int pipe_fd[2];
	int infile;              // Descripteur de fichier d'entrée
    int outfile;             // Descripteur de fichier de sorti
} t_cmd;

// Fonctions de gestion des commandes
t_cmd       	*create_command(void);
void            free_command(t_cmd *cmd);
void            free_command_list(t_cmd *cmd);
bool 			create_pipes(t_cmd *cmd_list);
int				setup_redirection(t_redirection *redirections);
void			restore_io(int stdin_fd, int stdout_fd);

#endif