#include "../../includes/minishell.h"

t_env_list	*ft_env_last(t_env_list *lst)
{
    t_env_list *tmp;

    if (!lst)
        return (NULL);
    tmp = lst;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    return (tmp);
}

void	ft_lst_env_back(t_env_list **lst, t_env_list *new)
{
    t_env_list *tmp;

    if (lst == NULL || new == NULL)
        return ;
    if (*lst == NULL)
    {
        *lst = new;
        return ;
    }
    tmp = ft_env_last(*lst);
    tmp->next = new;
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*tmp;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '=';
	i++;

	while (i < size - 1)
	{
		tmp[i] = s2[i - ft_strlen(s1) - 1];

		i++;
	}
	tmp[i] = '\0';

	return (tmp);
}
