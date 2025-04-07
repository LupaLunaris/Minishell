/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:36:21 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:34:47 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_list
{
	char *key; //nom de la variable d'environnement (par exemple : PATH, HOME, USER)
	char *value; //valeur associée à cette clé
	struct s_env_list *next; //'élément suivant dans la liste chaînée
} t_env_list;

typedef struct	s_indices
{
	int	i;
	int	j;
 }	t_indices;

 typedef struct s_quote
{
	int in_dquote;
	int	in_squote;
}	t_quote;


// Fonctions de gestion de l'environnement
t_env_list      *init_env(char **envp);
int				add_env_var(t_env_list **env_list, char *name, char *value);
void            remove_env_var(t_env_list **list, char *key);
char            *get_env_value(t_env_list *list, char *key);
void            free_env_list(t_env_list *list);
char			*ft_strjoin_env(char const *s1, char const *s2);
char            **env_list_to_array(t_env_list *list);
t_env_list      *find_env_var(t_env_list *list, char *key);
void            print_sorted_env(t_env_list *list);
int				count_env_vars(t_env_list *env_list);
void			sort_env_list(t_env_list **env_array, int count);
void			add_env_var_without_value(t_env_list **env_list, char *key);
void			delete_env_var(t_env_list **env_list, char *key);
void			update_env_var(t_env_list **env_list, char *name, char *value);
void			expand_cmd_args(t_cmd *cmd, t_shell_data *data);
void			update_cmd_from_args(t_cmd *cmd);
char			*init_expand_result(char *str, t_shell_data *data);
char			*expand_variables(char *str, t_shell_data *data);
void			ft_env_back(t_env_list **lst, t_env_list *new);
char			*ft_strjoin_env(char const *s1, char const *s2);
t_quote			*init_quote_state(void);

/* var expend */

char		*expand_no_quote(char *str, char *result, t_shell_data *data);
t_indices	process_quoted_vars(char *str, char *result, t_shell_data *data,
	t_indices idx);
char		*expand_quote(char *str, char *result, t_shell_data *data);
int			handle_none_var(t_env_list *list, t_cmd *cmd, t_shell_data *data);
void		var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data);

/* env */
int				handle_var(char *result, char *str, t_env_list *list, int i);
t_indices		process_special_vars(char *str, char *result, t_shell_data *data,
	t_indices idx);
void			print_env_list(t_env_list *env_list);
char			*get_env_var(t_env_list *env_list, char *key);
int				add_env_var_from_string(t_env_list **env_list, char *var_str);

/* var_verif */
int				has_quotes(char *str);
int				handle_q_mark(t_shell_data *data, char *result, int j, int i);
int				handle_dollars(char *result, int j, int i);
t_indices		is_in_squote(t_quote *state, char *str, t_indices idx);
int				is_none_var(t_env_list *list, t_cmd *cmd);

#endif
