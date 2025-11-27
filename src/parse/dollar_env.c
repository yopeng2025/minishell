/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:19 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:55:48 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

char	*get_dollar_word(char *line, int size)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * size);
	if (!word)
		return (NULL);
	i = 0;
	while (line[++i] && i < size)
		word[i - 1] = line[i];
	word[i - 1] = '\0';
	return (word);
}

char	*get_elem_env(t_list *env, char *key)
{
	t_list	*tmp;
	int		list_len;
	int		key_len;
	int		i;

	if (!key)
		return (NULL);
	tmp = env;
	list_len = len_list(tmp);
	key_len = ft_strlen(key);
	while (list_len--)
	{
		if (ft_strncmp(tmp->str, key, key_len) == 0 && \
			tmp->str[key_len] == '=')
		{
			i = 0;
			while (tmp->str[i] && tmp->str[i] != '=')
				i++;
			return (ft_strdup(&tmp->str[i + 1]));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	add_char(char *c, char **str, int *index)
{
	char	char_to_str[2];
	char	*tmp;

	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}
