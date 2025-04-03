/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:00:51 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/04/03 20:48:47 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Fonction pour supprimer les guillemets d'une chaîne de caractères */
char	*strip_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_squote;
	int		in_dquote;

	in_squote = 0;
	in_dquote = 0;
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

/* Configure la redirection de sortie vers le fichier spécifié.
 * Le fichier spécifié est ouvert (ou créé) avec les permissions appropriées.
 * Son descripteur de fichier est redirigé grâce à dup2 vers stdout.
 */
int	setup_output_redirection(const char *output_file, int append)
{
	int		fd_out;
	int		flags;
	char	*cleaned_file;

	cleaned_file = strip_quotes((char *)output_file);
	if (!cleaned_file)
		return (error_handler("file", "memory allocation failed", 1, EXIT_FAILURE));
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd_out = open(cleaned_file, flags, 0644);
	if (fd_out == -1)
	{
		error_handler(cleaned_file, strerror(errno), 1, EXIT_FAILURE);
		free(cleaned_file);
		return (EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close(fd_out);
		error_handler(cleaned_file, strerror(errno), 1, EXIT_FAILURE);
		free(cleaned_file);
		return (EXIT_FAILURE);
	}
	close(fd_out);
	free(cleaned_file);
	return (0);
}

/* Cette fonction gère toutes les redirections d'entrée/sortie.
 * Elle redirige stdin ou stdout en fonction des fichiers spécifiés
 */
int	setup_redirection(t_redirection *redirections)
{
	t_redirection	*current;
	int				fd;
	char			*cleaned_file;
	int				pipe_fd[2];

	current = redirections;
	while (current)
	{
		cleaned_file = strip_quotes(current->file);
		if (!cleaned_file)
			return (error_handler("file", "memory allocation failed", 1, EXIT_FAILURE));
		switch (current->type)
		{
			case REDIR_INPUT:
				fd = open(cleaned_file, O_RDONLY);
				if (fd < 0)
				{
					error_handler(cleaned_file, strerror(errno), 1, 1);
					free(cleaned_file);
					return (1);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
				break ;
			case REDIR_OUTPUT:
				fd = open(cleaned_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					error_handler(cleaned_file, strerror(errno), 1, 1);
					free(cleaned_file);
					return (1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break ;
			case REDIR_APPEND:
				fd = open(cleaned_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0)
				{
					error_handler(cleaned_file, strerror(errno), 1, 1);
					free(cleaned_file);
					return (1);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break ;
			case REDIR_HEREDOC:
				if (current->heredoc_content)
				{
					if (pipe(pipe_fd) == -1)
					{
						error_handler("pipe", strerror(errno), 1, 1);
						free(cleaned_file);
						return (1);
					}
					write(pipe_fd[1], current->heredoc_content,
						strlen(current->heredoc_content));
					close(pipe_fd[1]);
					dup2(pipe_fd[0], STDIN_FILENO);
					close(pipe_fd[0]);
				}
			break ;
		}
		free(cleaned_file);
		current = current->next;
	}
	return (0);
}

/* Restaure les descripteurs originaux de l'entrée
 * et la sortie standard après une redirection*/
void	restore_io(int stdin_fd, int stdout_fd)
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
