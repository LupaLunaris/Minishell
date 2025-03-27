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
int main(int argc, char **argv, char **envp)
{
	char *rl;
	char **splited_args;
	t_cmd *cmds;
	int final_status = 0;

	if (argc != 1 || !argv)
		return 1;

	// Initialiser la structure t_shell_data
	t_shell_data *data = malloc(sizeof(t_shell_data));
	if (!data)
		return 1;

	// Initialisation des données du shell
	data->exit_status = 0;
	data->interactive = isatty(STDIN_FILENO);
	t_env_list *env_list = init_env(envp);
	data->env_list = env_list;

	// Boucle principale du shell
	while (1)
	{
		// Réinitialiser l'état des signaux pour chaque nouvelle commande
		g_signal_received = 0;

		// Configurer les signaux en mode interactif avant de demander une entrée utilisateur
		if (data->interactive)
			set_signals_interactive();

		// Lire l'entrée de l'utilisateur
		rl = readline("MiniShellDeLaMort> ");

		// Traitement explicite de Ctrl+D (EOF)
		if (rl == NULL)
		{
			if (data->interactive)
				write(STDOUT_FILENO, "exit\n", 5);
			final_status = data->exit_status;
			break;  // Sortie immédiate de la boucle
		}

		// Traiter la ligne saisie si elle n'est pas vide
		if (rl[0] != '\0')
		{
			add_history(rl);

			// Passer en mode non-interactif avant d'exécuter la commande
			if (data->interactive)
				set_signals_noninteractive();

			// Parsing et préparation des commandes
			splited_args = ft_split(rl, ' ');
			cmds = parser(splited_args);
			var_expend(env_list,cmds);
			free(rl);

			// Exécution des commandes
			if (cmds)
			{
				add_builtin(cmds);
				data->exit_status = execute(cmds, env_list, data);
				free_command(cmds);
			}

			// Vérifier si un signal a été reçu pendant l'exécution
			if (g_signal_received == SIGINT)
				data->exit_status = 130;  // 128 + SIGINT (2)
			else if (g_signal_received == SIGQUIT)
				data->exit_status = 131;  // 128 + SIGQUIT (3)
		}
		else
		{
			free(rl);
		}
	}

	// Libérer les ressources
	if (env_list)
		free_env_list(env_list);

	// Libérer la mémoire allouée pour data
	free(data);
	rl_clear_history();

	return (final_status);
}
