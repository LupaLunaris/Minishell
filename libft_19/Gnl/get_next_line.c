/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:54:53 by Jpaulis           #+#    #+#             */
/*   Updated: 2024/11/25 09:36:37 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*extrait une ligne complète (jusqu'au prochain \n ou la fin de stash)*/
static char	*ft_extract_line(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (stash[++i] && stash[i] != '\n')
		line[i] = stash[i];
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*libère la mémoire allouée à un pointeur et met ce pointeur à NULL*/
static char	*ft_free_null(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

/*sauvegarde le reste de stash après la ligne extraite*/
static char	*ft_save_remainder(char *stash)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (ft_free_null(&stash));
	remainder = malloc(sizeof(char) * (ft_strlen(&stash[i + 1]) + 1));
	if (!remainder)
		return (ft_free_null(&stash));
	i++;
	j = 0;
	while (stash[i])
		remainder[j++] = stash[i++];
	remainder[j] = '\0';
	free(stash);
	return (remainder);
}

/*lit le fichier et stocke les données dans stash*/
static char	*ft_read_file(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free_null(&stash));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (ft_free_null(&stash));
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
		if (!stash || ft_strchr(stash, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ft_free_null(&stash));
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = ft_read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line)
		return (ft_free_null(&stash));
	stash = ft_save_remainder(stash);
	return (line);
}

/*
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 42
#include "get_next_line.h"

int	main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/