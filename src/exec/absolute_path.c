#include "minishell.h"

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
	if (!S_ISREG(path_stat.st_mode)) //true可执行文件 false目录
	{
		print_error(cmd);
		print_error(" : Is a directory\n");
		data->exit_code = 126;
		return(true);
	}
	return (false);
}