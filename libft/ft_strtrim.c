/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:52:28 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/15 15:52:09 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		start;	
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isset(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_isset(s1[end], set))
		end--;
	if (end == 0)
		return (ft_strdup(""));
	new = (char *)malloc((end - start + 2) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		new[i++] = s1[start++];
	new[i] = '\0';
	return (new);
}
