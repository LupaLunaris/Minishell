/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:11:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/15 14:19:13 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit(const char *message, int exit_code)
{
    // Libère les ressources ici

    // Appelle l'error_handler pour afficher un message d'erreur, puis quitte
    error_handler("commade", message, 0, exit_code);
    exit(exit_code);
}

// void free_shell_data(t_shell_data *data)
// {
//     if (!data)
//         return;
//     if (data->history)
//     {
//         int i = 0;
//         while (data->history[i])
//         {
//             free(data->history[i]);
//             i++;
//         }
//         free(data->history);
//     }
//     free(data);
// }