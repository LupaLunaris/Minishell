/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:36:21 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/14 16:36:45 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_list
{
	char *key; //nom de la variable d'environnement (par exemple : PATH, HOME, USER)
	char *value; //valeur associée à cette clé
	struct s_env_list *next; //'élément suivant dans la liste chaînée
} t_env_list;

// Fonctions de gestion de l'environnement
t_env_list      *init_env(char **envp);
t_env_list      *add_env_var(t_env_list *list, char *key, char *value);
void            remove_env_var(t_env_list **list, char *key);
char            *get_env_value(t_env_list *list, char *key);
void            free_env_list(t_env_list *list);
char            **env_list_to_array(t_env_list *list);
t_env_list      *find_env_var(t_env_list *list, char *key);
void            print_sorted_env(t_env_list *list);

#endif
