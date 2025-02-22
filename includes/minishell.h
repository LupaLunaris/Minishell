/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:46:16 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/21 14:02:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"


// Structure globale temporaire (attente de martinLAf)
typedef struct s_command
{
    char *cmd;               // Commande principale (ex: "ls", "grep", "echo")
    char **args;             // Liste des arguments (ex: ["ls", "-l", NULL])
    char *input_file;        // Fichier si redirection de stdin (ex: "input.txt" pour `< input.txt`)
    char *output_file;       // Fichier si redirection de stdout (ex: "output.txt" pour `> output.txt`)
    int append;              // Flag pour append : 1 = `>>`, 0 = `>`
    struct s_command *next;  // Pointeur vers la commande suivante (en cas de pipe)
	struct s_command *prev;
	pid_t		pid;
    int is_builtin;          // 1 si c'est une commande builtin, 0 sinon
} t_command;

typedef struct s_env_list
{
    char *key; //nom de la variable d'environnement (par exemple : PATH, HOME, USER)
    char *value; //valeur associée à cette clé
    struct s_env_list *next; //'élément suivant dans la liste chaînée
} t_env_list;

// minishell.c
int main(int argc, char **argv, char **envp);

#endif
