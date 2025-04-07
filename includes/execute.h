/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:56:35 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 20:55:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <stdbool.h>
# include "command.h"
# include "shell_data.h"

int		execute(t_cmd *cmd, t_env_list *env_list, t_shell_data *data);
int		check_redirections(t_cmd *cmd);
int		get_children(t_cmd *cmd);
int		create_children(t_cmd *cmd, t_env_list *env_list, t_shell_data *data);
int		process_heredoc(char *delimiter, t_cmd *command);
int		setup_output_redirection(const char *output_file, int append);
char	*get_heredoc_content(char *delimiter);
void	print_redirections(t_redirection *redir);
int		add_line_to_content(char **new_content, char *line);
bool	create_pipes(t_cmd *cmd_list);
int		setup_redirection(t_redirection *redirections);
void	restore_io(int stdin_fd, int stdout_fd);
void	init_pipeline(t_pipe_data *pd, t_shell_exec *se,
			t_env_list *env_list, t_cmd *cmd_list);
int		create_process(t_cmd *curr, t_pipe_data *pd, t_shell_exec *se);
int		wait_for_processes(t_cmd *cmd, int *last_status);
void	manage_pipes(t_pipe_data *pd, int is_child);
void	process_pipe_command(t_cmd *curr, t_shell_exec *se);
int		execute_pipeline(t_cmd *cmd, t_env_list *env_list, t_shell_data *data);
int		handle_dup_output(int fd_out, char *cleaned_file);
int		handle_input_redir(char *cleaned_file);
int		handle_output_redir(char *cleaned_file, int append);
int		handle_heredoc_redir(t_redirection *current, char *cleaned_file);
char	*strip_quotes(char *str);
char	*get_cmd_heredoc_content(t_cmd *cmd);
int		handle_status(int status);
int		has_heredoc(t_cmd *cmd);
char	*get_heredoc_delimiter(t_cmd *cmd);

#endif
