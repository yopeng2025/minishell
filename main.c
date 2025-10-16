#include "minishell.h"

int main(int ac, char *av[], char **env)
{
	char	*line;
	t_data	data;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		line = readline("minishell> ");
		if (*line)
			add_history(line);
		printf("You typed: %s\n", line);
		if (!parseline(&data, line))
			continue ;
		// exec(&data);
		free(line);
	}

    return (0);
}
