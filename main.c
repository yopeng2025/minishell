#include "minishell.h"

void	initial_data(t_data *data)
{
	data->exit_code = 0;
	data->token = NULL;
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	(void)argc;
	(void)argv;
	(void)env;
	initial_data(&data);
	while (1)
	{
		line = readline("minishell> ");
		if (*line)
			add_history(line);
		printf("You typed: %s\n", line);
		if (!parseline(&data, line))
			continue ;
		print_token_list(data.token);
		// exec(&data);
		free_token_list(&data.token);
		free(line);
	}

    return (0);
}
