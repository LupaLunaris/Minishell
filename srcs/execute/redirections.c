/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 19:34:08 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int setup_heredoc_redirection(const char *heredoc_content)
// {
//     int pipe_fd[2];
    
//     if (pipe(pipe_fd) == -1)
//         return error_handler("setup_redirection", "pipe creation failed", 0, EXIT_FAILURE);
        
//     // Écrire le contenu du heredoc dans le pipe
//     if (heredoc_content)
//         write(pipe_fd[1], heredoc_content, ft_strlen(heredoc_content));
//     close(pipe_fd[1]); // Fermer l'extrémité d'écriture
    
//     // Rediriger l'entrée standard vers le pipe
//     if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
//     {
//         close(pipe_fd[0]); 
//         return error_handler("setup_redirection", "dup2 error for heredoc", 0, EXIT_FAILURE);
//     }
//     close(pipe_fd[0]);
    
//     return 0;
// }

// /* Configure la redirection d'entrée vers le fichier spécifié.
//  * Le fichier spécifié est ouvert.
//  * Son descripteur de fichier est redirigé grâce à dup2 vers stdin.
//  */
// static int	setup_input_redirection(const char *input_file)
// {
// 	int fd_in; // Descripteur pour le fichier d'entrée

// 	fd_in = open(input_file, O_RDONLY);
// 	if (fd_in == -1) // Erreur : ouverture fichier entrée échouée
// 		return error_handler(input_file,"No such file or directory" , 1, EXIT_FAILURE);
// 	if (dup2(fd_in, STDIN_FILENO) == -1) // Erreur : duplication de STDIN échouée
// 	{
// 		close(fd_in); // On nettoie avant de retourner
// 		return error_handler("setup_redirection", "dup2 error for input", 1, EXIT_FAILURE);
// 	}
// 	close(fd_in); // Libère fd_in, car il n'est plus nécessaire
// 	return 0;
// }

/* Configure la redirection de sortie vers le fichier spécifié.
 * Le fichier spécifié est ouvert (ou créé) avec les permissions appropriées.
 * Son descripteur de fichier est redirigé grâce à dup2 vers stdout.
 */
int	setup_output_redirection(const char *output_file, int append)
{
	int fd_out; // Descripteur pour le fichier de sortie
	int flags; // Ouverture en écriture (création si nécessaire)

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND; // Mode ajout (`>>`)
	else
		flags |= O_TRUNC;  // Mode écrasement (`>`)
	fd_out = open(output_file, flags, 0644); // Permission rw-r--r--
	if (fd_out == -1) // Erreur : ouverture fichier sortie échouée
		return error_handler(output_file, "Permission denied", 1, EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == -1) // Erreur : duplication de STDOUT échouée
	{
		close(fd_out); // On nettoie avant de retourner
		return error_handler(output_file, "No such file or directory", 1, EXIT_FAILURE);
	}
	close(fd_out); // Libère fd_out, car il n'est plus nécessaire
	return 0;
}

/* Cette fonction gère toutes les redirections d'entrée/sortie.
 * Elle redirige stdin ou stdout en fonction des fichiers spécifiés
 */
int setup_redirection(t_redirection *redirections)
{
    t_redirection *current = redirections;
    int fd;
    
    while (current)
    {
        switch (current->type)
        {
            case REDIR_INPUT:
                fd = open(current->file, O_RDONLY);
                if (fd < 0)
                    return error_handler("open", strerror(errno), 1, 1);
                dup2(fd, STDIN_FILENO);
                close(fd);
                break;
                
            case REDIR_OUTPUT:
                fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                    return error_handler("open", strerror(errno), 1, 1);
                dup2(fd, STDOUT_FILENO);
                close(fd);
                break;
                
            case REDIR_APPEND:
                fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0)
                    return error_handler("open", strerror(errno), 1, 1);
                dup2(fd, STDOUT_FILENO);
                close(fd);
                break;
                
            case REDIR_HEREDOC:
                if (current->heredoc_content)
                {
                    int pipe_fd[2];
                    if (pipe(pipe_fd) == -1)
                        return error_handler("pipe", strerror(errno), 1, 1);
                    
                    write(pipe_fd[1], current->heredoc_content, ft_strlen(current->heredoc_content));
                    close(pipe_fd[1]);
                    
                    dup2(pipe_fd[0], STDIN_FILENO);
                    close(pipe_fd[0]);
                }
                break;
        }
        current = current->next;
    }
    return 0;
}


/* Restaure les descripteurs originaux de l'entrée 
 * et la sortie standard après une redirection*/
void restore_io(int stdin_fd, int stdout_fd)
{
	if (stdin_fd >= 0)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
	if (stdout_fd >= 0)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}
