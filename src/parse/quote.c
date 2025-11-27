/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:47 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:48 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quoting_choice(bool *dq, bool *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*sq)
			*sq = true;
		else if (c == '"' && !*dq)
			*dq = true;
		if (index)
			++(*index);
	}
	else if (c == '\'' || c == '"')
	{
		if (c == '\'' && *sq && !*dq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		if (index)
			++(*index);
	}
}

int	open_quote(t_data *data, char *line)
{
	bool	dq;
	bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	while (line && line[i])
	{
		quoting_choice(&dq, &sq, &i, line[i]);
		if (line[i] && line[i] != '\'' && line[i] != '"')
			i++;
	}
	if (dq || sq)
	{
		print_error("open quote\n");
		data->exit_code = 2;
		return (1);
	}
	return (0);
}
