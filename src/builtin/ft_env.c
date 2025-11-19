#include "minishell.h"

int	ft_env(t_list *env, char **cmd_param)
{
	t_list	*tmp;

	if (count_param(cmd_param) > 1)
	{
		write(2, "env: '", 7);
		write(2, cmd_param[1], ft_strlen(cmd_param[1]));
		write(2, "': No such file or directory\n", 30);
		return (127);
	}
	tmp = env;
	if (!tmp)
		return (0);
	if (ft_strchr(tmp->str, '='))
		printf("%s\n", tmp->str);
	tmp = tmp->next;
	while (tmp != env)
	{
		if (ft_strchr(tmp->str, '='))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (0);
}
