/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:15 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/16 17:34:10 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_token
{
	char	*str;
	struct s_token	*prev;
	struct s_token	*prev;
}	t_token;

typedef struct	s_cmd
{


}	t_cmd;

typedef struct	s_data
{
	t_token	*token;
	t_cmd	*cmd;
	//t_env	*env;
	int     exit_code;
}				t_data;


//parse
bool	parseline(t_data *data, char *line);
void    quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);

//utils
bool    print_error(char *str);

bool	parseline(t_data *data, char *line);

#endif