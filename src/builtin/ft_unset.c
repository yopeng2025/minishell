/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:27 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:28 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_env(t_list *tmp, t_list **env)
{
	if (tmp->next == tmp)
	{
		(*env) = NULL;
		return ;
	}
	if (tmp == (*env))
		(*env) = tmp->next;
}

static int	position_in_env(char *str, t_list *env)
{
	int		position;
	int		i;
	t_list	*tmp;

	i = 0;
	position = 0;
	tmp = env;
	while (str[i] && str[i] != '=')
		i++;
	if (!ft_strncmp(str, (tmp->str), i) && (tmp->str[i] == '=' || \
		tmp->str[i] == '\0'))
		return (position);
	position++;
	tmp = tmp->next;
	while (tmp != env)
	{
		if (!ft_strncmp(str, (tmp->str), i) && (tmp->str[i] == '=' || \
			tmp->str[i] == '\0'))
			return (position);
		position++;
		tmp = tmp->next;
	}
	return (-1);
}

void	unset(char *str, t_list **env)
{
	int		position;
	int		i;
	t_list	*tmp;

	position = position_in_env(str, (*env));
	if (position >= 0)
	{
		tmp = (*env);
		i = 0;
		while (i < position)
		{
			tmp = tmp->next;
			i++;
		}
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp->str);
		check_env(tmp, env);
		free(tmp);
		tmp = NULL;
	}
}

int	ft_unset(char **str, t_list **env)
{
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 0;
	while (str[i])
	{
		unset(str[i], env);
		i++;
	}
	return (exit_code);
}
