/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulis <jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:14:11 by jpaulis           #+#    #+#             */
/*   Updated: 2024/10/13 13:31:21 by jpaulis          ###   ########.be       */
/*                                                                            */
/* ************************************************************************** */

/* Divise la chaîne s en un tableau de mots séparés par le caractère c
 * Retourne un tableau de chaînes de caractères résultant de la découpe
 * s : la chaine a decouper
 * c : le caractère délimiteur
 */
#include "libft.h"

static size_t	ft_count_wrd(char const *s, char c)
{
	size_t	nb_wrd;
	size_t	i;

	nb_wrd = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			nb_wrd++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (nb_wrd);
}

static char	*allocate_word(const char *s, size_t start, size_t end)
{
	char	*word;

	word = (char *)malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &s[start], end - start + 1);
	return (word);
}

static void	free_split(char **tab, size_t str)
{
	while (str > 0)
		free(tab[--str]);
	free(tab);
}

static char	**fill_tab(char const *s, char c, char **tab, size_t nb_wrd)
{
	size_t	str;
	size_t	i;
	size_t	start;

	str = 0;
	i = 0;
	while (str < nb_wrd)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[str] = allocate_word(s, start, i);
		if (!tab[str])
		{
			free_split(tab, str);
			return (NULL);
		}
		str++;
	}
	tab[str] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_wrd;
	char	**tab;

	if (!s)
		return (NULL);
	nb_wrd = ft_count_wrd(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_wrd + 1));
	if (!tab)
		return (NULL);
	return (fill_tab(s, c, tab, nb_wrd));
}

/*
#include <stdio.h>
#include "libft.h"

int main() {
	char **result;
	char *s = "To be or not to be";
	char c = ' ';
	int i = 0;

	result = ft_split(s, c);
	while (result[i]) {
		printf("%s\n", result[i]);
		i++;
	}
	i = 0;
	while (result[i]) {
		free(result[i]);
		i++;
	}
	free(result);
	return 0;
}
*/