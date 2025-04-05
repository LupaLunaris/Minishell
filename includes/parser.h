/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:08:00 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 14:08:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexing.h"
# include "command.h"

/* Analyse l'entrée utilisateur directement (lexing + parsing) */
t_cmd       *parse_input(char *input);

/* Analyse une liste de tokens et construit l'arbre de commandes */
t_cmd       *parse_tokens(t_token *tokens);

/* Crée une nouvelle commande vide */
t_cmd		*create_command(void);

/* Nettoie la liste de commandes (libère la mémoire) */
void        *clean_cmd_list(t_cmd *cmd_list);

/* Identifie les commandes builtin */
void        add_builtin(t_cmd *cmd_list);

/* Utilitaire pour libérer un tableau de chaînes */
void        free_arr(char **arr);


int			init_args(t_cmd *cmd, int arg_count);
/*
** Compte le nombre d'arguments pour une commande (jusqu'au pipe suivant)
** en excluant les redirections et leurs fichiers
*/

int			count_args(t_token *token, t_token *end);

t_cmd	*ft_cmdlast(t_cmd *lst);

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);

int		add_token_redir(t_cmd *cmd, t_token **token);


#endif
