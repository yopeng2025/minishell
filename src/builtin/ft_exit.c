/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:48:27 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/12 12:49:16 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nbr = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && nbr > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		if (sign == -1 && nbr < (LONG_MIN + (str[i] - '0')) / 10)
			return (LONG_MIN);
		nbr = 10 * nbr + (str[i] - '0');
		i++;
	}
	return (sign * nbr);
}

static bool	if_all_numeric(char *cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param[i])
	{
		if (i == 0 && (cmd_param[i] == '-' || cmd_param[i] == '+'))
		{
			i++;
			continue;
		}
		if (cmd_param[i] < '0' || cmd_param[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_data *data, char **cmd_param)
{
	long	exit_code;

	printf("exit\n");
	if (count_param(cmd_param) >= 2)
	// if (cmd_param[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		exit_code =  127;
		return (exit_code);
	}
	if (!cmd_param[1])
		free_all(data, NULL, data->exit_code);
	if (!if_all_numeric(cmd_param[1]))
	{
		write(2, "minishell: exit:", 17);
		write(2, cmd_param[1], ft_strlen(cmd_param[1]));
		write(2, ": numeric argument required\n", 29);
		free_all(data, NULL, 2);
	}
	exit_code = ft_atol(cmd_param[1]);
	exit_code = (unsigned char)exit_code;
	free_all(data, NULL, exit_code);
	return (exit_code);
}
