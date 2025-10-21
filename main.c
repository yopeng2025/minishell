#include "minishell.h"

void	initial_data(t_data *data)
{
	data->exit_code = 0;
	data->token = NULL;
}

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	char	*tmp;
	int		i;

	i = 0;
	list = NULL;
	while(env[i])
	{
		tmp = ft_strdup(env[i]);
		append(&list, tmp);
		i++;
	}
	data->env = list;
	return (1);
}

/* env字符串数组，每个元素都是一个 "KEY=VALUE" 形式的环境变量 */
int main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	(void)argc;
	(void)argv;

	initial_data(&data);
	make_env(&data, env);
	
	while (1)
	{
		line = readline("minishell> ");
		if (*line)
			add_history(line);
		printf("You typed: %s\n", line);
		if (!parseline(&data, line))
		 	continue ;
		//print_token_list(data.token);
		// exec(&data);
		//free_token_list(&data.token);
		free(line);
	}

    return (0);
}
