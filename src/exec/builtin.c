#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strncmp("echo", cmd, INT_MAX) == 0 ||\
		ft_strncmp("cd", cmd, INT_MAX) == 0 ||\
		ft_strncmp("pwd", cmd, INT_MAX) == 0 ||\
		ft_strncmp("export", cmd, INT_MAX) == 0 ||\
		ft_strncmp("unset", cmd, INT_MAX) == 0 ||\
		ft_strncmp("env", cmd, INT_MAX) == 0 ||\
		ft_strncmp("exit", cmd, INT_MAX) == 0)
		return (true);
	return (false);
}
void	exec_builtin(int save_stdout, t_data *data, t_cmd *cmd)
{
	if (ft_strncmp("echo", cmd->cmd_param[0], INT_MAX) == 0)
		data->exit_code = ft_echo(cmd->cmd_param);
	else if (ft_strncmp("cd", cmd->cmd_param[0], INT_MAX) == 0)
		data->exit_code = ft_cd(data, cmd->cmd_param);
	else if (ft_strncmp("pwd", cmd->cmd_param[0], INT_MAX) == 0)
		data->exit_code = ft_pwd();
	else if (ft_strncmp("export", cmd->cmd_param[0], INT_MAX) == 0)
		data->exit_code = ft_export(cmd->cmd_param, &data->env);
	else if (ft_strncmp("unset", cmd->cmd_param[0], INT_MAX) == 0)
		data->exit_code = ft_unset(cmd->cmd_param, &data->env);
	else if (ft_strncmp("env", cmd->cmd_param[0], INT_MAX) == 0)
		data->exit_code = ft_env(data->env, cmd->cmd_param);
	else if (ft_strncmp("exit", cmd->cmd_param[0], INT_MAX) == 0)
	{
		if (cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(data, cmd->cmd_param);
	}
}

void	launch_builtin(t_data *data, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
	}
	exec_builtin(save_stdout, data, cmd);
	if (cmd->outfile >= 0)
	{
		dup2(save_stdout, 1);
		close(save_stdout);
	}
}
