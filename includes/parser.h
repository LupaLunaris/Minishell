#ifndef PARSER_H
# define PARSER_H



//cdm_parser
int		process_redirection(t_cmd *current, char **splited_args, int *i);
void	fill_cmd_args(t_cmd *cmd, char **splited_args, int *i);
t_cmd	*parser(char **splited_args);
//parser_utils
int		is_redirect(char *token);
int		is_builtin(char *cmd);
t_cmd	*create_cmd_node(void);
void	add_cmd_node(t_cmd **head, t_cmd *new_node);
int		count_args_to_pipe(char **splited_args, int start);
void	add_builtin(t_cmd *cmd);
void	free_arr(char **arr);
t_shell_data *init_shell_data(char **envp);
#endif

