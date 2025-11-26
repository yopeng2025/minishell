#include "minishell.h"

void	dir_not_found(char *param1, char *param2)
{
	write(2, "minishell: ", 12);
	write(2, param1, ft_strlen(param1));
	write(2, ": ", 3);
	write(2, param2, ft_strlen(param2));
	write(2, ": No such file or directory\n", 29);
}

char	*is_home_exist(t_data *data)
{
	char	*home;
	t_list	*tmp;

	tmp = data->env;
	home = NULL;
	if (!ft_strncmp(tmp->str, "HOME=", 5))
		home = ft_strdup(tmp->str + 5);
	tmp = tmp->next;
	while (tmp != data->env)
	{
		if (!ft_strncmp(tmp->str, "HOME=", 5))
		{
			home = ft_strdup(tmp->str + 5);
			break ;
		}
		tmp = tmp->next;
	}
	return (home);
}

char	*is_oldpwd_exist(t_data *data)
{
	char	*oldpwd;
	t_list	*tmp;

	tmp = data->env;
	oldpwd = NULL;
	if (!ft_strncmp(tmp->str, "OLDPWD=", 7))
		oldpwd = ft_strdup(tmp->str + 7);
	tmp = tmp->next;
	while (tmp != data->env)
	{
		if (!ft_strncmp(tmp->str, "OLDPWD=", 7))
		{
			oldpwd = ft_strdup(tmp->str + 7);
			break ;
		}
		tmp = tmp->next;
	}
	return (oldpwd);
}

int	cd_home(t_data *data, char **cmd_param)
{
	char	*home;

	home = is_home_exist(data);
	if (home == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, cmd_param[0], ft_strlen(cmd_param[0]));
		write(2, ": HOME not set\n", 16);
		return (1);
	}
	if (chdir(home) == -1)
	{
		dir_not_found(cmd_param[0], home);
		free(home);
		return (1);
	}
	update_cwd(data, home);
	free(home);
	return (0);
}

int	cd_oldpwd(t_data *data, char **cmd_param)
{
	char	*oldpwd;

	oldpwd = is_oldpwd_exist(data);
	if (oldpwd == NULL)
	{
		write(2, "minishell: ", 12);
		write(2, cmd_param[0], ft_strlen(cmd_param[0]));
		write(2, ": OLDPWD not set\n", 16);
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		dir_not_found(cmd_param[0], oldpwd);
		free(oldpwd);
		return (1);
	}
	update_cwd(data, oldpwd);
	printf("%s\n", oldpwd);
	free(oldpwd);
	return (0);
}
