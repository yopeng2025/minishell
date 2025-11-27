/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:30:51 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/27 14:30:54 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_pwd_entry(t_list *env)
{
	t_list	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	if (!ft_strncmp(tmp->str, "PWD=", 4))
		return (tmp->str);
	tmp = tmp->next;
	while (tmp && tmp != env)
	{
		if (!ft_strncmp(tmp->str, "PWD=", 4))
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	set_oldpwd_from_pwd(char *pwd, t_data *data)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLD", pwd);
	if (!oldpwd)
		free_all(data, ERR_MALLOC, EXT_MALLOC);
	export(oldpwd, &data->env);
	free(oldpwd);
}

void	update_oldpwd(t_data *data)
{
	char	*pwd_entry;

	if (!data || !data->env)
		return ;
	pwd_entry = find_pwd_entry(data->env);
	if (!pwd_entry)
	{
		unset("OLDPWD", &data->env);
		return ;
	}
	set_oldpwd_from_pwd(pwd_entry, data);
}

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
