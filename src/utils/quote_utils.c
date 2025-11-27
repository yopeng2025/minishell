/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:32:16 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:32:17 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_char(char *out, char c)
{
	char	*tmp;

	tmp = ft_strjoin_char(out, c);
	free(out);
	return (tmp);
}

static char	*join_special(char *out, const char *s)
{
	char	*tmp;

	tmp = ft_strjoin(out, s);
	free(out);
	return (tmp);
}

static int	handle_double_redir(char *str, int i, char **out)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		*out = join_special(*out, "\"<<\"");
		return (2);
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		*out = join_special(*out, "\">>\"");
		return (2);
	}
	return (0);
}

static void	process_char(char c, char **out)
{
	if (c == '<')
		*out = join_special(*out, "\"<\"");
	else if (c == '>')
		*out = join_special(*out, "\">\"");
	else if (c == '|')
		*out = join_special(*out, "\"|\"");
	else
		*out = join_char(*out, c);
}

char	*add_quote_special_char(char *str)
{
	char	*out;
	int		i;
	int		skip;

	out = ft_strdup("");
	if (!out)
		return (NULL);
	i = 0;
	while (str[i])
	{
		skip = handle_double_redir(str, i, &out);
		if (skip)
		{
			i += skip;
			continue ;
		}
		process_char(str[i], &out);
		i++;
	}
	return (out);
}
