/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/19 14:22:12 by Jpaulis          ###   ########.fr       */
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
void setup_redirection(const char *input_file, const char *output_file, int append)
{
	if (input_file)
	{ // Si un fichier d'entrée (`<`) est spécifié
		int fd_in = open(input_file, O_RDONLY); // Ouvre le fichier en lecture seulement.
		if (fd_in == -1) {  // Si le fichier n'est pas accessible :
			perror("Error opening input file");
			exit(EXIT_FAILURE); // Termine le programme à cause d'une erreur critique.
		}
		dup2(fd_in, STDIN_FILENO);  // Remplace l'entrée standard par ce fichier.
		close(fd_in);  // Ferme le fichier après duplication.
	}
	if (output_file)
	{ // Si un fichier de sortie (`>` ou `>>`) est spécifié
		int flags = O_WRONLY | O_CREAT;
		if (append)
    		flags |= O_APPEND;  // Ajoute le flag O_APPEND pour "append"
		else
    		flags |= O_TRUNC;   // Ajoute le flag O_TRUNC pour "truncate"
		// Détermine les modes d'ouverture : append ou écrasement
		int fd_out = open(output_file, flags, 0644); // Autorisations : rw-r--r--
		if (fd_out == -1)
		{ // Si le fichier n'est pas accessible :
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);  // Remplace la sortie standard par ce fichier.
		close(fd_out);  // Ferme le fichier après duplication.
	}
}

/* O_CREAT: Crée un fichier s'il n'existe pas.
O_WRONLY: Ouvre le fichier en écriture uniquement.
O_RDONLY: Ouvre le fichier en lecture uniquement.
O_RDWR: Ouvre le fichier en lecture et en écriture.
O_TRUNC: Tronque le fichier à une taille de 0 lorsqu'il est ouvert.
O_APPEND: Ajoute des données à la fin du fichier sans écraser son contenu existant.
O_EXCL: Utilisé avec O_CREAT pour empêcher la création du fichier si celui-ci existe déjà.
*/