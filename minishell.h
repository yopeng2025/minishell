/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:15 by peiyli            #+#    #+#             */
/*   Updated: 2025/10/21 15:11:20 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_MALLOC "malloc error\n"
# define EXT_MALLOC 1

# define INPUT		1 	//"<"
# define HEREDOC	2	//"<<"
# define TRUNCATE	3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_token
{
	char	*str;
	int		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct	s_cmd
{


}	t_cmd;

// typedef struct s_list
// {
// 	char			*str;
// 	struct s_list	*prev;
// 	struct s_list	*next;
// }				t_list;

typedef struct	s_data
{
	t_token	*token;
	// t_cmd	*cmd;
	//t_env	*env;
	int     exit_code;
	bool	sq;
}				t_data;


//parse
bool	parseline(t_data *data, char *line);
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
bool	create_list_token(t_token **head_token, char *line);

//token
void	print_token_list(t_token *head);
void	free_token_list(t_token **head_token);
t_token	*create_new_token(char *str, int type);
void	add_new_back(t_token **head_token, t_token *new);
void	cpy_str(char *str, char *line , int len);
bool	is_quote(char c);
int		get_token_lenth(char **line);
bool	add_token_node(t_token **head_token, char *str, int type);
bool	add_token(char **line, t_token **head_token);
int		is_special(char *line);
bool	is_space(char c);


//utils
bool    print_error(char *str);


#endif