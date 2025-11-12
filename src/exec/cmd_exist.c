#include "minishell.h"
/* $PATH=/usr/local/bin:/usr/bin:/bin
	cmd=ls
	path_return=/usr/local/bin/ls
	path_return=/usr/bin/ls
	path_return=/bin/ls             
	PATH指针移动到：后面一位			 */
void	strslashjoin(char *path_return, char *cmd, char *path_in_env, int *i)
{
	int	j;
	int	k;

	j = 0;
	while(*i < (PATH_MAX - 1) && path_in_env[*i] && path_in_env[*i] != ':')
		path_return[j++] = path_in_env[(*i)++];
	(*i)++;
	path_return[j++] = '/';
	k = 0;
	while (k < (PATH_MAX - 1) && cmd[k])
		path_return[j++] = cmd[k++];
	path_return[j] = '\0';
}

/* 找出ENV中的$PATH=/usr/local/bin:/usr/bin:/bin
	返回=后面的值 
	即/usr/local/bin:/usr/bin:/bin  */
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

char	*cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	return (NULL);
}

char	*find_path(t_data *data, char *cmd, t_list *env)
{
	char	*path_in_env;
	char	path_return[PATH_MAX];
	int		i;
	int		len;

	path_in_env = create_path(env, len_list(env));
	if (!path_in_env || ft_strlen(cmd) > PATH_MAX / 2)
		return(cmd_not_found(cmd));
	i = 0;
	len = ft_strlen(path_in_env);
	while (i < len)
	{
		strslashjoin(path_return, cmd, path_in_env, &i);
		if (access(path_return, F_OK) == 0)
		{
			cmd = ft_strdup(path_return);
			if (!cmd)
			{
				print_error(ERR_MALLOC);
				data->exit_code = -1;
			}
			return (cmd);
		}
	}
	return (cmd_not_found(cmd));
}

bool	cmd_exist(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_path(data, cmd, data->env);
	else
		absolute_path(path, cmd, data);//这一步骤让path=cmd，即path=./a.out
	if (!(*path) && data->exit_code == -1)
		free_all(data, NULL, data->exit_code);
	if (!(*path))
	{
		data->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK) !=0)
	{
		perror(*path);
		free(*path);
		(*path) = NULL;
		data->exit_code = 126;
		return (false);
	}
	if (is_dir(path, cmd, data))
		return (false);
	return(true);
}