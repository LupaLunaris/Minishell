#include "minishell.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static char	*add_word(char const *s, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	fill_tab(char **tab, char const *s, char c)
{
	size_t	ind;
	size_t	i;
	size_t	count;

	i = 0;
	ind = 0;
	while (s[ind])
	{
		count = 0;
		while (s[ind] && s[ind] == c)
			ind++;
		if (!s[ind])
			break ;
		while (s[ind + count] && s[ind + count] != c)
			count++;
		tab[i] = add_word(s + ind, count);
		if (!tab[i])
			return (0);
		ind += count;
		i++;
	}
	tab[i] = NULL;
	return (1);
}

