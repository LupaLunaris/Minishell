/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:35:06 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_env_var(t_env_list **env_list, char *name, char *value)
{
    t_env_list *current = *env_list;
    
    // Chercher si la variable existe déjà
    while (current)
    {
        if (ft_strcmp(current->key, name) == 0)
        {
            // Mettre à jour la valeur
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
    
    // Si la variable n'existe pas, l'ajouter
    add_env_var(env_list, name, value);
}

int add_env_var(t_env_list **env_list, char *name, char *value)
{
    t_env_list *new_node;
    
    // Allouer de la mémoire pour le nouveau nœud
    new_node = (t_env_list *)malloc(sizeof(t_env_list));
    if (!new_node)
        return (0); // Échec
    
    // Initialiser les champs du nouveau nœud
    new_node->key = ft_strdup(name);
    if (!new_node->key)
    {
        free(new_node);
        return (0);
    }
    
    new_node->value = ft_strdup(value);
    if (!new_node->value)
    {
        free(new_node->key);
        free(new_node);
        return (0);
    }
    
    new_node->next = NULL;
    
    // Cas particulier : liste vide
    if (*env_list == NULL)
    {
        *env_list = new_node;
        return (1); // Succès
    }
    
    // Sinon, ajouter à la fin de la liste
    t_env_list *current = *env_list;
    while (current->next)
        current = current->next;
    
    current->next = new_node;
    return (1); // Succès
}

int is_variable(char *str)
{
    // Vérifie si on a un  $  non échappé
    if (!str || !str[0])
        return 0;
        
    // Si on est dans une chaîne avec simple quote, pas d'expansion
    if (str[0] == '\'')
        return 0;
        
    // Cherche le  $  dans la chaîne
    char *dollar = strchr(str, '$');
    if (!dollar)
        return 0;
        
    // Retourne la position du  $  par rapport au début de la chaîne
    return (dollar - str + 1);
}

// Dans les paramètres de expand_variables, n'incluez pas in_single_quotes
char *expand_variables(char *str, t_env_list *list, t_shell_data *data)
{
    // Si la chaîne est vide, retourner une copie vide
    if (!str)
        return NULL;
        
    char *result = malloc(4096); // Buffer temporaire
    int j = 0;
    int i = 0;
    
    if (!result)
        return NULL;
    while (str[i])
    {
        // Si on trouve un $
        if (str[i] == '$' && str[i+1])
        {
            i++; // Passer le $
            
            // Cas spécial $?
            if (str[i] == '?')
            {
                char *exit_str = ft_itoa(data->exit_status);
                strcpy(result + j, exit_str);
                j += strlen(exit_str);
                free(exit_str);
                i++;
            }
            // Cas $$ pour PID
            else if (str[i] == '$')
            {
                char *pid_str = ft_itoa(getpid());
                strcpy(result + j, pid_str);
                j += strlen(pid_str);
                free(pid_str);
                i++;
            }
            // Expansions des variables d'environnement
            else if (isalpha(str[i]) || str[i] == '_')
            {
                int start = i;
                while (str[i] && (isalnum(str[i]) || str[i] == '_'))
                    i++;
                
                char *var_name = ft_substr(str, start, i - start);
                char *var_value = get_env_value(list, var_name);
                
                if (var_value)
                {
                    strcpy(result + j, var_value);
                    j += strlen(var_value);
                }
                
                free(var_name);
            }
            else
            {
                //   $   suivi d'autre chose, on garde le   $  
                result[j++] = '$';
            }
        }
        else
        {
            result[j++] = str[i++];
        }
    }
    
    result[j] = '\0';
    char *final_result = ft_strdup(result);
    free(result);
    
    return final_result;
}

void var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
    t_cmd *cmd_temp = cmds;
    
    while (cmd_temp)
    {
        int i = 0;
        while (cmd_temp->args[i])
        {
            // Traiter d'abord les guillemets
            char *arg = cmd_temp->args[i];
            char *processed_arg = NULL;
            
            // Si c'est une chaîne entre guillemets simples, on la prend telle quelle
            if (arg[0] == '\'' && arg[strlen(arg) - 1] == '\'')
            {
                // Pour les guillemets simples, PAS d'expansion
                processed_arg = ft_strtrim(arg, "'");
            }
            // Si c'est une chaîne entre guillemets doubles, on expand les variables
            else if (arg[0] == '"' && arg[strlen(arg) - 1] == '"')
            {
                // Retirer les guillemets
                char *without_quotes = ft_strtrim(arg, "\"");
                
                // Expandre les variables dans la chaîne
                processed_arg = expand_variables(without_quotes, list, data);
                free(without_quotes);
            }
            // Sinon c'est un mot simple, on expande aussi les variables
            else
            {
                processed_arg = expand_variables(arg, list, data);
            }
            
            // Remplacer l'argument original par l'argument traité
            free(cmd_temp->args[i]);
            cmd_temp->args[i] = processed_arg;
            
            i++;
        }
        cmd_temp = cmd_temp->next;
    }
}
