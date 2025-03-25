/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/03/15 14:26:10 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
static int	setup_output_redirection(const char *output_file, int append)
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
int	setup_redirection(const char *input_file, const char *output_file, int append)
{
	if (input_file)
	{
		if (setup_input_redirection(input_file) != 0)
			return (EXIT_FAILURE);
	}
	if (output_file)
	{
		if (setup_output_redirection(output_file, append) != 0)
			return (EXIT_FAILURE);
	}
	return (0); // Succès
}

void restore_io(char *stdin_backup, char *stdout_backup)
{
    if (stdin_backup)
    {
        dup2(STDIN_FILENO, atoi(stdin_backup));
        close(atoi(stdin_backup));
        free(stdin_backup);
    }
    if (stdout_backup)
    {
        dup2(STDOUT_FILENO, atoi(stdout_backup));
        close(atoi(stdout_backup));
        free(stdout_backup);
    }
}

int check_redirections(t_cmd *cmd)
{
    // Check input redirection
    if (cmd->input_file)
    {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd < 0)
        {
            perror(cmd->input_file);
            return (1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    // Check output redirection
    if (cmd->output_file)
    {
        int flags = O_WRONLY | O_CREAT;
        if (cmd->append)
            flags |= O_APPEND;
        else
            flags |= O_TRUNC;

        int fd = open(cmd->output_file, flags, 0644);
        if (fd < 0)
        {
            perror(cmd->output_file);
            return (1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    return (0);
}
/* O_CREAT: Crée un fichier s'il n'existe pas.
O_WRONLY: Ouvre le fichier en écriture uniquement.
O_RDONLY: Ouvre le fichier en lecture uniquement.
O_RDWR: Ouvre le fichier en lecture et en écriture.
O_TRUNC: Tronque le fichier à une taille de 0 lorsqu'il est ouvert.
O_APPEND: Ajoute des données à la fin du fichier sans écraser son contenu existant.
O_EXCL: Utilisé avec O_CREAT pour empêcher la création du fichier si celui-ci existe déjà.
*/