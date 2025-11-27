/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:31:51 by yopeng            #+#    #+#             */
/*   Updated: 2025/11/27 14:31:52 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		free_all(data, ERR_FORK, EXT_FORK);
	else if (g_signal_pid == 0)
	{
		if (cmd->skip_cmd == false)
			child_process(data, cmd, pip);
		else
			free_all(data, NULL, 1);
	}
	else
		parent_process(data, cmd, pip);
}

int	len_cmd(t_data *data)
{
	int		len;
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
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
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
	if (tmp && tmp->skip_cmd == false && tmp->cmd_param[0] && tmp->next == tmp \
		&& is_builtin(tmp->cmd_param[0]))
	{
		launch_builtin(data, tmp);
		return ;
	}
	if (pipe(pip) == -1)
		free_all(data, ERR_PIPE, EXT_PIPE);
	execute_cmd(data, tmp, pip);
	tmp = tmp->next;
	while (tmp != data->cmd)
	{
		if (pipe(pip) == -1)
			free_all(data, ERR_PIPE, EXT_PIPE);
		execute_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
}
