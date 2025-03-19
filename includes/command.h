/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:35:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/19 17:20:24 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <sys/types.h>

typedef struct s_command
{
	char *cmd;               // Commande principale (ex: "ls", "grep", "echo")
	char **args;             // Liste des arguments (ex: ["ls", "-l", NULL])
	char *input_file;        // Fichier si redirection de stdin (ex: "input.txt" pour `< input.txt`)
	char *output_file;       // Fichier si redirection de stdout (ex: "output.txt" pour `> output.txt`)
	int append;              // Flag pour append : 1 = `>>`, 0 = `>`
	char *heredoc;          // Le contenu du heredoc (si heredoc utilisé)
	struct s_command *next;  // Pointeur vers la commande suivante (en cas de pipe)
	struct s_command *prev;
	pid_t		pid;
	int is_builtin;          // 1 si c'est une commande builtin, 0 sinon
	int pipe_fd[2];
} t_command;

// Fonctions de gestion des commandes
t_command       *create_command(void);
void            free_command(t_command *cmd);
void            free_command_list(t_command *cmd);
int             create_pipes(t_command *cmd);
int             check_redirections(t_command *cmd);
int				setup_redirection(const char *input_file, const char *output_file, int append);
void            restore_io(int stdin_backup, int stdout_backup);

#endif