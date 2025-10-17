/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:02:08 by yopeng            #+#    #+#             */
/*   Updated: 2025/10/17 16:05:15 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	
}

int	replace_dollar(char **line, t_data *data)
{
	int		i;
	bool	dq;
	char	*str;

	i = 0;
	dq = false;
	data->sq = false;
	str = ft_strdup("");
	while((*line)[i])
	{
		quoting_choice(dq, &data->sq, NULL, (*line)[i]);
		if ((*line)[i] && (*line)[i + 1] &&  (*line)[i] == '$' && \
			(*line)[i + 1] != '\'' && (*line)[i + 1] != '"' && \
			(ft_isalpha((*line)[i + 1]) || (*line)[i + 1] == '?' || \
			(*line)[i + 1] == '_') && !data->sq && \
			!add_dollar((*line), &i, &str, data))
			return (0);
		if ((*line)[i] && !add_char())
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}