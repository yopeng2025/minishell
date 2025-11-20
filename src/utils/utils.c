#include "minishell.h"

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