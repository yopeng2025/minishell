#include "minishell.h"

void	child_progress(t_data *data, t_cmd *cmd)
{
	// if (!cmd->skip_cmd)
	// 	data->exit_code = 1; // ?？为什么要等于1
	if (is_builtin(cmd))
	

}

void	parent_progress(t_data *data, t_cmd *cmd)
{
	
}


void	execute_cmd(t_data *data, t_cmd *cmd)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all(data, NULL, -1); //需要再看 因为不知道如何打印错误信息
	else if (g_signal_pid == 0)
		child_progress(data, cmd);
	else
		parent_progress(data, cmd);
}

void	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	tmp = data->cmd;
	pip = data->pip;
	if (tmp && tmp->cmd_param[0] && tmp->next == tmp \
		&& tmp->skip_cmd == false && is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(data, tmp));
	if (pipe(pip) == -1)
		//error notif
		free_all(data, NULL, -1); //需要再看 因为不知道如何打印错误信息
	execute_cmd(data, tmp);
	tmp = tmp->next;
	while (tmp != data->cmd)
	{
		if (pipe(pip) == -1)
			free_all(data, NULL, 1);
		execute_cmd(data, tmp);
		tmp = tmp->next;
	}
	wait_all(data);
}
