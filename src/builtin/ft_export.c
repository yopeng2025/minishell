#include "minishell.h"

/*  
	输入 export 后面没有变量
	输出 declare -x USER="yopeng"
		...	
	按变量首字母顺序排列
*/
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
/*
	环境变量开头:  字母a-z 下划线_
	环境变量名组成：字母a-z 下划线_ 数字0-9 
*/
bool static	valid_identifier(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd[0] || (!ft_isalpha(cmd[0]) && cmd[0] != '_'))
		return (false);
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (false);
		i++;
	}
	return (true);
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

/*
	export + 环境变量存在：找出在env的位置，更新'='后面的值
	export + 环境变量不存在：追加到env链表最后面
*/
bool	export(char	*str, t_list **env)
{
	int		position;
	int		i;
	char	*tmp_str;
	t_list	*tmp_env;

	tmp_str = ft_strdup(str);
	if (!tmp_str)
		return (false);
	position = position_in_env(str, (*env));
	if (position >=0)
	{
		i = 0;
		tmp_env = (*env);
		while (i < position)
		{
			i++;
			tmp_env = tmp_env->next;
		}
		free(tmp_env->str);
		tmp_env->str = tmp_str;
	}
	else if (position == -1)
		if (!append(env, tmp_str))
			return(false);
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
			// print_error(" not a valid identifier\n");
			exit_code = 1;
		}
		else if (!export(cmd[i], env))
			return(print_error(ERR_MALLOC));
		i++;
	 }
	return (exit_code);
}
