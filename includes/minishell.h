/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:46:16 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/17 16:06:49 by Jpaulis          ###   ########.fr       */
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
    char *key; //nom de la variable d'environnement (par exemple : PATH, HOME, USER)
    char *value; //valeur associée à cette clé
    struct s_env *next; //'élément suivant dans la liste chaînée
} t_env;

// minishell.c
int main(int argc, char **argv, char **envp);

#endif
