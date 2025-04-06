/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:35:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 10:31:25 by Jpaulis          ###   ########.fr       */
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
char	*find_command_path(char *cmd, t_env_list *env_list);
int		wait_for_commands(t_cmd *cmd_list, t_shell_data *data);
void	execute_single_command(t_cmd *cmd, t_shell_data *data);
void	execute_external_command(t_cmd *cmd, t_shell_data *data);
void	execute_command(t_cmd *cmd, char **env_array);
int	execute_command_for_heredoc(t_cmd *cmd, char **env_array);
char	*create_cmd_path(char *cmd, char **paths);
char	*get_path(char **env_array);
char	*get_cmd_path(char *cmd, char **env_array);

#endif