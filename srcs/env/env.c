/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Jpaulis <Jpaulis@student.s19.be>		   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/12 15:29:44 by Jpaulis		   #+#	#+#			 */
/*   Updated: 2025/03/17 12:30:56 by Jpaulis		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

/**
 * Ajoute une variable d'environnement à partir d'une chaîne "KEY=VALUE"
 * @param env_list Liste des variables d'environnement
 * @param var_str Chaîne au format "KEY=VALUE"
 * @return 0 en cas de succès, -1 sinon
 */
int	add_env_var_from_string(t_env_list **env_list, char *var_str)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		result;

	equal_sign = ft_strchr(var_str, '=');
	if (!equal_sign)
		return (-1);
	key = ft_substr(var_str, 0, equal_sign - var_str);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (-1);
	}
	result = add_env_var(env_list, key, value);
	free(key);
	free(value);
	return (result);
}

/**
 * Recherche une variable d'environnement par son nom
 * @param env_list Liste des variables d'environnement
 * @param key Nom de la variable à rechercher
 * @return Pointeur sur la valeur ou NULL si non trouvée
 */
char	*get_env_var(t_env_list *env_list, char *key)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
 * Affiche l'environnement (liste chaînée d'env_list)
 * @param env_list Le début de la liste chaînée d'environnement
 */
void	print_env_list(t_env_list *env_list)
{
	t_env_list	*current;

	current = env_list;
	while (current)
	{
		write(STDOUT_FILENO, current->key, strlen(current->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, current->value, strlen(current->value));
		write(STDOUT_FILENO, "\n", 1);
		current = current->next;
	}
}

int	handle_var(char *result, char *str, t_env_list *list, int i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		j;

	j = 0;
	start = i;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_substr(str, start, i - start);
	var_value = get_env_value(list, var_name);
	if (var_value)
	{
		while (var_value[j])
		{
			result[j] = var_value[j];
			j++;
		}
	}
	free(var_name);
	return (j);
}

t_indices	process_special_vars(char *str, char *result, t_shell_data *data,
	t_indices idx)
{
	t_indices	n_id;

	n_id = idx;
	if (str[n_id.i] == '?')
	{
		n_id.j = handle_q_mark(data, result, n_id.j, n_id.i);
		n_id.i++;
	}
	else if (str[n_id.i] == '$')
	{
		n_id.j = handle_dollars(result, n_id.j, n_id.i);
		n_id.i++;
	}
	else if (ft_isalpha(str[n_id.i]) || str[n_id.i] == '_')
	{
		n_id.j += handle_var(&result[n_id.j], str, data->env_list, n_id.i);
		while (str[n_id.i] && (ft_isalnum(str[n_id.i])
				|| str[n_id.i] == '_'))
			n_id.i++;
	}
	else
		result[n_id.j++] = '$';
	return (n_id);
}
