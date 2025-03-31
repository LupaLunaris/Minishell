/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 18:46:41 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable(char *str)
{
	if(str[0] != '$' || str[0] == '\'')
	{
		printf("0 , str[0] = %c\n",str[0]);
		return (0);
	}
	// if((str[0] == '\"' && str[1] == '$'))
	// {
	// 	printf("2 , str[0] = %c\n",str[0]);
	// 	return (2);
	// }
	// else if ((str[1] != '$' ||  str[1] == '?'))
	// 	return (0);
	return 1;
}

int array_len(char **array)
{
	int	i;

	i = 0;
	while(array[i])
		i++;
	return(i);
}
void	free_arr(char **arr)
{
	int  i;

	i = 0;
	if (!arr)
		return;
	while(arr[i])
	{
		free(arr[i++]);
	}
	free(arr);
}
char **new_args(char **args, int indice)
{
    int i;
    int size_args;
    char **new_args;

    if (!args)
        return (NULL);
    size_args = array_len(args);
    if (indice >= size_args) // Vérification pour éviter un accès hors limite
        return (args);
    new_args = malloc(sizeof(char *) * (size_args + 2));
    if (!new_args)
        return (NULL);
    i = 0;
    while (i < indice)
    {
        new_args[i] = ft_strdup(args[i]);
        i++;
    }
    while (args[i])
    {
        new_args[i] = ft_strdup(args[i]);
        i++;
    }
    new_args[i] = NULL;
    i = 0;
	free_arr(args);
    return (new_args);
}


void var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
    int i;
    char *value;
    char *env_value = NULL;
    t_cmd *cmd_temp;
    int jump;
	char *args;
	char *args2;
    cmd_temp = cmds;
    while (cmd_temp)
    {
        i = 1;
        while (cmd_temp->args[i])
        {
            jump = is_variable(cmd_temp->args[i]);
            if (jump)
            {
                //printf("jumped by %s \n",cmd_temp->args[i] );
				value = ft_strtrim((cmd_temp->args[i] + jump), "\"");
                env_value = get_env_value(list, value);

                if (env_value)
                {
                    free(cmd_temp->args[i]); // Libérer avant remplacement
                    cmd_temp->args[i] = strdup(env_value);
                }
                else if (value[0] == '?')
                {
                    char *exit_status_str = ft_itoa(data->exit_status);
                    cmd_temp->args = new_args(cmd_temp->args, i + 1); // Ne pas libérer avant d'allouer
                    cmd_temp->args[i] = exit_status_str;
					{
						args =  strdup(value + 1);
						args2 = strdup(cmd_temp->args[i]);
						cmd_temp->args[i] = ft_strjoin(args2, args);

					}
                }
				else if (value[0] == '$')
                {
                    char *pid_str = ft_itoa(getpid());
                    cmd_temp->args = new_args(cmd_temp->args, i); // Ne pas libérer avant d'allouer
                    cmd_temp->args[i] = pid_str;
					if(value[1])
					{
						args =  strdup(value + 1);
						args2 = strdup(cmd_temp->args[i]);
						cmd_temp->args[i] = ft_strjoin(args2, args);

					}
                }

                else
                {
                    free(cmd_temp->args[i]);
                    cmd_temp->args[i] = strdup("");
                }

                free(value);
            }
			else if (cmd_temp->args[i][0] == '\'')
			{

					args =  strdup(cmd_temp->args[i]);
					cmd_temp->args[i] = ft_strtrim(args,"'");
			}

            i++;
        }
        cmd_temp = cmd_temp->next;
    }
}

// int	is_variable(char *str)
// {
// 	if(str[0] != '$' && str[0] != '\"')
// 		return (0);
// 	if(str[0] == '\"' && str[1] == '$')
// 		return (2);
// 	return 1;
// }
// // char *get_env_value(t_env_list *list, char *key)
// // {
// //     t_env_list *current = list;

// //     while (current)
// //     {
// //         if (ft_strcmp(current->key, key) == 0)
// //             return (current->value);
// //         current = current->next;
// //     }
// //     return (NULL);
// // }

// //char *args_news_values(char *args, )

// void var_expend(t_env_list *list, t_cmd *cmds)
// {
// 	int	i;
// 	char *value;
// 	char *env_value = NULL;
// 	t_cmd *cmd_temp;
// 	int	jump;

// 	i = 0;
// 	cmd_temp = cmds;
// 	while(cmd_temp)
// 	{
// 		i = 1;
// 		while (cmd_temp->args[i])
// 		{
// 			jump = is_variable(cmd_temp->args[i]);
// 			//printf("%d\n",jump);

// 			if(jump)
// 			{
// 				//printf("args =  %s\n", cmd_temp->args[i]);

// 				value = ft_strtrim((cmd_temp->args[i] + jump), "\"");
// 				env_value = get_env_value(list, value);
// 				if(env_value)
// 					cmd_temp->args[i] = strdup(env_value);
// 				//printf("value =  %s\n", cmd_temp->args[i]);
// 				else
// 					cmd_temp->args[i] = strdup("");
// 			}
// 			i++;
// 		}
// 		cmd_temp = cmd_temp->next;
// 	}
// }