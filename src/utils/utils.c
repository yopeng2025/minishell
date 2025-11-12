#include "minishell.h"

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

int	count_param(char **cmd_param)
{
	int	count;

	count = 0;
	while (cmd_param[count])
		count++;
	return (count);
}
