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

t_cmd		*parse_input(char *input);
t_cmd		*parse_tokens(t_token *tokens);
t_cmd		*create_command(void);

void		*clean_cmd_list(t_cmd *cmd_list);
void		add_builtin(t_cmd *cmd_list);
void		free_arr(char **arr);
int			init_args(t_cmd *cmd, int arg_count);
int			count_args(t_token *token, t_token *end);
t_cmd		*ft_cmdlast(t_cmd *lst);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
int			add_token_redir(t_cmd *cmd, t_token **token);

#endif
