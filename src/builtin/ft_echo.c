#include "minishell.h"

// return false if "-n" option found (no newline)
// return true otherwise (print newline)
static bool	check_new_line(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] && cmd[i] == '-')
	{
		i++;
		while (cmd[i] == 'n')
			i++;
		if (i == (int)ft_strlen(cmd))
			return (false);
	}
	return (true);
}

static void	exec_echo(char **cmd, int i, int count, bool new_line)
{
	new_line = check_new_line(cmd[i]);
	if (!new_line)
		i++;
	while (i < count)
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (i != count - 1)
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

/* 如echo后面接 -n 或 -nnnnn... 则输出不换行 */
int	ft_echo(char **cmd)
{
	int		i;
	int		count;
	bool	new_line;

	i = 1;
	count = 0;
	new_line = true;
	while (cmd[count])
		count++;
	exec_echo(cmd, i, count, new_line);
	return (0);
}
