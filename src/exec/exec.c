#include "minishell.h"

void	execute_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all(data, NULL, -1); //需要再看 因为不知道如何打印错误信息
	else if (g_signal_pid == 0)
		child_process(data, cmd, pip);
	else
		parent_process(data, cmd, pip);
}

int	len_cmd(t_data *data)
{
	int 	len;
	t_cmd	*tmp;

	tmp = data->cmd;
	tmp = tmp->next;
	len = 1;
	while (tmp != data->cmd)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	wait_all(t_data *data)
{
	t_cmd	*tmp;
	int		status;
	int		pid;
	int		len;

	tmp = data->cmd;
	len = len_cmd(data);
	while (len)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				data->exit_code= WEXITSTATUS(status);
		}
		tmp = tmp->next;
		len--;
	}
}

void	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	tmp = data->cmd;
	pip = data->pip;
	if (tmp && tmp->cmd_param[0] && tmp->next == tmp \
		&& tmp->skip_cmd == false && is_builtin(tmp->cmd_param[0]))
	{
		launch_builtin(data, tmp);
		return ;
	}
	if (pipe(pip) == -1)
		//error notif
		free_all(data, NULL, -1); //需要再看 因为不知道如何打印错误信息
	execute_cmd(data, tmp, pip);
	tmp = tmp->next;
	while (tmp != data->cmd)
	{
		if (pipe(pip) == -1)
			free_all(data, NULL, 1);
		execute_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
}
