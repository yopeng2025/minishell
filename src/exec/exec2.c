#include "minishell.h"

void	redirect_io(t_data *data, t_cmd *cmd, int *pip)
{
	close(pip[0]);
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
		dup2(pip[1], 1);
	close(pip[1]);
}

void	built(t_data *data, t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->outfile < 0 && cmd->next != data->cmd)
		cmd->outfile = pip[1];
	else
		close(pip[1]);
	launch_builtin(data, cmd);
}

void	child_process(t_data *data, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**envp;

	path = NULL;
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		built(data, cmd, pip);
	else if (cmd_exist(&path, data, cmd->cmd_param[0]))
	{
		redirect_io(data, cmd, pip);
		envp = list_to_array(data->env);
		if (!envp)
			free_all(data, NULL, 1);
		rl_clear_history();
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->cmd_param, envp);
		if (path)
			free(path);
	}
	free_all(data, NULL, data->exit_code);
}

void	parent_process(t_data *data, t_cmd *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->next->infile == -2 && cmd->next != data->cmd)
		cmd->next->infile = pip[0];
	else
		close(pip[0]);
}