/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopeng <yopeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:32:42 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/29 15:46:32 by yopeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_signal_pid;

bool	empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (i == (int)ft_strlen(str))
	{
		free(str);
		return (true);
	}
	return (false);
}

void	initial_data(t_data *data)
{
	data->exit_code = 0;
	data->token = NULL;
	data->cmd = NULL;
	data->env = NULL;
	data->pip[0] = -1;
	data->pip[1] = -1;
	g_signal_pid = 0;
	signals();
}

int	make_env(t_data *data, char **env)
{
	t_list	*list;
	char	*tmp;
	int		i;

	if (!(*env))
		return (make_env2(data));
	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		append(&list, tmp);
		i++;
	}
	data->env = list;
	return (1);
}

int	main(int argc, char **argv, char **env)
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
		if (!line)
			free_all(&data, "exit\n", data.exit_code);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
			continue ;
		exec(&data);
		free_token_list(&data.token);
		free_cmd_list(&data.cmd);
		g_signal_pid = 0;
	}
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*line;
// 	t_data	data;
// 	char	*gnl_line;

// 	(void)argc;
// 	(void)argv;
// 	initial_data(&data);
// 	make_env(&data, env);
// 	while (1)
// 	{
// 		if (isatty(fileno(stdin)))
// 			line = readline("minishell> ");
// 		else
// 		{
// 			gnl_line = get_next_line(fileno(stdin));
// 			if (gnl_line == NULL)
// 				free_all(&data, NULL, data.exit_code);
// 			line = ft_strtrim(gnl_line, "\n");
// 			free(gnl_line);
// 		}
// 		if (!line)
// 		{
// 			if (isatty(fileno(stdin)))
// 				free_all(&data, "exit\n", data.exit_code);
// 			else
// 				break ;
// 		}
// 		if (empty_line(line))
// 			continue ;
// 		add_history(line);
// 		if (!parseline(&data, line))
// 			continue ;
// 		exec(&data);
// 		free_token_list(&data.token);
// 		free_cmd_list(&data.cmd);
// 		g_signal_pid = 0;
// 	}
// 	return (0);
// }
