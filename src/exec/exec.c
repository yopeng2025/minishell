#include "minishell.h"


void	redirect_io(t_data *data, t_cmd *cmd)
{
	close(data->pip[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != data->cmd)
		dup2(data->pip[1], 1);
	close(data->pip[1]);
}

void	built(t_data *data, t_cmd *cmd)
{
	close(data->pip[0]);
	if (cmd->outfile < 0 && cmd->next != data->cmd)
		cmd->outfile = data->pip[1];
	else
		close(data->pip[1]);
	launch_builtin(data, cmd);
}

void	child_progress(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	*envp;

	path = NULL;
	if (!cmd->skip_cmd)
		data->exit_code = 1; // ?？为什么要等于1
	if (is_builtin(cmd))
		built(data, cmd);
	if (cmd_exist(&path, data, cmd->cmd_param[0]))
	{
		redirect_io(data, cmd);
		envp = list_to_array(data->env);
		if (!envp)
			free_all(data, NULL, 1);
		rl_clear_history();
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd, envp);
		if (path)
			free(path);
		free_all(data, NULL, data->exit_code);
	}
}

void	parent_progress(t_data *data, t_cmd *cmd)
{
	close(data->pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->next->infile == -2 && cmd->next != data->cmd)
		cmd->next->infile = data->pip[0];
	else
		close(data->pip[0]);
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
	while (len_cmd)
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
