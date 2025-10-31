#include "minishell.h"

static bool	export_no_arg(t_list *env)
{
	
}

int	ft_export(char **cmd, t_list **env)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!cmd || !cmd[i])
	{
		if (*env && !export_no_arg(*env))
			return (print_error(ERR_MALLOC));
		return (0);
	}
	while (cmd[i])
	{
		if (!valid_identifier(cmd[i]))
		{
			print_error("export: invalid idnetifier\n");
			exit_code = 1;
		}
		else if (!export(cmd[i], env))
			return(print_error(ERR_MALLOC));
		i++;
	}
	return (exit_code);
}
