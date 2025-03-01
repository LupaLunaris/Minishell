/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/01 16:42:02 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/**
 * Supprime une variable d'environnement de la liste
 * @param env_list Pointeur vers le début de la liste chaînée d'environnement
 * @param var_name Nom de la variable à supprimer
 */
void unset_env_var(t_env_list **env_list, char *var_name)
{
	t_env_list *current;  // Pointeur pour parcourir la liste
	t_env_list *prev;     // Pointeur pour garder trace du nœud précédent

	if (!env_list || !*env_list || !var_name)  // Vérification des arguments pour éviter les segfaults
		return;
	current = *env_list;  // Commencer au début de la liste
	prev = NULL;          // Pas de nœud précédent pour le premier élément
	if (current && ft_strcmp(current->key, var_name) == 0)  // Cas spécial: si le premier élément correspond à la variable à supprimer
	{
		*env_list = current->next;  // Le deuxième élément devient le premier
		free(current->key);         // Libération de la mémoire allouée pour la clé
		free(current->value);       // Libération de la mémoire allouée pour la valeur
		free(current);              // Libération de la structure elle-même
		return;                     // Sortie de la fonction après suppression
	}
	while (current)  // Pour tous les autres éléments de la liste
	{
		if (ft_strcmp(current->key, var_name) == 0)  // Si le nom correspond à celui recherché
		{
			prev->next = current->next;  // Relier le nœud précédent au nœud suivant
			free(current->key);          // Libérer la mémoire de la clé
			free(current->value);        // Libérer la mémoire de la valeur
			free(current);               // Libérer la structure
			return;                      // Sortir après suppression
		}
		prev = current;                  // Mettre à jour le pointeur précédent
		current = current->next;         // Passer au nœud suivant
	}  	// Si on arrive ici, la variable n'a pas été trouvée dans la liste
}

/**
 * Ajoute ou modifie une variable d'environnement dans la liste
 * @param env_list Pointeur vers le début de la liste chaînée d'environnement
 * @param var_assignment Chaîne au format "KEY=VALUE"
 */
void add_env_var(t_env_list **env_list, char *var_assignment)
{
	char *key;            // Stockera la clé de la variable
	char *value;          // Stockera la valeur de la variable
	char *equals_sign;    // Pointeur vers le signe égal dans var_assignment
	t_env_list *current;  // Pour parcourir la liste d'environnement
	
	// Trouver la position du signe égal
	equals_sign = ft_strchr(var_assignment, '=');
	if (!equals_sign)     // Si pas de signe égal, format invalide
		return;
	// Extraire la clé (partie avant '=') et la valeur (partie après '=')
	key = ft_substr(var_assignment, 0, equals_sign - var_assignment);
	value = ft_strdup(equals_sign + 1);
	// Vérifier si l'allocation a réussi
	if (!key || !value)
	{
		free(key);        // Libérer key si alloué
		free(value);      // Libérer value si alloué
		return;           // Sortir en cas d'échec
	}
	// Vérifier si la variable existe déjà dans la liste d'environnement
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)  // Si la clé existe déjà
		{
			// Mettre à jour la valeur existante
			free(current->value);              // Libérer l'ancienne valeur
			current->value = value;            // Assigner la nouvelle
			free(key);                         // Libérer la clé dupliquée car on garde celle existante
			return;                            // Sortir après mise à jour
		}
		current = current->next;               // Passer au nœud suivant
	}
	// Si la variable n'existe pas, créer un nouveau nœud
	t_env_list *new_node = malloc(sizeof(t_env_list));  // Allouer un nouveau nœud
	if (!new_node)                                      // Vérifier si l'allocation a réussi
	{
		free(key);                                      // Libérer en cas d'échec
		free(value);
		return;
	}
	// Initialiser le nouveau nœud avec les valeurs extraites
	new_node->key = key;
	new_node->value = value;
	new_node->next = *env_list;                         // Insérer en tête de liste
	*env_list = new_node;                               // Mettre à jour la tête de liste
}

/**
 * Implémente la commande builtin 'env' qui affiche ou modifie l'environnement
 * @param args Tableau des arguments de la commande
 * @param env_list Pointeur vers le début de la liste chaînée d'environnement
 * @return Exit status de la commande
 */
int builtin_env(char **args, t_env_list **env_list)
{
	int i = 1;  // Commence à l'indice 1 car args[0] est le nom de la commande ('env')
	
	// Traiter tous les arguments de la commande
	while (args[i])
	{
		// Option "-u" : supprimer une variable
		if (ft_strcmp(args[i], "-u") == 0)
		{
			i++;  // Avancer au nom de la variable à supprimer
			if (args[i])  // Si un argument est fourni après "-u"
			{
				unset_env_var(env_list, args[i]);  // Supprimer la variable
				i++;  // Avancer à l'argument suivant
			}
			else
				// Erreur si pas d'argument après "-u"
				return (error_handler("env", "option requires an argument: -u", 0, EXIT_FAILURE));
		}
		// Format "NOM=VALEUR" : ajouter/modifier une variable
		else if (ft_strchr(args[i], '='))
		{
			add_env_var(env_list, args[i]);  // Ajouter ou mettre à jour la variable
			i++;  // Passer à l'argument suivant
		}
		// Argument non reconnu (ni option ni variable)
		else
			// Afficher un message d'erreur et quitter
			return (error_handler("env", "illegal option or argument", 0, EXIT_FAILURE));
	}
	// Si tous les arguments ont été traités ou s'il n'y en avait pas,
	// afficher l'environnement actuel
	print_env_list(*env_list);  // Supposant que cette fonction existe déjà
	// Succès de la commande
	return (EXIT_SUCCESS);
}

/**
 * Affiche l'environnement (liste chaînée d'env_list)
 * @param env_list Le début de la liste chaînée d'environnement
 */
void print_env_list(t_env_list *env_list)
{
    t_env_list *current = env_list;
    
    while (current)
    {
        write(STDOUT_FILENO, current->key, strlen(current->key));
        write(STDOUT_FILENO, "=", 1);
        write(STDOUT_FILENO, current->value, strlen(current->value));
        write(STDOUT_FILENO, "\n", 1);
        current = current->next;
    }
}

// PATH : Liste des répertoires où le shell cherche les exécutables
// HOME : Chemin vers le répertoire home de l'utilisateur
// USER : Nom de l'utilisateur connecté
// PWD : Répertoire de travail actuel
// SHELL : Chemin vers le shell utilisé
// TERM : Type de terminal utilisé