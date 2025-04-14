/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:46:16 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/08 15:55:26 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <string.h>
# include <ctype.h>
# include "libft.h"

# include "shell_data.h"
# include "command.h"
# include "env.h"
# include "execute.h"
# include "builtins.h"
# include "lexing.h"
# include "parser.h"
# include "signals.h"

struct							s_command;
struct							s_env_list;
struct							s_shell_data;
struct							s_redirection;
struct							s_token;
struct							s_lexer;

typedef struct s_command		t_cmd;
typedef struct s_env_list		t_env_list;
typedef struct s_shell_data		t_shell_data;
typedef struct s_redirection	t_redirection;
typedef struct s_token			t_token;
typedef struct s_lexer			t_lexer;

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef TRUE_FALSE_DEFINED
#  define TRUE_FALSE_DEFINED
#  define TRUE 1
#  define FALSE 0
# endif

int		error_handler(const char *cmd, const char *message,
			int should_exit, int error_code);
int		error_handler_c(t_cmd *cmd, char **env_array, const char *message,
			int should_exit);
int		error_message_env_init(t_shell_data *data);
int		error_message_and_exit(char *prefix, char *message);
int		is_valid_identifier(char *str);
char	*strip_quotes(char *str);
void	cleanup_and_exit(t_shell_data *data, t_cmd *cmds, int exit_code);
void	free_arr(char **arr);
void	*clean_cmd_list(t_cmd *head);
int		process_command(char *input, t_shell_data *data);
int		process_all_redirections(t_cmd *cmd_list, t_shell_data *data);
int		check_special_commands(char *input);
int		check_dollar_command(t_cmd *cmd_list);
void	main_shell_loop(t_shell_data *data, char **rl);
void	handle_input_loop(t_shell_data *data, char **rl);
void	handle_signals_exit_status(t_shell_data *data);
int		main(int argc, char **argv, char **envp);
void	free_env_array(char **env_array);

#endif
