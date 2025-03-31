/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/31 18:22:02 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int setup_heredoc_redirection(const char *heredoc_content)
{
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1)
        return error_handler("setup_redirection", "pipe creation failed", 0, EXIT_FAILURE);
        
    // Écrire le contenu du heredoc dans le pipe
    if (heredoc_content)
        write(pipe_fd[1], heredoc_content, ft_strlen(heredoc_content));
    close(pipe_fd[1]); // Fermer l'extrémité d'écriture
    
    // Rediriger l'entrée standard vers le pipe
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
    {
        close(pipe_fd[0]); 
        return error_handler("setup_redirection", "dup2 error for heredoc", 0, EXIT_FAILURE);
    }
    close(pipe_fd[0]);
    
    return 0;
}

/* Configure la redirection d'entrée vers le fichier spécifié.
 * Le fichier spécifié est ouvert.
 * Son descripteur de fichier est redirigé grâce à dup2 vers stdin.
 */
static int	setup_input_redirection(const char *input_file)
{
	int fd_in; // Descripteur pour le fichier d'entrée

	fd_in = open(input_file, O_RDONLY);
	if (fd_in == -1) // Erreur : ouverture fichier entrée échouée
		return error_handler("setup_redirection", input_file, 0, EXIT_FAILURE);
	if (dup2(fd_in, STDIN_FILENO) == -1) // Erreur : duplication de STDIN échouée
	{
		close(fd_in); // On nettoie avant de retourner
		return error_handler("setup_redirection", "dup2 error for input", 0, EXIT_FAILURE);
	}
	close(fd_in); // Libère fd_in, car il n'est plus nécessaire
	return 0;
}

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
		return error_handler("setup_redirection", output_file, 0, EXIT_FAILURE);
	if (dup2(fd_out, STDOUT_FILENO) == -1) // Erreur : duplication de STDOUT échouée
	{
		close(fd_out); // On nettoie avant de retourner
		return error_handler("setup_redirection", "dup2 error for output", 0, EXIT_FAILURE);
	}
	close(fd_out); // Libère fd_out, car il n'est plus nécessaire
	return 0;
}

/* Cette fonction gère toutes les redirections d'entrée/sortie.
 * Elle redirige stdin ou stdout en fonction des fichiers spécifiés
 */
int setup_redirection(t_cmd *cmd)
{
    // Le heredoc a priorité sur les redirections de fichier d'entrée
    if (cmd->heredoc)
    {
        if (setup_heredoc_redirection(cmd->heredoc) != 0)
            return (EXIT_FAILURE);
    }
    else if (cmd->input_file)
    {
        if (setup_input_redirection(cmd->input_file) != 0)
            return (EXIT_FAILURE);
    }
    if (cmd->output_file)
    {
        if (setup_output_redirection(cmd->output_file, cmd->append) != 0)
            return (EXIT_FAILURE);
    }
    return (0);
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
