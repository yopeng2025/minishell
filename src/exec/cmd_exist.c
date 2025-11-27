/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:45 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:46 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strslashjoin(char *path_return, char *cmd, char *path_in_env, int *i)
{
	int	j;
	int	k;

	j = 0;
	while (*i < (PATH_MAX - 1) && path_in_env[*i] && path_in_env[*i] != ':')
		path_return[j++] = path_in_env[(*i)++];
	(*i)++;
	path_return[j++] = '/';
	k = 0;
	while (k < (PATH_MAX - 1) && cmd[k])
		path_return[j++] = cmd[k++];
	path_return[j] = '\0';
}

char	*create_path(t_list *env, int len)
{
	t_list	*tmp;

	tmp = env;
	while (len--)
	{
		if (!ft_strncmp(tmp->str, "PATH=", 5))
			return (&tmp->str[5]);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*search_in_paths(t_data *data, char *cmd, char *path_in_env)
{
	char	path_return[PATH_MAX];
	char	*dup;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(path_in_env);
	while (i < len)
	{
		strslashjoin(path_return, cmd, path_in_env, &i);
		if (access(path_return, F_OK) == 0)
		{
			dup = ft_strdup(path_return);
			if (!dup)
			{
				print_error(ERR_MALLOC);
				data->exit_code = -1;
				return (NULL);
			}
			return (dup);
		}
	}
	return (NULL);
}

char	*find_path(t_data *data, char *cmd, t_list *env)
{
	char	*path_in_env;
	char	*res;

	if (cmd[0] == '\0')
		return (cmd_not_found(cmd));
	path_in_env = create_path(env, len_list(env));
	if (!path_in_env || ft_strlen(cmd) > PATH_MAX / 2)
		return (cmd_not_found(cmd));
	res = search_in_paths(data, cmd, path_in_env);
	if (res)
		return (res);
	return (cmd_not_found(cmd));
}

bool	cmd_exist(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_path(data, cmd, data->env);
	else
		absolute_path(path, cmd, data);
	if (!(*path) && data->exit_code == -1)
		free_all(data, NULL, data->exit_code);
	if (!(*path))
	{
		data->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK) != 0)
	{
		perror(*path);
		free(*path);
		(*path) = NULL;
		data->exit_code = 126;
		return (false);
	}
	if (is_dir(path, cmd, data))
		return (false);
	return (true);
}
