/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:46:16 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/17 15:53:23 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
#include <sys/types.h>
# include <signal.h>
# include <string.h>
# include "libft.h"

// Structure globale
typedef struct s_data {

} t_data;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

// minishell.c
int main(int argc, char **argv, char **envp);

#endif
