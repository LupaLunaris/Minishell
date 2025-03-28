/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/28 10:17:22 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable(char *str)
{
	if(str[0] != '$' && str[0] != '\"')
		return (0);
	if(str[0] == '\"' && str[1] == '$')
		return (2);
	return 1;
}
// char *get_env_value(t_env_list *list, char *key)
// {
//     t_env_list *current = list;

//     while (current)
//     {
//         if (ft_strcmp(current->key, key) == 0)
//             return (current->value);
//         current = current->next;
//     }
//     return (NULL);
// }

//char *args_news_values(char *args, )

void var_expend(t_env_list *list, t_cmd *cmds)
{
	int	i;
	char *value;
	char *env_value = NULL;
	t_cmd *cmd_temp;
	int	jump;

	i = 0;
	cmd_temp = cmds;
	while(cmd_temp)
	{
		i = 1;
		while (cmd_temp->args[i])
		{
			jump = is_variable(cmd_temp->args[i]);
			printf("%d\n",jump);

			if(jump)
			{
				//printf("args =  %s\n", cmd_temp->args[i]);

				value = ft_strtrim((cmd_temp->args[i] + jump), "\"");
				env_value = get_env_value(list, value);
				if(env_value)
					cmd_temp->args[i] = strdup(env_value);
				//printf("value =  %s\n", cmd_temp->args[i]);
				else
					cmd_temp->args[i] = strdup("");
			}
			i++;
		}
		cmd_temp = cmd_temp->next;
	}
}