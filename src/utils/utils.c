/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:32:49 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:32:50 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_exit_code(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_code);
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	(*str) = tmp2;
	return (1);
}

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

int	count_param(char **cmd_param)
{
	int	count;

	count = 0;
	while (cmd_param[count])
		count++;
	return (count);
}

bool	make_env2(t_data *data)
{
	char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !append(&(data->env), tmp) || getcwd(path, PATH_MAX) == NULL)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	return (1);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin(s, tmp));
}
