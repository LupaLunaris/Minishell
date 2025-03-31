/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 22:04:20 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Met à jour une variable d'environnement ou l'ajoute si elle n'existe pas
 */
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

/**
 * Vérifie si une chaîne contient une variable à expandre
 */
int is_variable(char *str)
{
    if (!str || !str[0])
        return 0;
        
    // Si on est dans une chaîne avec simple quote, pas d'expansion
    if (str[0] == '\'')
        return 0;
        
    // Cherche le $ dans la chaîne
    char *dollar = strchr(str, '$');
    if (!dollar)
        return 0;
        
    // Retourne la position du  $  par rapport au début de la chaîne
    return (dollar - str + 1);
}

/**
 * Expande les variables d'environnement dans une chaîne
 */
char *expand_variables(char *str, t_env_list *list, t_shell_data *data)
{
    if (!str)
        return NULL;
        
    char *result = malloc(4096); // Buffer temporaire
    if (!result)
        return NULL;
        
    int j = 0;
    int i = 0;
    
    while (str[i])
    {
        // Si on trouve un  $ 
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
                //  $  suivi d'autre chose, on garde le  $ 
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

/**
 * Traite et expande les variables dans tous les arguments des commandes
 */
void var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
    t_cmd *cmd_temp = cmds;
    
    while (cmd_temp)
    {
        // Traiter aussi la commande elle-même
        if (cmd_temp->cmd && cmd_temp->cmd[0] == '$')
        {
            char *expanded_cmd = expand_variables(cmd_temp->cmd, list, data);
            free(cmd_temp->cmd);
            cmd_temp->cmd = expanded_cmd;
        }
        
        int i = 0;
        while (cmd_temp->args && cmd_temp->args[i])
        {
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