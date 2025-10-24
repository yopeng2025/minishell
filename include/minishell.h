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

# include "libft.h"
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
	char	*cmd_param;
	int		infile;
	int		outfile;
	bool	skip_cmd;
	struct s_cmd	*prev;
	struct s_cmd	*next;
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
	t_cmd	*cmd;
	t_list	*env;
	int     exit_code;
	bool	sq;
}				t_data;

//parse
bool	parseline(t_data *data, char *line);
void	quoting_choice(bool *dq, bool *sq, int *index, char c);
int		open_quote(t_data *data, char *line);
bool	create_list_token(t_token **head_token, char *line);
int		add_dollar(char *line, int *index, char **str, t_data *data);
int		replace_dollar(char **line, t_data *data);
int		exist_in_env(char *line, int *i, t_data *data);
char	*get_dollar_word(char *line, int size);
char	*get_elem_env(t_list *env, char *key);
//int		append_exit_code(t_data *data, char **str);

//token
void	print_token_list(t_token *head);
t_token	*create_new_token(char *str, int type);
void	add_new_back(t_token **head_token, t_token *new);
void	cpy_str(char *str, char *line , int len);
bool	is_quote(char c);
int		get_token_lenth(char **line);
bool	add_token_node(t_token **head_token, char *str, int type);
bool	add_token(char **line, t_token **head_token);
bool	is_space(char c);
int		is_special(char *line);
bool	add_special_token(char **line, t_token **head_token, int type);
bool	create_list_token(t_token **head_token, char *line);

//command
//bool	create_list_cmd(t_data *data);

// free
void	free_all(t_data *data, char *err, int ext);
int		free_list(t_list **env);
void	free_token_list(t_token **head_token);

//utils
bool	print_error(char *str);

//utils_list
size_t	len_list(t_list *list);
int		append(t_list **list, char *str);
int		ft_search(char *str, char c);

//free
int		free_list(t_list **env);
void	free_all(t_data *data, char *err, int ext);

#endif