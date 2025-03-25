#ifndef PARSER_H
# define PARSER_H

# include "command.h"
# include "env.h"
# include "shell_data.h"

void ft_lst_env_back(t_env_list **lst, t_env_list *new);
t_env_list *init_env(char **envp);
char	**env_list_to_array(t_env_list *env_list);



char	*ft_strjoin_env(char const *s1, char const *s2);
//char	**ft_split(char const *s, char c);
t_env_list	*ft_env_last(t_env_list *lst);

//cdm_parser

int process_redirection(t_command *current, char **splited_args, int *i);


//parser_utils
t_command	*create_cmd_node(void);
void	add_cmd_node(t_command **head, t_command *new_node);
int		is_redirect(char *token);
int		count_args_to_pipe(char **splited_args, int start);
t_command	*parser(char **splited_args);
void	add_builtin(t_command *cdm);

//clean_utils

void	*clean_cmd_list(t_command *head);
void	free_env(t_env_list *env_list);
void	free_arr(char **arr);

//lexing
char	*lexing(char *prompt);

//error_lexing
int	error_lexing(char *prompt);

#endif