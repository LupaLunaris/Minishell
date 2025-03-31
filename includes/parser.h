#ifndef PARSER_H
# define PARSER_H

# include "command.h"  // Pour le type t_cmd

// Fonctions de parser
int     process_redirection(t_cmd *current, char **splited_args, int *i);
void    fill_cmd_args(t_cmd *cmd, char **splited_args, int *i);
t_cmd   *parser(char **splited_args);
void    free_arr(char **arr);  // Ajout de cette déclaration
void    *clean_cmd_list(t_cmd *cmd);  // Vérifiez que cette déclaration est déjà présente

// Fonctions utilitaires
int     is_redirect(char *token);
int     is_builtin(char *cmd);
t_cmd   *create_cmd_node(void);
void    add_cmd_node(t_cmd **head, t_cmd *new_node);
int     count_args_to_pipe(char **splited_args, int start);
void    add_builtin(t_cmd *cmd);

#endif
