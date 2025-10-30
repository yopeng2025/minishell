#include "minishell.h"


bool	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	tmp = data->cmd;
	pip = data->pip;
	if (tmp && tmp->cmd_param[0] && tmp->next == tmp \
		&& tmp->skip_cmd == false && is_buildin(tmp->cmd_param[0]))
		return (launch_buildin(data, tmp));
	return (true);
}
