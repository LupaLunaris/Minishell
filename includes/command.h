/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:35:04 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/15 11:34:26 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <sys/types.h>
# include "shell_data.h"

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redirection
{
	char					*file;
	t_redir_type			type;
	char					*heredoc_content;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	t_redirection		*redirections;
	struct s_command	*next;
	struct s_command	*prev;
	pid_t				pid;
	int					is_builtin;
	int					pipe_fd[2];
	int					infile;
	int					outfile;
}	t_cmd;

void	free_command(t_cmd *cmd);
char	*find_command_path(char *cmd, t_env_list *env_list);
int		wait_for_commands(t_cmd *cmd_list, t_shell_data *data);
void	execute_single_command(t_cmd *cmd, t_shell_data *data);
void	execute_external_command(t_cmd *cmd, t_shell_data *data);
void	execute_command(t_cmd *cmd, char **env_array);
int		execute_command_for_heredoc(t_cmd *cmd, char **env_array);
char	*create_cmd_path(char *cmd, char **paths);
char	*get_path(char **env_array);
char	*get_cmd_path(char *cmd, char **env_array);
t_cmd	*create_command(void);
#endif