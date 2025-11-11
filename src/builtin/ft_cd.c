#include "minishell.h"

// void	update_oldpwd(t_data *data)
// {
// 	t_list	*tmp_env;
// 	char	*old_pwd;

// 	tmp_env = data->env;
// 	old_pwd = NULL;
// 	if (!ft_strncmp(tmp_env->str, "PWD=", 4))
// 		old_pwd = tmp_env->str;
// 	tmp_env = tmp_env->next;
// 	while (tmp_env != data->env)
// 	{
// 		if (!ft_strncmp(tmp_env->str, "PWD=", 4))
// 		{
// 			old_pwd = tmp_env->str;
// 			break ;
// 		}
// 		tmp_env = tmp_env->next;
// 	}
// 	if (!old_pwd)
// 		export("OLDPWD=", &data->env);
// 	if (old_pwd)
// 	{
// 		old_pwd = ft_strjoin("OLD", old_pwd);
// 		if (!old_pwd)
// 		{
// 			//打印错误信息
// 			return ;
// 		}
// 		export(old_pwd, &data->env);
// 	}
// 	free(old_pwd);
// }

static void	update_cwd(t_data *data, char *path)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	(void)path;
	// update_oldpwd(data); 这个函数可以去掉不写 因为cd -不是相对或绝对路径
	if (!getcwd(cwd, PATH_MAX))
	{
		//打印错误信息
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		//打印错误信息
		return ;
	export(pwd, &data->env);
	free(pwd);
}
static int	count_param(char **cmd_param)
{
	int	count;

	count = 0;
	while (cmd_param[count])
		count++;
	return (count);
}

int	ft_cd(t_data *data, char **cmd_param)
{
	if (count_param(cmd_param) > 2)
	{
		//打印错误信息 minishell: cd: too many arguments
		return (1);
	}
	if (count_param(cmd_param) == 1)
	{
		// chdir()把cwd更新为home
		return (0);
	}
	if (chdir(cmd_param[1]) == -1)
	{
		//打印错误信息
		return (1);
	}
	update_cwd(data, cmd_param[1]);
	return (0);
}
