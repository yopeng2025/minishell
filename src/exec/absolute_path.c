/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:35 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:36 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	return (NULL);
}

void	absolute_path(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	if (access((*path), F_OK) != 0)
	{
		cmd_not_found(cmd);
		free (*path);
		*path = NULL;
	}
}

bool	is_dir(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error(cmd);
		print_error(" : Is a directory\n");
		data->exit_code = 126;
		return (true);
	}
	return (false);
}
