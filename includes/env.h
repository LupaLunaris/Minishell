/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:36:21 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/06 10:35:35 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

t_env_list	*init_env(char **envp);
int			add_env_var(t_env_list **env_list, char *name, char *value);
void		remove_env_var(t_env_list **list, char *key);
char		*get_env_value(t_env_list *list, char *key);
void		free_env_list(t_env_list *list);
char		*ft_strjoin_env(char const *s1, char const *s2);
char		**env_list_to_array(t_env_list *list);
t_env_list	*find_env_var(t_env_list *list, char *key);
void		print_sorted_env(t_env_list *list);
void		print_env_list(t_env_list *env_list);
int			count_env_vars(t_env_list *env_list);
void		sort_env_list(t_env_list **env_array, int count);
char		*get_env_var(t_env_list *env_list, char *key);
void		add_env_var_without_value(t_env_list **env_list, char *key);
void		delete_env_var(t_env_list **env_list, char *key);
void		var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data);
char		*expand_variables(char *str, t_env_list *list, t_shell_data *data);
void		update_env_var(t_env_list **env_list, char *name, char *value);
int			add_env_var_from_string(t_env_list **env_list, char *var_str);
char		*ft_strjoin_env(char const *s1, char const *s2);

#endif
