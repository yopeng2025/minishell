/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:59 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:50:15 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char const *s, char c)
{
	int		flag;
	int		n;
	size_t	i;

	i = 0;
	flag = 0;
	n = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			if (flag == 0)
				n++;
			flag = 1;
		}
		else
			flag = 0;
		i++;
	}
	return (n);
}

void	ft_free(char **tab, int j)
{
	while (j > 0)
	{
		j--;
		free(tab[j]);
	}
	free(tab);
}

char	*ft_cpy_str(char const *s1, int n)
{
	int		i;
	char	*s2;

	s2 = (char *)malloc((n + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	i = 0;
	while (i < n && s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	**ft_allo_str(char const *s, char c, char **tab)
{
	size_t	i;
	int		n;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		n = 0;
		while (*(s + n) != c && *(s + n) != '\0')
			n++;
		tab[i] = ft_cpy_str(s, n);
		if (tab[i] == NULL)
		{
			ft_free(tab, i);
			return (NULL);
		}
		i++;
		s += n;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		n;

	if (s == NULL)
		return (NULL);
	n = ft_count_words(s, c);
	tab = (char **)malloc((n + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = ft_allo_str(s, c, tab);
	return (tab);
}
