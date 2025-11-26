#include "minishell.h"

void	update_cwd(t_data *data, char *path)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	(void)path;
	update_oldpwd(data);
	if (!getcwd(cwd, PATH_MAX))
	{
		print_error(path);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		print_error(ERR_MALLOC);
		return ;
	}
	export(pwd, &data->env);
	free(pwd);
}

void	dir_not_found(char *param1, char *param2)
{
	write(2, "minishell: ", 12);
	write(2, param1, ft_strlen(param1));
	write(2, ": ", 3);
	write(2, param2, ft_strlen(param2));
	write(2, ": No such file or directory\n", 29);
}

int	ft_cd(t_data *data, char **cmd_param)
{
	if (count_param(cmd_param) > 2)
	{
		print_error("minishell: cd: too many arguments\n");
		return (1);
	}
	if (count_param(cmd_param) == 1)
		return (cd_home(data, cmd_param));
	if (ft_strncmp("~", cmd_param[1], ft_strlen(cmd_param[1])) == 0)
		return (cd_home(data, cmd_param));
	else if (ft_strncmp("-", cmd_param[1], ft_strlen(cmd_param[1])) == 0)
		return (cd_oldpwd(data, cmd_param));
	if (chdir(cmd_param[1]) == -1)
	{
		dir_not_found(cmd_param[0], cmd_param[1]);
		return (1);
	}
	update_cwd(data, cmd_param[1]);
	return (0);
}
