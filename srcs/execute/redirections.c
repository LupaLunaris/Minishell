/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/26 16:58:57 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/* Cette fonction gère toutes les redirections d'entrée/sortie.
 * Elle redirige stdin ou stdout en fonction des fichiers spécifiés 
 * 
 * Le fichier spécifié est ouvert.
 * Son descripteur de fichier est redirigé grâce à dup2.
 * Les redirections configurent l'entrée (stdin) ou la sortie (stdout).
 */
int	setup_redirection(const char *input_file, const char *output_file, int append)
{
	int fd_in = -1; // Descripteur pour le fichier d'entrée
	int fd_out = -1; // Descripteur pour le fichier de sortie
	if (input_file) // Gestion fichier d'entrée (`<`)
	{
		fd_in = open(input_file, O_RDONLY);
		if (fd_in == -1) // Erreur : ouverture fichier entrée échouée
			return error_handler("setup_redirection", input_file, 0, EXIT_FAILURE);
		if (dup2(fd_in, STDIN_FILENO) == -1) // Erreur : duplication de STDIN échouée
		{
			close(fd_in); // On nettoie avant de retourner
			return error_handler("setup_redirection", "dup2 error for input", 0, EXIT_FAILURE);
		}
		close(fd_in); // Libère fd_in, car il n'est plus nécessaire
	}
	if (output_file)// Gestion fichier de sortie (`>` ou `>>`)
	{
		int flags = O_WRONLY | O_CREAT; // Ouverture en écriture (création si nécessaire)
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
	}
	return 0; // Succès
}


/* O_CREAT: Crée un fichier s'il n'existe pas.
O_WRONLY: Ouvre le fichier en écriture uniquement.
O_RDONLY: Ouvre le fichier en lecture uniquement.
O_RDWR: Ouvre le fichier en lecture et en écriture.
O_TRUNC: Tronque le fichier à une taille de 0 lorsqu'il est ouvert.
O_APPEND: Ajoute des données à la fin du fichier sans écraser son contenu existant.
O_EXCL: Utilisé avec O_CREAT pour empêcher la création du fichier si celui-ci existe déjà.
*/