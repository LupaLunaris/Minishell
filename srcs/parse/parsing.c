#include "../minishell.h"

t_command *parse_input(char *input, t_env_list *env_list)
{
	t_command *cmd = malloc(sizeof(t_command));
	if (!cmd)
		return NULL;
	// Exemple basique sans parsing complexe (remplacer par un vrai tokenizer).
	char **splited_args = ft_split(input, ' ');
	cmd->cmd = ft_strdup(splited_args[0]);
	cmd->args = splited_args;
	cmd->input_file = NULL;  // À compléter pour < redirections
	cmd->output_file = NULL; // À compléter pour > redirections
	cmd->append = 0;         // Gérer >> redirection append
	cmd->next = NULL;
	return cmd;
}
