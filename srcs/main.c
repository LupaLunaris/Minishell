/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:45:57 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/25 11:17:11 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction auxiliaire pour libérer un tableau de chaînes
void free_array(char **arr)
{
    int i;
    
    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

t_command *parse_input(char *input, t_env_list *env_list)
{
    char **splited_args;
    t_command *result;
	(void)env_list;
    
    if (!input || !*input)
        return (NULL);
    // Diviser l'entrée en arguments
    splited_args = ft_split(input, ' '); // Ajuste selon ta logique de découpage
    if (!splited_args)
        return (NULL);
    
    // Prétraitement avec les variables d'environnement si nécessaire
    // preprocess_args(splited_args, env_list);

    // Appeler le parser existant
    result = parser(splited_args);
    // Libérer le tableau d'arguments
    free_array(splited_args); // Assure-toi d'avoir cette fonction
    
    return (result);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
    (void)argv;
	// Initialiser la structure t_shell_data
	t_shell_data *data = malloc(sizeof(t_shell_data));
	if (!data)
		return (1);
	data->exit_status = 0;
	data->interactive = isatty(STDIN_FILENO);
	t_env_list *env_list = init_env(envp);
	char *rl;
	while (1)
	{ 
		rl = readline("MiniShellDeLaMort> ");
		if (!rl)
			break;
		add_history(rl);
		t_command *cmds = parse_input(rl, env_list);
		free(rl);
		if (!cmds)
			continue;
		// Passer data à execute pour qu'il puisse enregistrer le statut de sortie
		data->exit_status = execute(cmds, env_list, data);
		free_command(cmds);
	}
	printf("exit\n");
	// Libérer la mémoire allouée pour data
	free_shell_data(data);
	return (0);
}
