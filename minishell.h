#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_MALLOC "malloc error\n"
# define EXT_MALLOC 1

# include "libft/libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_token
{
	char	*str;
	// int		type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct	s_cmd
{


}	t_cmd;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef struct	s_data
{
	t_token	*token;
	// t_cmd	*cmd;
	t_list	*env;
	int     exit_code;
	bool	sq;
}				t_data;


//parse
bool	parseline(t_data *data, char *line);
void    quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
bool	create_list_token(t_token **head_token, char *line);
int		add_dollar(char *line, int *index, char **str, t_data *data);
static int	in_env(t_data *data, char *line, int size, char **str);
int		replace_dollar(char **line, t_data *data);
static int	end_word(char *str, char *env);
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_dollar_word(char *line, int size);
char	*get_elem_env(t_list *env, char *key);
//token
void	print_token_list(t_token *head);
void	free_token_list(t_token **head_token);
t_token	*create_new_token(char *str);
void	add_new_back(t_token **head_token, t_token *new);
void	cpy_str(char *str, char *line , int len);
bool	add_token(char **line, t_token **head_token);
bool	is_space(char c);


//utils
bool    print_error(char *str);
size_t	len_list(t_list *list);
int		append(t_list **list, char *str);

#endif