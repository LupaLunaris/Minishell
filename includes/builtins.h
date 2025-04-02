/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:08:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:19:25 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"
# include "env.h"
# include "shell_data.h"

typedef struct s_quote_data
{
	int		in_quotes;
	char	quote_type;
	int		i;
	int		j;
}	t_quote_data;

// Fonctions builtins
int		execute_builtin(t_cmd *cmd, t_shell_data *data);
int		builtin_echo(t_cmd *cmd);
int		builtin_cd(char **args, t_env_list **env_list);
int		builtin_pwd(void);
int		builtin_exit(t_cmd *cmd, t_shell_data *data);
int		builtin_export(t_cmd *cmd, t_env_list **env_list);
int		builtin_unset(char **args, t_env_list **env_list);
int		builtin_env(t_cmd *cmd, t_env_list **env_list);
int		is_valid_identifier(char *arg);
int		process_export_with_equals(char *arg, t_env_list **env_list);
void	print_export_list(t_env_list *env_list);
void	print_sorted_exp(t_env_list **sorted_env, int count);

#endif
