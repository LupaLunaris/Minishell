#include "minishell.h"
#include "../includes/minishell.h"

# include "signals.h"

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		return 1;
	}
	if (!argv)
	{
		return 1;
	}
	// Initialiser la structure t_shell_data
	t_shell_data *data = malloc(sizeof(t_shell_data));
	char **splited_args;

	if (!data)
		return (1);
	printf("data ok \n");
	data->exit_status = 0;
	data->interactive = isatty(STDIN_FILENO);
	t_env_list *env_list = init_env(envp);
	char *rl;
	while (1)
	{
		rl = readline("MiniShellDeLaMort> ");
		if (!rl)
		{
			printf("Exiting shell...\n");
			break;
		}
		add_history(rl);
		//t_command *cmds = parse_input(rl, env_list);
		splited_args = ft_split(rl, ' ');
		t_cmd *cmds = parser(splited_args);
		free(rl);
		if (!cmds)
			continue;
		add_builtin(cmds);
		// Passer data à execute pour qu'il puisse enregistrer le statut de sortie
		data->exit_status = execute(cmds, env_list, data);
		free_command(cmds);
	}
	printf("exit\n");
	// Libérer la mémoire allouée pour data
	//free_shell_data(data);
	rl_clear_history();
	return (data->exit_status);
}
