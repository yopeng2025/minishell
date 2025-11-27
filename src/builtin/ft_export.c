#include "minishell.h"

static bool	export_no_arg(t_list *env)
{
	char	**array;
	int		i;
	int		j;

	array = list_to_array(env);
	if (!array)
		return (false);
	sort_array(array, env);
	i = 0;
	while (array[i])
	{
		printf("declare -x ");
		j = 0;
		while (array[i][j] && array[i][j] != '=')
			printf("%c", array[i][j++]);
		if (array[i][j] && array[i][j] == '=')
			printf("=\"%s\"\n", &array[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free_array(array);
	return (true);
}

void	update_env_value(t_list *tmp_env, char *tmp_str, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		i++;
		tmp_env = tmp_env->next;
	}
	free(tmp_env->str);
	tmp_env->str = tmp_str;
}

int	position_in_env(char *str, t_list *env)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!env)
		return (-1);
	tmp = env;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	if (!ft_strncmp(str, (tmp->str), i) && ((tmp->str[i]) == '=' \
		|| (tmp->str[i]) == '\0'))
		return (j);
	j++;
	tmp = tmp->next;
	while (tmp != env)
	{
		if (!ft_strncmp(str, (tmp->str), i) && ((tmp->str[i]) == '=' \
			|| (tmp->str[i]) == '\0'))
			return (j);
		j++;
		tmp = tmp->next;
	}
	return (-1);
}

bool	export(char	*str, t_list **env)
{
	int		position;
	char	*tmp_str;
	t_list	*tmp_env;

	tmp_str = ft_strdup(str);
	if (!tmp_str)
		return (false);
	position = position_in_env(str, (*env));
	if (position >= 0)
	{
		tmp_env = (*env);
		update_env_value(tmp_env, tmp_str, position);
	}
	else if (position == -1)
	{	
		if (!export_append(env, tmp_str))
		{
			free(tmp_str);
			return (false);
		}
	}
	return (true);
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
			write(2, "minishell: export: '", 21);
			write(2, cmd[i], ft_strlen(cmd[i]));
			write(2, "': not a valid identifier\n", 27);
			exit_code = 1;
		}
		else if (!export(cmd[i], env))
			return (print_error(ERR_MALLOC));
		i++;
	}
	return (exit_code);
}
