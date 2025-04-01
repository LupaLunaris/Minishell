/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:17:19 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 21:38:43 by Jpaulis          ###   ########.fr       */
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

// Fonction pour supprimer les guillemets d'une chaîne
char *remove_quotes(char *str)
{
    int i, j;
    int in_squote = 0;
    int in_dquote = 0;
    char *result;

    if (!str)
        return (NULL);

    result = malloc(strlen(str) + 1);
    if (!result)
        return (NULL);

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (str[i] == '"' && !in_squote)
            in_dquote = !in_dquote;
        else
            result[j++] = str[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

// Fonction pour développer les variables d'environnement
char *expand_variables(char *str, t_env_list *list, t_shell_data *data)
{
    char *result;
    int i, j;
    int in_squote = 0;
    int in_dquote = 0;

    // Si la chaîne est vide ou NULL, retourner NULL ou une chaîne vide
    if (!str)
        return (NULL);

    // Vérifier si la chaîne contient au moins un guillemet
    int has_quotes = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] == '\'' || str[i] == '"') {
            has_quotes = 1;
            break;
        }
    }

    // Si pas de guillemets, pas besoin d'expansion spéciale
    if (!has_quotes) {
        // Allouer un buffer pour le résultat (assez grand)
        result = malloc(4096);
        if (!result)
            return (NULL);

        i = 0;
        j = 0;

        while (str[i])
        {
            // Si on trouve un $ et pas dans des guillemets simples
            if (str[i] == '$' && str[i+1])
            {
                i++; // Passer le $

                // Cas spécial $?
                if (str[i] == '?')
                {
                    char *exit_str = ft_itoa(data->exit_status);
                    int k = 0;
                    while (exit_str[k])
                        result[j++] = exit_str[k++];
                    free(exit_str);
                    i++;
                }
                // Cas $$ pour PID
                else if (str[i] == '$')
                {
                    char *pid_str = ft_itoa(getpid());
                    int k = 0;
                    while (pid_str[k])
                        result[j++] = pid_str[k++];
                    free(pid_str);
                    i++;
                }
                // Expansions des variables d'environnement
                else if (ft_isalpha(str[i]) || str[i] == '_')
                {
                    int start = i;
                    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                        i++;

                    char *var_name = ft_substr(str, start, i - start);
                    char *var_value = get_env_value(list, var_name);

                    if (var_value)
                    {
                        int k = 0;
                        while (var_value[k])
                            result[j++] = var_value[k++];
                    }

                    free(var_name);
                }
                else
                {
                    // $ suivi d'autre chose, on garde le $
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

        return (final_result);
    }

    // Allouer un buffer pour le résultat (assez grand)
    result = malloc(4096);
    if (!result)
        return (NULL);

    i = 0;
    j = 0;

    while (str[i])
    {
        // Gestion des guillemets
        if (str[i] == '\'' && !in_dquote)
        {
            in_squote = !in_squote;
            i++;
        }
        else if (str[i] == '"' && !in_squote)
        {
            in_dquote = !in_dquote;
            i++;
        }
        // Expansion des variables
        else if (str[i] == '$' && str[i+1] && !in_squote)
        {
            i++; // Passer le $

            // Cas spécial $?
            if (str[i] == '?')
            {
                char *exit_str = ft_itoa(data->exit_status);
                int k = 0;
                while (exit_str[k])
                    result[j++] = exit_str[k++];
                free(exit_str);
                i++;
            }
            // Cas $$ pour PID
            else if (str[i] == '$')
            {
                char *pid_str = ft_itoa(getpid());
                int k = 0;
                while (pid_str[k])
                    result[j++] = pid_str[k++];
                free(pid_str);
                i++;
            }
            // Expansions des variables d'environnement
            else if (ft_isalpha(str[i]) || str[i] == '_')
            {
                int start = i;
                while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                    i++;

                char *var_name = ft_substr(str, start, i - start);
                char *var_value = get_env_value(list, var_name);

                if (var_value)
                {
                    int k = 0;
                    while (var_value[k])
                        result[j++] = var_value[k++];
                }

                free(var_name);
            }
            else
            {
                // $ suivi d'autre chose, on garde le $
                result[j++] = '$';
            }
        }
        else
        {
            // Caractère normal
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';
    char *final_result = ft_strdup(result);
    free(result);

    return (final_result);
}

// Fonction principale pour développer les variables
void var_expend(t_env_list *list, t_cmd *cmds, t_shell_data *data)
{
    t_cmd *cmd_temp = cmds;

    while (cmd_temp)
    {
        // Traiter les arguments
        if (cmd_temp->args)
        {
            int i = 0;
            while (cmd_temp->args[i])
            {
                // Expander les variables
                char *expanded = expand_variables(cmd_temp->args[i], list, data);
                if (expanded)
                {
                    free(cmd_temp->args[i]);

                    // Supprimer les guillemets
                    char *no_quotes = remove_quotes(expanded);
                    free(expanded);

                    cmd_temp->args[i] = no_quotes;
                }
                i++;
            }
        }

        // Mettre à jour cmd si nécessaire (premier argument)
        if (cmd_temp->args && cmd_temp->args[0])
        {
            free(cmd_temp->cmd);
            cmd_temp->cmd = ft_strdup(cmd_temp->args[0]);
        }

        cmd_temp = cmd_temp->next;
    }
}