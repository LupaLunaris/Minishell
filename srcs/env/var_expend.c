/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/02 15:26:40 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction pour développer les variables d'environnement*/
char *expand_variables(char *str, t_env_list *list, t_shell_data *data)
{
	char *result;
	int i;
	int j;
	int in_squote;
	int in_dquote;

	in_squote = 0;
	in_dquote = 0;
	if (!str)
		return (NULL);
	int has_quotes = 0;
	for (i = 0; str[i]; i++) {
		if (str[i] == '\'' || str[i] == '"') {
			has_quotes = 1;
			break;
		}
	}
	if (!has_quotes) {
		result = malloc(4096);
		if (!result)
			return (NULL);
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] == '$' && str[i+1])
			{
				i++;

				// Cas spécial $?
				if (str[i] == '?')
				{
					char *exit_str = ft_itoa(data->exit_status);
					int k = 0;
					while (exit_str[k])
						result[j++] = exit_str[k++];
					free(exit_str);
					i++;
				}
				// Cas $$ pour PID
				else if (str[i] == '$')
				{
					char *pid_str = ft_itoa(getpid());
					int k = 0;
					while (pid_str[k])
						result[j++] = pid_str[k++];
					free(pid_str);
					i++;
				}
				// Expansions des variables d'environnement
				else if (ft_isalpha(str[i]) || str[i] == '_')
				{
					int start = i;
					while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
						i++;

					char *var_name = ft_substr(str, start, i - start);
					char *var_value = get_env_value(list, var_name);

					if (var_value)
					{
						int k = 0;
						while (var_value[k])
							result[j++] = var_value[k++];
					}

					free(var_name);
				}
				else
				{
					// $ suivi d'autre chose, on garde le $
					result[j++] = '$';
				}
			}
			else
			{
				result[j++] = str[i++];
			}
		}

		result[j] = '\0';
		char *final_result = ft_strdup(result);
		free(result);

		return (final_result);
	}

	// Allouer un buffer pour le résultat (assez grand)
	result = malloc(4096);
	if (!result)
		return (NULL);

	i = 0;
	j = 0;

	while (str[i])
	{
		// Gestion des guillemets
		if (str[i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
		}
		else if (str[i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
		}
		// Expansion des variables
		else if (str[i] == '$' && str[i+1] && !in_squote)
		{
			i++; // Passer le $

			// Cas spécial $?
			if (str[i] == '?')
			{
				char *exit_str = ft_itoa(data->exit_status);
				int k = 0;
				while (exit_str[k])
					result[j++] = exit_str[k++];
				free(exit_str);
				i++;
			}
			// Cas $$ pour PID
			else if (str[i] == '$')
			{
				char *pid_str = ft_itoa(getpid());
				int k = 0;
				while (pid_str[k])
					result[j++] = pid_str[k++];
				free(pid_str);
				i++;
			}
			// Expansions des variables d'environnement
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				int start = i;
				while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
					i++;

				char *var_name = ft_substr(str, start, i - start);
				char *var_value = get_env_value(list, var_name);

				if (var_value)
				{
					int k = 0;
					while (var_value[k])
						result[j++] = var_value[k++];
				}

				free(var_name);
			}
			else
			{
				// $ suivi d'autre chose, on garde le $
				result[j++] = '$';
			}
		}
		else
		{
			// Caractère normal
			result[j++] = str[i++];
		}
	}

	result[j] = '\0';
	char *final_result = ft_strdup(result);
	free(result);

	return (final_result);
}

// Fonction principale pour développer les variables
void var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
	t_cmd *cmd_temp = cmds;

	while (cmd_temp)
	{
		// Traiter les arguments
		if (cmd_temp->args)
		{
			int i = 0;
			// Si le premier argument est une variable d'environnement vide
			if (cmd_temp->args[0] && cmd_temp->args[0][0] == '$' && 
				(!get_env_var(list, cmd_temp->args[0] + 1) || 
				 (get_env_var(list, cmd_temp->args[0] + 1) && ft_strlen(get_env_var(list, cmd_temp->args[0] + 1)) == 0)))
			{
				// S'il y a d'autres arguments, déplacer tous les arguments
				if (cmd_temp->args[1])
				{
					free(cmd_temp->args[0]);
					int j = 0;
					while (cmd_temp->args[j+1])
					{
						cmd_temp->args[j] = cmd_temp->args[j+1];
						j++;
					}
					cmd_temp->args[j] = NULL;
					
					// Mettre à jour cmd
					free(cmd_temp->cmd);
					cmd_temp->cmd = ft_strdup(cmd_temp->args[0]);
					
					// Supprimer la ligne is_builtin qui cause l'erreur
					// cmd_temp->is_builtin = is_builtin(cmd_temp->cmd);
				}
				else
				{
					// Sinon, s'il n'y a pas d'arguments suivants, c'est une erreur
					data->exit_status = 127;
					// Garder la commande vide pour afficher l'erreur
				}
			}
			else {
				// Expansion normale
				while (cmd_temp->args[i])
				{
					// Expander les variables
					char *expanded = expand_variables(cmd_temp->args[i], list, data);
					if (expanded)
					{
						free(cmd_temp->args[i]);

						// Supprimer les guillemets
						char *no_quotes = remove_quotes(expanded);
						free(expanded);

						cmd_temp->args[i] = no_quotes;
					}
					i++;
				}
			}
		}

		// Mettre à jour cmd si nécessaire (premier argument)
		if (cmd_temp->args && cmd_temp->args[0])
		{
			free(cmd_temp->cmd);
			cmd_temp->cmd = ft_strdup(cmd_temp->args[0]);
		}

		cmd_temp = cmd_temp->next;
	}
}
